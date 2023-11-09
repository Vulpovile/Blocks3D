#include "Reflection/ReflectionDataTable.h"
#include "DataModelV3/Instance.h"

using namespace B3D::Reflection;

ReflectionDataTable::ReflectionDataTable(B3D::Instance * parentInstance, std::string className)
{
	this->parentInstance = parentInstance;
	this->className = className;
}

ReflectionDataTable::ReflectionDataTable(void)
{
}

ReflectionDataTable::~ReflectionDataTable(void)
{
	std::map<std::string, ReflectionProperty<void*>*>::iterator it;
	for (it = propertyTable.begin(); it != propertyTable.end(); it++)
	{
		it->second->dispose();
	}
}

std::string ReflectionDataTable::getClassName(void)
{
	return className;
}

void ReflectionDataTable::notify(ReflectionProperty<void*>* prop)
{
	parentInstance->reflectionNotify(prop);
}

void ReflectionDataTable::mapProperty(std::string key, ReflectionProperty<void*>* prop)
{
	if(propertyTable.find(key) != propertyTable.end())
	{
		throw std::string("Reflection error: Key") + key + std::string("already defined!");
	}
	propertyTable[key] = prop;
}