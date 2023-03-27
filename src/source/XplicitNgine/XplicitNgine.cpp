#include "XplicitNgine/XplicitNgine.h"
#include "DataModelV2/JointsService.h"
#include "Globals.h"

XplicitNgine::XplicitNgine() 
{
	
	physWorld = dWorldCreate();
	physSpace = dHashSpaceCreate(0);
	contactgroup = dJointGroupCreate(0);

	dWorldSetGravity(physWorld, 0, -9.8F, 0);
	dWorldSetAutoDisableFlag(physWorld, 1);
	dWorldSetAutoDisableLinearThreshold(physWorld, 0.5F);
	dWorldSetAutoDisableAngularThreshold(physWorld, 0.5F);
	dWorldSetAutoDisableSteps(physWorld, 20);

	this->name = "PhysicsService";
}

XplicitNgine::~XplicitNgine() 
{
	g_dataModel->getJointsService()->remove();
	dJointGroupDestroy (contactgroup);
	dSpaceDestroy (physSpace);
	dWorldDestroy (physWorld);
	dCloseODE();
}

void XplicitNgine::resetBody(PartInstance* partInstance)
{
	deleteBody(partInstance);
	createBody(partInstance);
}

void collisionCallback(void *data, dGeomID o1, dGeomID o2) 
{
	int i,n;
	
	dBodyID b1 = dGeomGetBody(o1);
	dBodyID b2 = dGeomGetBody(o2);
	
	if (b1 && b2 && dAreConnected(b1, b2))
		return;
	
	

	const int N = 4;
	dContact contact[N];
	n = dCollide (o1,o2,N,&contact[0].geom,sizeof(dContact));
	if (n > 0) {
		for (i=0; i<n; i++) {
			contact[i].surface.mode = dContactBounce | dContactSlip1 | dContactSlip2 | dContactSoftERP | dContactSoftCFM | dContactApprox1;

			// Define contact surface properties
			contact[i].surface.bounce = 0.5; //Elasticity
			contact[i].surface.mu = 0.4F; //Friction
			contact[i].surface.slip1 = 0.0;
			contact[i].surface.slip2 = 0.0;
			contact[i].surface.soft_erp = 0.8F;
			contact[i].surface.soft_cfm = 0.01F;
			
			// Create joints
			dJointID c = dJointCreateContact(
				g_xplicitNgine->physWorld,
				g_xplicitNgine->contactgroup,
				contact+i
			);
			
			dJointAttach (c,b1,b2);
			
			if(b1 != NULL) 
			{
				PartInstance* touched = (PartInstance*)dGeomGetData(o2);
				if(touched != NULL) 
				{
					touched->onTouch();
				}
			}
		}
	}
}

void XplicitNgine::deleteBody(PartInstance* partInstance)
{
	g_dataModel->getJointsService()->destroyPartSnap(partInstance);
	if(partInstance->physBody != NULL)
	{
		dBodyEnable(partInstance->physBody);
		dGeomEnable(partInstance->physGeom[0]);
		if(partInstance->isAnchored() || partInstance->isDragging())
		{
			dGeomSetBody(partInstance->physGeom[0], partInstance->physBody);
			dGeomEnable(partInstance->physGeom[0]);
			updateBody(partInstance);
			step(0.03F);
		}

		for(int i = 0; i < dBodyGetNumJoints(partInstance->physBody); i++) {
			dBodyID b1 = dJointGetBody(dBodyGetJoint(partInstance->physBody, i), 0);
			dBodyID b2 = dJointGetBody(dBodyGetJoint(partInstance->physBody, i), 1);
			
			if(b1 != NULL)
			{
				dBodyEnable(b1);
				PartInstance * part = (PartInstance *)dBodyGetData(b1);
				if(part != NULL)
					dGeomEnable(part->physGeom[0]);
			}

			if(b2 != NULL)
			{
				dBodyEnable(b2);
				PartInstance * part = (PartInstance *)dBodyGetData(b2);
				if(part != NULL)
					dGeomEnable(part->physGeom[0]);
			}
			dJointDestroy(dBodyGetJoint(partInstance->physBody, i));
		}
		dBodyDestroy(partInstance->physBody);
		dGeomDestroy(partInstance->physGeom[0]);
		partInstance->physBody = NULL;
	}
}

