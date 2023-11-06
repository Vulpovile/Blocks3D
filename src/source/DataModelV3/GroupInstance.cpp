#include "DataModelV3/GroupInstance.h"

using namespace B3D;


GroupInstance::GroupInstance(std::string className)
{
	PVInstance::PVInstance(className);
	name = "Model";
	primaryPart = NULL;
}

GroupInstance::GroupInstance(void)
{
	GroupInstance::GroupInstance("Model");
}

GroupInstance::~GroupInstance(void)
{
}

std::vector<Instance *> GroupInstance::unGroup()
{
	while(children.size() > 0)
	{
		children[0]->setParent(parent);
	}
	return std::vector<Instance *>();
}

void GroupInstance::render(RenderDevice * rd)
{
	Instance::render(rd);
	//Controllerflag!
	if(primaryPart != NULL && controllerFlagShown.getValue() && getControllerColor(controller.getValue()) != Color3::gray())
	{
			rd->disableLighting();
			Vector3 vec = Vector3(0,0,0);
			Vector3 up = Vector3(0,8,0);
			rd->setColor(getControllerColor(controller.getValue()));
			rd->setObjectToWorldMatrix(primaryPart->getCFrame());
			rd->beforePrimitive();

				glBegin(GL_LINES);
				glVertex3f(vec.x, vec.y, vec.z);
				glVertex3f(up.x, up.y, up.z);
				glEnd();

				glBegin( GL_TRIANGLES );
				glVertex3f(up.x, up.y-2, up.z);
				glVertex3f(up.x, up.y-1, up.z-2);
				glVertex3f(up.x, up.y, up.z);
				
				glVertex3f(up.x, up.y, up.z);
				glVertex3f(up.x, up.y-1, up.z-2);
				glVertex3f(up.x, up.y-2, up.z);

				glEnd();
			rd->afterPrimitive();
			rd->setColor(Color3::white());
			rd->enableLighting();
	}
}