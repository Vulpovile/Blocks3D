#include "GroupInstance.h"

GroupInstance::GroupInstance(void)
{
	PVInstance::PVInstance();
	name = "Model";
	className = "GroupInstance";
	listicon = 12;
}

GroupInstance::GroupInstance(const GroupInstance &oinst)
{
	PVInstance::PVInstance(oinst);
	name = "Model";
	className = "GroupInstance";
	listicon = 12;
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