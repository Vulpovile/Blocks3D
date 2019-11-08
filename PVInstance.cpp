#include "PVInstance.h"
#include "WorkspaceInstance.h"

PVInstance::PVInstance(void)
{
	Instance::Instance();
	nameShown = false;
	className = "PVInstance";
	listicon = 0;
}

PVInstance::PVInstance(const PVInstance &oinst)
{
	Instance::Instance(oinst);
}

PVInstance::~PVInstance(void)
{
}

void PVInstance::postRender(RenderDevice* rd)
{
}

void PVInstance::render(RenderDevice* rd)
{
}

void PVInstance::setParent(Instance* newParent)
{
	if(parent != NULL)
	{
		Instance* workspace = parent;
		while(workspace != NULL)
		{
			if(WorkspaceInstance* wsp = dynamic_cast<WorkspaceInstance*>(workspace))
			{
				wsp->removeFromPVector(this);
				break;
			}
			workspace = workspace->getParent();
		}
		parent->removeChild(this);
	}
	parent = newParent;
	if(newParent != NULL)
	{
		Instance* workspace = parent;
		while(workspace != NULL)
		{
			if(WorkspaceInstance* wsp = dynamic_cast<WorkspaceInstance*>(workspace))
			{
				wsp->addToPVector(this);
				break;
			}
			workspace = workspace->getParent();
		}
		newParent->addChild(this);
	}
}

std::vector<PROPGRIDITEM> PVInstance::getProperties()
{
	std::vector<PROPGRIDITEM> properties = Instance::getProperties();
	properties.push_back(createPGI(
		"Item",
		"NameShown",
		"This chooses whether the item name is shown",
		nameShown,
		PIT_CHECK));
	return properties;
}
void PVInstance::PropUpdate(LPPROPGRIDITEM &pItem)
{
	if(strcmp(pItem->lpszPropName, "NameShown") == 0)
	{
		nameShown = (bool)pItem->lpCurValue;
	}
	else Instance::PropUpdate(pItem);
}
