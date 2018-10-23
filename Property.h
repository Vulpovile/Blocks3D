#pragma once
#include <windows.h>
#include "propertyGrid.h"
class Property
{
public:
	void(*callbackFuncOnChange)(PROPGRIDITEM);
	PROPGRIDITEM * item;
	Property(PROPGRIDITEM * item, void(*onPropUpdate)(PROPGRIDITEM));
	~Property(void);
	void updateProperty(PROPGRIDITEM);
};
