#include "WorkspaceInstance.h"


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

void WorkspaceInstance::removeFromPVector(PVInstance * instance)
{
	__pvVector.erase(std::remove(__pvVector.begin(), __pvVector.end(), instance), __pvVector.end());
}
void WorkspaceInstance::addToPVector(PVInstance * instance)
{
	__pvVector.push_back(instance);
}