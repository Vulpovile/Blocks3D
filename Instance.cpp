#include <G3DAll.h>
#include "Instance.h"

std::string name;
Instance* parent;
static const int BASE_INSTANCE = 0;
static const int PHYSICAL_INSTANCE = 1;
static const int type = BASE_INSTANCE;

Instance::Instance(void)
{
	name = "Default Game Instance";
}

Instance::~Instance(void)
{
	name = "Default Game Instance";
}
int getType()
{
	return type;
}



