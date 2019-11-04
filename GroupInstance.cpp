#include "GroupInstance.h"

GroupInstance::GroupInstance(void)
{
	PVInstance::PVInstance();
	className = "GroupInstance";
	listicon = 12;
}

GroupInstance::GroupInstance(const GroupInstance &oinst)
{
	PVInstance::PVInstance(oinst);
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
