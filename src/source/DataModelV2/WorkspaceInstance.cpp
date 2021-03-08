#include "DataModelV2/WorkspaceInstance.h"


WorkspaceInstance::WorkspaceInstance(void)
{
	GroupInstance::GroupInstance();
	name = "Workspace";
	className = "Workspace";
	canDelete = false;
}

WorkspaceInstance::~WorkspaceInstance(void)
{
}
