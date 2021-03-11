#pragma once
#include "propertyGrid.h"
template <typename T> 
class Property
{
public:
	Property(std::string name, T& value)
	{
		value = t;
	}
	~Property(void);
	T getValue();
	void setValue(T);
	PROPGRIDITEM getPropGridItem();
	void setProperty(LPPROPGRIDITEM item);
protected:
	std::string name;
	T* value;
};
