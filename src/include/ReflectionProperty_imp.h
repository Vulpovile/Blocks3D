using namespace B3D::Reflection;

template<class T>
ReflectionProperty<T>::ReflectionProperty(std::string key, T * value, ReflectionType type, ReflectionDataTable * containerTable)
{
	this->value = value;
	this->type = type;
	this->containerTable = containerTable;
	this->locked = locked;
	this->archivable = archivable;
	this->propertyHidden = propertyHidden;
	containerTable->mapProperty(key, (ReflectionProperty<void*>*)this);
}

template<class T>
ReflectionProperty<T>::ReflectionProperty(void)
{
}

template<class T>
ReflectionProperty<T>::~ReflectionProperty(void)
{
}

template<class T>
void ReflectionProperty<T>::dispose()
{
	delete value;
	value = NULL;
}