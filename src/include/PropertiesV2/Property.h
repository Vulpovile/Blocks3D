#pragma once
#include <G3DAll.h>
#include "propertyGrid.h"

class Instance;

class Property
{
public:
	Property(LPSTR name, LPSTR desc, LPSTR catalog, Instance * owner){
		_name = name;
		_desc = desc;
		_catalog = catalog;
		_owner = owner;
	}
	Property(LPSTR name, LPSTR desc, LPSTR catalog, void* value, Instance * owner){
		_name = name;
		_desc = desc;
		_catalog = catalog;
		_owner = owner;
		_value = value;
	}
	~Property(void){}
	const void* getValue() {
		return _value;
	}
	virtual PROPGRIDITEM getPropGridItem();
	virtual void setProperty(LPPROPGRIDITEM &pItem);
protected:
	Instance* _owner;
	LPSTR _name;
	LPSTR _desc;
	LPSTR _catalog;
	void* _value;
};
