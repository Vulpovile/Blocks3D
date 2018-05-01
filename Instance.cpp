#define WINVER	0x0400
#include <G3DAll.h>
#include "Instance.h"

std::string name;
Instance* parent;
std::vector<Instance* > children;
static std::string className = "BaseInstance";

Instance::Instance(void)
{
	name = "Default Game Instance";
	className = "BaseInstance";
}

Instance::~Instance(void)
{
	name = "Default Game Instance";
}

std::string Instance::getClassName()
{
	return className;
}




