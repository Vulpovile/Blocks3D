#pragma once
#include "Property.h"
#include <sstream>

class Vector3Property : public Property
{
public:
	typedef void (Instance::*instanceSetter)(Vector3);
	~Vector3Property(void){}; 
	Vector3Property(LPSTR name, LPSTR desc, LPSTR catalog, Vector3 value, Instance * owner, instanceSetter setterFunc)
	:Property(name, desc, catalog, &_value, owner) 
	{
		this->_value = value;
		this->setterFunc = setterFunc;
	}
	const void setValue(Vector3 val){
		(_owner->*setterFunc)(val);
		_value = val;
	}
	PROPGRIDITEM getPropGridItem();
	void setProperty(LPPROPGRIDITEM &pItem);
private:
	Vector3 _value;
	std::string stringRep;
	instanceSetter setterFunc;
};
