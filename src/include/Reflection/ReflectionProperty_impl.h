using namespace B3D::Reflection;

template<class T>
ReflectionProperty<T>::ReflectionProperty(std::string key, T * value, ReflectionType type, ReflectionDataTable * containerTable, void* extData = NULL, bool archivable = true, bool locked = false, bool propertyHidden = false)
{
	this->value = value;
	this->type = type;
	this->containerTable = containerTable;
	this->locked = locked;
	this->archivable = archivable;
	this->propertyHidden = propertyHidden;
	this->extData = extData;
	containerTable->mapProperty(key, (ReflectionProperty<void*>*)this);
}

template<class T>
ReflectionProperty<T>::ReflectionProperty(std::string key, T value, ReflectionType type, ReflectionDataTable * containerTable, void* extData = NULL, bool archivable = true, bool locked = false, bool propertyHidden = false)
{
	this->value = new T(value);
	this->type = type;
	this->containerTable = containerTable;
	this->locked = locked;
	this->archivable = archivable;
	this->propertyHidden = propertyHidden;
	this->extData = extData;
	containerTable->mapProperty(key, (ReflectionProperty<void*>*)this);
}

template<class T>
ReflectionProperty<T>::ReflectionProperty(void)
{
}

template<class T>
ReflectionProperty<T>::~ReflectionProperty(void)
{
	dispose();
}

template<class T>
void ReflectionProperty<T>::dispose()
{
	delete value;
	value = NULL;
	if(this->extData != NULL)
	{
		delete extData;
		extData = NULL;
	}
}

template<class T>
T ReflectionProperty<T>::getValueClone()
{
	return T(value);
}

template<class T>
T ReflectionProperty<T>::getValue()
{
	return *value;
}

template<class T>
T* ReflectionProperty<T>::getValuePtr()
{
	return value;
}

template<class T>
void ReflectionProperty<T>::setValue(T value){
	this=value;
}