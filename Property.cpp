#include "Property.h"

Property::Property(PROPGRIDITEM * item, void(*onPropUpdate)(PROPGRIDITEM))
{
	this->callbackFuncOnChange = onPropUpdate;
	this->item = item;
}

Property::~Property(void)
{
	delete item;
}

void Property::updateProperty(PROPGRIDITEM item)
{
	callbackFuncOnChange(item);
}



