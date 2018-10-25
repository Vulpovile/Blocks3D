#include "WorkspaceInstance.h"


WorkspaceInstance::WorkspaceInstance(void)
{
	GroupInstance::GroupInstance();
	name = "Instance";
	className = "Level";
	timer = 60.0F;
	score = 0;
	canDelete = false;
}

WorkspaceInstance::~WorkspaceInstance(void)
{
}
