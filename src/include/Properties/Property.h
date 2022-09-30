#pragma once
#include "DataModelV2/Instance.h"
#include <string>
class Instance;

template <typename T> 
class Property
{
public:
	Property(std::string name, T& value, Instance& owner)
	{
		_value = value;
		_owner = owner;
	}
	~Property(void);
	const T getValue()
	{
		return _value;
	}
	const void setValue(T val)
	{
		_value = val;
	}
	virtual PROPGRIDITEM getPropGridItem();
	void setProperty(LPPROPGRIDITEM item);
protected:
	Instance* _owner;
	std::string _name;
	T* _value;
};
