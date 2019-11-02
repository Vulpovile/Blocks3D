#include "WorkspaceInstance.h"


WorkspaceInstance::WorkspaceInstance(void)
{
	GroupInstance::GroupInstance();
	name = "Workspace";
	className = "Workspace";
	canDelete = false;
	listicon = 8;
}

WorkspaceInstance::~WorkspaceInstance(void)
{
}
