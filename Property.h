#pragma once
#include <windows.h>
#include "propertyGrid.h"
class Property
{
public:
	PROPGRIDITEM item;
	DWORD addr;
	Property(PROPGRIDITEM item, DWORD addr);
	~Property(void);
};
