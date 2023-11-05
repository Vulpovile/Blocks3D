#include "DataModelV3/PVInstance.h"
using namespace B3D;

PVInstance::PVInstance(std::string className)
{
	Instance::Instance(className);

	nameShown = Reflection::ReflectionProperty<bool>("NameShown", false, TYPE_BOOLEAN, this->dataTable);
	controllerFlagShown = Reflection::ReflectionProperty<bool>("ControllerFlagShown", true, TYPE_BOOLEAN, this->dataTable);
	controller = Reflection::ReflectionProperty<Enum::Controller::Value>("Controller", Enum::Controller::None, TYPE_ENUM, this->dataTable,
		(void*)new EnumMeta(Enum::Controller::LENGTH, Enum::Controller::STR_TABLE));
	cFrame = Reflection::ReflectionProperty<CoordinateFrame>("CFrame", CoordinateFrame(), TYPE_CFRAME, this->dataTable);

}

PVInstance::PVInstance(void)
{
	PVInstance::PVInstance("PVInstance");
}

PVInstance::~PVInstance(void)
{
}

void PVInstance::postRender(RenderDevice* rd)
{
}
