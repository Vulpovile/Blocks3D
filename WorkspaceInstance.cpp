#include "WorkspaceInstance.h"


WorkspaceInstance::WorkspaceInstance(void)
{
	Instance::Instance();
	name = "Instance";
	className = "Level";
	timer = 60.0F;
	score = 0;
}

WorkspaceInstance::~WorkspaceInstance(void)
{
}
