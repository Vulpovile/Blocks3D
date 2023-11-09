#include "DataModelV3/WorkspaceInstance.h"

using namespace B3D;

WorkspaceInstance::WorkspaceInstance(void) : GroupInstance("Workspace")
{
	name = "Workspace";
	canDelete = false;
}

void WorkspaceInstance::clearChildren()
{
	partObjects.clear();
	Instance::clearChildren();
}

void WorkspaceInstance::zoomToExtents()
{
	//UGH TODO Implement Camera instance
//	g_usableApp->cameraController.zoomExtents();
}

WorkspaceInstance::~WorkspaceInstance(void)
{
}
