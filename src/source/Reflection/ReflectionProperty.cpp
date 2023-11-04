#include "Reflection\ReflectionProperty.h"
using namespace B3D::Reflection;

template<typename T>
ReflectionProperty<T>::ReflectionProperty(T * value, ReflectionType type, ReflectionDataTable * containerTable, bool archivable = true, bool locked = false, bool propertyHidden = false)
{
	this->value = value;
	this->type = type;
	this->containerTable = containerTable;
	this->locked = locked;
	this->archivable = archivable;
	this->propertyHidden = propertyHidden;
}

template<typename T>
ReflectionProperty<T>::ReflectionProperty(void)
{
}

template<typename T>
ReflectionProperty<T>::~ReflectionProperty(void)
{
}
