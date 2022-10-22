#pragma once
#include "PropertiesV2/BaseProperty.h"

template <typename T>
class Property : public BaseProperty
{
public:
	Property(LPSTR name, LPSTR desc, LPSTR catalog, T value, Instance * owner)
	:BaseProperty(name, desc, catalog, owner)
	{
		_value = value;
	}
	~Property(void){};
	const T getValue() {
		return _value;
	}
	virtual PROPGRIDITEM getPropGridItem();
	virtual void setProperty(LPPROPGRIDITEM &pItem);
protected:
	T _value;
};
