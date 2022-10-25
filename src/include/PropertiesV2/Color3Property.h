#pragma once
#include "Property.h"

class Color3Property : public Property
{
public:
	typedef void (Instance::*instanceSetter)(Color3);
	~Color3Property(void){}; 
	Color3Property(LPSTR name, LPSTR desc, LPSTR catalog, Color3 value, Instance * owner, instanceSetter setterFunc)
	:Property(name, desc, catalog, &_value, owner) 
	{
		this->_value = value;
		this->setterFunc = setterFunc;
	}
	const void setValue(Color3 val){
		(_owner->*setterFunc)(val);
		_value = val;
	}
	PROPGRIDITEM getPropGridItem();
	void setProperty(LPPROPGRIDITEM &pItem);
private:
	Color3 _value;
	instanceSetter setterFunc;
};
