using namespace B3D::Reflection;

template<class T>
ReflectionProperty<T>::ReflectionProperty(T * value, ReflectionType type, ReflectionDataTable * containerTable)
{
	this->value = value;
	this->type = type;
	this->containerTable = containerTable;
	this->locked = locked;
	this->archivable = archivable;
	this->propertyHidden = propertyHidden;
}

template<class T>
ReflectionProperty<T>::ReflectionProperty(void)
{
}

template<class T>
ReflectionProperty<T>::~ReflectionProperty(void)
{
}