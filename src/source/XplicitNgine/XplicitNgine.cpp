#include "XplicitNgine/XplicitNgine.h"
#include "Globals.h"

#define SIDE (0.5f)
#define MASS (1.0)

// constraints
#define MAX_BODIES 65535
#define OBJ_DENSITY (5.0)
#define MAX_CONTACT_PER_BODY 4

XplicitNgine::XplicitNgine() 
{
	physWorld = dWorldCreate();
	physSpace = dHashSpaceCreate(0);
	contactgroup = dJointGroupCreate(0);

	dWorldSetGravity(physWorld, 0, -0.5, 0);
	//dGeomID ground_geom = dCreatePlane(physSpace, 0, 1, 0, 0);
}

XplicitNgine::~XplicitNgine() 
{
  dJointGroupDestroy (contactgroup);
  dSpaceDestroy (physSpace);
  dWorldDestroy (physWorld);
  dCloseODE();
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
			contact[i].surface.mode = dContactSlip1 | dContactSlip2 | dContactSoftERP | dContactSoftCFM | dContactApprox1;

			// Define contact surface properties
			contact[i].surface.mu = 0.5;
			contact[i].surface.slip1 = 0.0;
			contact[i].surface.slip2 = 0.0;
			contact[i].surface.soft_erp = 0.8;
			contact[i].surface.soft_cfm = 0.01;
			
			// Create joints
			dJointID c = dJointCreateContact(
				g_xplicitNgine->physWorld,
				g_xplicitNgine->contactgroup,
				contact+i
			);

			dJointAttach (c,b1,b2);
		}
	}
}

void XplicitNgine::createBody(PartInstance* partInstance)
{
	// calculate collisions
	dSpaceCollide (physSpace,0,&collisionCallback);
    
	if(partInstance->physBody == NULL) 
	{
		// init body
		partInstance->physBody = dBodyCreate(physWorld);
		
		// Create geom
		partInstance->physGeom[0] = dCreateBox(physSpace,
			partInstance->getSize()[0],
			partInstance->getSize()[1],
			partInstance->getSize()[2]
		);

		// Debug output
		dVector3 result;
		dGeomBoxGetLengths(partInstance->physGeom[0], result);
		printf("[XplicitNgine] Part Geom Size: %.1f, %.1f, %.1f\n", 
			result[0], 
			result[1], 
			result[2]
		);

		// Create rigid body
		printf("[XplicitNgine] Created Geom for PartInstance\n");
		dBodySetPosition(partInstance->physBody, 
			partInstance->getPosition()[0],
			partInstance->getPosition()[1],
			partInstance->getPosition()[2]
		);

		Matrix3 g3dRot = partInstance->getCFrame().rotation;
		float rotation [12] = {	g3dRot[0][0], g3dRot[0][1], g3dRot[0][2], 0,
								g3dRot[1][0], g3dRot[1][1], g3dRot[1][2], 0,
								g3dRot[2][0], g3dRot[2][1], g3dRot[2][2], 0};

		dBodySetRotation(partInstance->physBody, rotation);

		printf("[XplicitNgine] Created Body for PartInstance\n");
		
		if(!partInstance->anchored)
			dGeomSetBody(partInstance->physGeom[0], partInstance->physBody);

	} else {
		if(partInstance->anchored)
			return;

		const dReal* physPosition = dBodyGetPosition(partInstance->physBody);
		
		// TODO: Rotation code
		// Probably should be done AFTER we get physics KINDA working!!!
		const dReal* physRotation = dGeomGetRotation(partInstance->physGeom[0]);
		//partInstance->setPosition(Vector3(physPosition[0], physPosition[1], physPosition[2]));
		partInstance->setCFrame(CoordinateFrame(
			Matrix3(physRotation[0],physRotation[1],physRotation[2],
					physRotation[4],physRotation[5],physRotation[6],
					physRotation[8],physRotation[9],physRotation[10]),
			Vector3(physPosition[0], physPosition[1], physPosition[2])));
	}

	dWorldQuickStep(physWorld,0.05);
	dJointGroupEmpty(contactgroup);
}