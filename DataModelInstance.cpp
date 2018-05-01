#include "DataModelInstance.h"


WorkspaceInstance* workspace;

DataModelInstance::DataModelInstance(void)
{
	workspace = new WorkspaceInstance();
	children.push_back(workspace);
	className = "DataModel";
}

DataModelInstance::~DataModelInstance(void)
{
}

WorkspaceInstance* DataModelInstance::getWorkspace()
{
	return workspace;
}