void XplicitNgine::createBody(PartInstance* partInstance)
{
	if(partInstance->physBody == NULL) 
	{
		
		Vector3 partSize = partInstance->getSize();
		Vector3 partPosition = partInstance->getPosition();
		Vector3 velocity = partInstance->getVelocity();
		Vector3 rotVelocity = partInstance->getRotVelocity();
		
		// init body
		partInstance->physBody = dBodyCreate(physWorld);
		dBodySetData(partInstance->physBody, partInstance);
		
		
		// Create geom
		if(partInstance->shape == Enum::Shape::Block)
		{
			partInstance->physGeom[0] = dCreateBox(physSpace,
					partSize.x,
					partSize.y,
					partSize.z
				);

			dVector3 result;
			dGeomBoxGetLengths(partInstance->physGeom[0], result);
		}
		else
		{
			partInstance->physGeom[0] = dCreateSphere(physSpace, partSize[0]/2);
		}
		
		if(partInstance->physGeom[0])
			dGeomSetData(partInstance->physGeom[0], partInstance);

		dMass mass;
		mass.setBox(sqrt(partSize.x*2), sqrt(partSize.y*2), sqrt(partSize.z*2), 0.7F);
		dBodySetMass(partInstance->physBody, &mass);

		// Create rigid body
		dBodySetPosition(partInstance->physBody, 
			partPosition.x,
			partPosition.y,
			partPosition.z
		);

		dGeomSetPosition(partInstance->physGeom[0], 
			partPosition.x,
			partPosition.y,
			partPosition.z);

		dBodySetLinearVel(partInstance->physBody, velocity.x, velocity.y, velocity.z);
		dBodySetAngularVel(partInstance->physBody, rotVelocity.x, rotVelocity.y, rotVelocity.z);

		Matrix3 g3dRot = partInstance->getCFrame().rotation;
		float rotation [12] = {	g3dRot[0][0], g3dRot[0][1], g3dRot[0][2], 0,
								g3dRot[1][0], g3dRot[1][1], g3dRot[1][2], 0,
								g3dRot[2][0], g3dRot[2][1], g3dRot[2][2], 0};
		dGeomSetRotation(partInstance->physGeom[0], rotation);
		dBodySetRotation(partInstance->physBody, rotation);

		if(!partInstance->isAnchored() && !partInstance->isDragging())
			dGeomSetBody(partInstance->physGeom[0], partInstance->physBody);

	} else {
		if(!partInstance->isAnchored() && !partInstance->isDragging())
		{
			const dReal* velocity = dBodyGetLinearVel(partInstance->physBody);
			const dReal* rotVelocity = dBodyGetAngularVel(partInstance->physBody);
			
			partInstance->setVelocity(Vector3(velocity[0],velocity[1],velocity[2]));
			partInstance->setRotVelocity(Vector3(rotVelocity[0],rotVelocity[1],rotVelocity[2]));

			const dReal* physPosition = dBodyGetPosition(partInstance->physBody);
			
			const dReal* physRotation = dGeomGetRotation(partInstance->physGeom[0]);
			partInstance->setCFrameNoSync(CoordinateFrame(
				Matrix3(physRotation[0],physRotation[1],physRotation[2],
						physRotation[4],physRotation[5],physRotation[6],
						physRotation[8],physRotation[9],physRotation[10]),
				Vector3(physPosition[0], physPosition[1], physPosition[2])));
		}
	}
}

void XplicitNgine::step(float stepSize)
{	
	dJointGroupEmpty(contactgroup);
	dSpaceCollide (physSpace,0,&collisionCallback);
	dWorldQuickStep(physWorld, stepSize);
}

void XplicitNgine::updateBody(PartInstance *partInstance)
{
	if(partInstance->physBody != NULL)
	{
		Vector3 position = partInstance->getCFrame().translation;

		dBodySetPosition(partInstance->physBody, 
			position[0],
			position[1],
			position[2]
		);
		dBodyEnable(partInstance->physBody);
		dGeomEnable(partInstance->physGeom[0]);

		Matrix3 g3dRot = partInstance->getCFrame().rotation;
		float rotation [12] = {	g3dRot[0][0], g3dRot[0][1], g3dRot[0][2], 0,
								g3dRot[1][0], g3dRot[1][1], g3dRot[1][2], 0,
								g3dRot[2][0], g3dRot[2][1], g3dRot[2][2], 0};

		dBodySetRotation(partInstance->physBody, rotation);
	}
}


dJointID XplicitNgine::createJoint(PartInstance *part1, PartInstance *part2)
{
	printf("XplicitNgine::createJoint called\n");
	if((part1->physBody != NULL) & (part2->physBody != NULL)){
		printf("creating a fixed joint\n");
		dJointID c = dJointCreateFixed(physWorld, 0);
		dJointAttach(c, part1->physBody, part2->physBody);
		dJointSetFixed(c);
		return c;
	}
	return NULL;
}

void XplicitNgine::destroyJoints(PartInstance *part)
{
	for(int i = 0; i < dBodyGetNumJoints(part->physBody); i++)
		dJointDestroy(dBodyGetJoint(part->physBody, i));
}