#define WINVER	0x0400
#include <G3DAll.h>
#include "Instance.h"

std::string name;
Instance* parent;
static std::string className = "DataModel";

Instance::Instance(void)
{
	name = "Default Game Instance";
	className = "DataModel";
}

Instance::~Instance(void)
{
	name = "Default Game Instance";
}




