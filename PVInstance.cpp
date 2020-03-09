#include "PVInstance.h"

PVInstance::PVInstance(void)
{
	Instance::Instance();
	nameShown = false;
	controllerFlagShown = true;
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
