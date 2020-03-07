#pragma once
#include "GroupInstance.h"

class WorkspaceInstance :
	public GroupInstance
{
public:
	WorkspaceInstance(void);
	~WorkspaceInstance(void);
	std::vector<PVInstance *> physicalObjects;
};
