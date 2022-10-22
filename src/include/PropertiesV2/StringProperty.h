#pragma once
#include "Property.h"

class StringProperty : public Property<std::string>
{
public:
	typedef void (Instance::*instanceSetter)(std::string);
	~StringProperty(void){}; 
	StringProperty(LPSTR name, LPSTR desc, LPSTR catalog, std::string value, Instance * owner, instanceSetter setterFunc)
	:Property(name, desc, catalog, value, owner) 
	{
		this->setterFunc = setterFunc;
	}
	const void setValue(std::string val){
		(_owner->*setterFunc)(val);
		_value = val;
	}
	PROPGRIDITEM getPropGridItem();
	void setProperty(LPPROPGRIDITEM &pItem);
private:
	instanceSetter setterFunc;
};
