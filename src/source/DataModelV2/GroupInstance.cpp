#include "DataModelV2/GroupInstance.h"

GroupInstance::GroupInstance(void)
{
	PVInstance::PVInstance();
	name = "Model";
	className = "GroupInstance";
	listicon = 12;
	primaryPart = NULL;
}

GroupInstance::GroupInstance(const GroupInstance &oinst)
{
	PVInstance::PVInstance(oinst);
	name = "Model";
	className = "GroupInstance";
	listicon = 12;
	primaryPart = NULL;
}

GroupInstance::~GroupInstance(void)
{
}

std::vector<PROPGRIDITEM> GroupInstance::getProperties()
{
	std::vector<PROPGRIDITEM> properties = PVInstance::getProperties();
	return properties;
}
void GroupInstance::PropUpdate(LPPROPGRIDITEM &pItem)
{
	PVInstance::PropUpdate(pItem);
}

std::vector<Instance *> GroupInstance::unGroup()
{
	std::vector<Instance *> child;
	while(children.size() > 0)
	{
		child.push_back(children[0]);
		children[0]->setParent(parent);
	}
	return child;
}

void GroupInstance::render(RenderDevice * rd)
{
	Instance::render(rd);
	if(primaryPart != NULL && controllerFlagShown && getControllerColor(controller) != Color3::gray())
	{
			rd->disableLighting();
			Vector3 vec = Vector3(0,0,0);
			Vector3 up = Vector3(0,8,0);
			rd->setColor(getControllerColor(controller));
			rd->setObjectToWorldMatrix(primaryPart->cFrame);
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