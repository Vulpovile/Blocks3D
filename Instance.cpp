#include <G3DAll.h>
#include "Instance.h"

std::string name;
Instance* parent;
static const std::string className = "Instance";

Instance::Instance(void)
{
	name = "Default Game Instance";
}

Instance::~Instance(void)
{
	name = "Default Game Instance";
}




