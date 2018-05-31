#include "DataModelInstance.h"


WorkspaceInstance* workspace;
Instance* guiRoot;
float mousex;
float mousey;
bool mouseButton1Down;


DataModelInstance::DataModelInstance(void)
{
	workspace = new WorkspaceInstance();
	guiRoot = new Instance();
	children.push_back(workspace);
	className = "dataModel";
	mousex = 0;
	mousey = 0;
	mouseButton1Down = false;
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
