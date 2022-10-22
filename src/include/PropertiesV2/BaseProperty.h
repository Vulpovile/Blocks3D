#pragma once
#include <string>
#include <G3DAll.h>
#include "propertyGrid.h"
class Instance;

/**
	DO NOT INHERIT FROM THIS CLASS!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	INHERIT FROM PROPERTY INSTEAD
*/
class BaseProperty
{
public:
	BaseProperty(LPSTR name, LPSTR desc, LPSTR catalog, Instance * owner) {
		_name = name;
		_desc = desc;
		_owner = owner;
		_catalog = catalog;
	}
	~BaseProperty(void){};

	virtual PROPGRIDITEM getPropGridItem();
	virtual void setProperty(LPPROPGRIDITEM &pItem);
protected:
	Instance* _owner;
	LPSTR _name;
	LPSTR _desc;
	LPSTR _catalog;
};
