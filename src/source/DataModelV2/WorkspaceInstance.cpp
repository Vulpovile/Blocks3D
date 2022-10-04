#include "DataModelV2/WorkspaceInstance.h"
#include "Globals.h"
#include "Application.h"

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

void WorkspaceInstance::zoomToExtents()
{
	g_usableApp->cameraController.zoomExtents();
}

WorkspaceInstance::~WorkspaceInstance(void)
{
}
