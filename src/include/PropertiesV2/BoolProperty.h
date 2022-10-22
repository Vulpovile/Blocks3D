#pragma once
#include "Property.h"

class BoolProperty : public Property<bool>
{
public:
	typedef void (Instance::*instanceSetter)(bool); 
	//Win32 why
	~BoolProperty(void){};
	BoolProperty(LPSTR name, LPSTR desc, LPSTR catalog, bool value, Instance * owner, instanceSetter setterFunc)
	:Property(name, desc, catalog, value, owner) 
	{
		this->setterFunc = setterFunc;
	}
	const void setValue(bool val){
		(_owner->*setterFunc)(val);
		_value = val;
	}
	PROPGRIDITEM getPropGridItem();
	void setProperty(LPPROPGRIDITEM &pItem);
private:
	instanceSetter setterFunc;
};
