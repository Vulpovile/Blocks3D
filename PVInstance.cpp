#include "PVInstance.h"

PVInstance::PVInstance(void)
{
	Instance::Instance();
	className = "PVInstance";
}

PVInstance::PVInstance(const PVInstance &oinst)
{
	Instance::Instance(oinst);
}

PVInstance::~PVInstance(void)
{
}

std::vector<PROPGRIDITEM> PVInstance::getProperties()
{
	std::vector<PROPGRIDITEM> properties = Instance::getProperties();
	return properties;
}
void PVInstance::PropUpdate(LPPROPGRIDITEM &pItem)
{
	Instance::PropUpdate(pItem);
}
