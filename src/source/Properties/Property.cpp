#include "Properties/Property.h"

template <typename T>
void Property<T>::setProperty(LPPROPGRIDITEM item)
{
	_owner->propertiesChanged();
}