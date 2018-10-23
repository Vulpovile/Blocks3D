#include "Property.h"

Property::Property(std::string title, std::string propName, void * prop, void *(*getFunc)(void), void(*setFunc)(void *))
{
	this->title = title;
	this->propName = propName;
	this->prop = prop;
	this->getFunc = getFunc;
	this->setFunc = setFunc;
}

Property::~Property(void)
{
}


void Property::setProperty(void * newprop)
{
	this->setFunc(newprop);
}

void * Property::getProperty()
{
	return this->getFunc();
}