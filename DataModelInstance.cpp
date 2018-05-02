#include "DataModelInstance.h"


WorkspaceInstance* workspace;
Instance* guiRoot;

DataModelInstance::DataModelInstance(void)
{
	workspace = new WorkspaceInstance();
	guiRoot = new Instance();
	children.push_back(workspace);
	className = "dataModel";
}

DataModelInstance::~DataModelInstance(void)
{
}

WorkspaceInstance* DataModelInstance::getWorkspace()
{
	return workspace;
}

Instance* DataModelInstance::getGuiRoot()
{
	return guiRoot;
}
