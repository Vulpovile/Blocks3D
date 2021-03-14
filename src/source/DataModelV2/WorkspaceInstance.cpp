#include "DataModelV2/WorkspaceInstance.h"


WorkspaceInstance::WorkspaceInstance(void)
{
	GroupInstance::GroupInstance();
	name = "Workspace";
	className = "Workspace";
	canDelete = false;
}

void WorkspaceInstance::clearChildren()
{
	partObjects.clear();
	Instance::clearChildren();
}

WorkspaceInstance::~WorkspaceInstance(void)
{
}
