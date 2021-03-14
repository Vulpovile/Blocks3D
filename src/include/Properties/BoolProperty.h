#pragma once
#include "Property.h"
class BoolProperty : public Property<bool>
{
public:
	BoolProperty(std::string name, bool& value, Instance& owner)
	{
		Property<bool>(name, value, owner);
	}
	~BoolProperty(void);
	PROPGRIDITEM getPropGridItem();
};
