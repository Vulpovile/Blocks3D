#include "Reflection/ReflectionDataTable.h"

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
}

std::string ReflectionDataTable::getClassName(void)
{
	return className;
}