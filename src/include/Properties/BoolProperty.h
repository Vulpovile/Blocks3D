#pragma once
#include "Property.h"
#pragma once
class BoolProperty : public Property<bool>
{
public:
	template <typename T> 
	BoolProperty(std::string name, bool& value)
	{
		Property(name, (T)value);
	}
	~BoolProperty(void);
};
