#pragma once
#include "GroupInstance.h"
#include "PartInstance.h"

class WorkspaceInstance :
	public GroupInstance
{
public:
	WorkspaceInstance(void);
	~WorkspaceInstance(void);
	std::vector<PartInstance *> partObjects;
};
