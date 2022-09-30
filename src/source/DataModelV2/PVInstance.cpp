#include "DataModelV2/PVInstance.h"

PVInstance::PVInstance(void)
{
	Instance::Instance();
	nameShown = false;
	controllerFlagShown = true;
	className = "PVInstance";
	listicon = 0;
	controller = (Enum::Controller::Value)0;
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

static TCHAR* enumStr(int controller)
{
	switch(controller)
	{
		case Enum::Controller::None:
			return "None";
		case Enum::Controller::KeyboardLeft:
			return "KeyboardLeft";
		case Enum::Controller::KeyboardRight:
			return "KeyboardRight";
		case Enum::Controller::Joypad1:
			return "Joypad1";
		case Enum::Controller::Joypad2:
			return "Joypad2";
		case Enum::Controller::Chase:
			return "Joypad1";
		case Enum::Controller::Flee:
			return "Joypad2";
	}
	return "None";
}

static Enum::Controller::Value strEnum(TCHAR * tval)
{
	if(strcmp(tval, "KeyboardLeft") == 0)
		return Enum::Controller::KeyboardLeft;
	if(strcmp(tval, "KeyboardRight") == 0)
		return Enum::Controller::KeyboardRight;
	if(strcmp(tval, "Joypad1") == 0)
		return Enum::Controller::Joypad1;
	if(strcmp(tval, "Joypad2") == 0)
		return Enum::Controller::Joypad2;
	if(strcmp(tval, "Chase") == 0)
		return Enum::Controller::Chase;
	if(strcmp(tval, "Flee") == 0)
		return Enum::Controller::Flee;
	return Enum::Controller::None;
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
	properties.push_back(createPGI(
		"Item",
		"ControllerFlagShown",
		"This chooses whether the item's ControllerFlag is shown",
		controllerFlagShown,
		PIT_CHECK));
	properties.push_back(createPGI(
		"Behaviour",
		"Controller",
		"This chooses what type of controller is used",
		(LPARAM)enumStr(controller),
		PIT_COMBO,
		TEXT("None\0KeyboardRight\0KeyboardLeft\0Joypad1\0Joypad2\0Chase\0Flee")
		));

	return properties;
}
void PVInstance::PropUpdate(LPPROPGRIDITEM &pItem)
{
	if(strcmp(pItem->lpszPropName, "NameShown") == 0)
	{
		nameShown = pItem->lpCurValue == TRUE;
	}
	if(strcmp(pItem->lpszPropName, "ControllerFlagShown") == 0)
	{
		controllerFlagShown = pItem->lpCurValue == TRUE;
	}
	if(strcmp(pItem->lpszPropName, "Controller") == 0)
	{
		controller = strEnum((TCHAR *)pItem->lpCurValue);
	}
	else Instance::PropUpdate(pItem);
}
