#pragma once
#include "GroupInstance.h"
#include "PartInstance.h"

class WorkspaceInstance :
	public GroupInstance
{
public:
	WorkspaceInstance(void);
	~WorkspaceInstance(void);
	void clearChildren();
	std::vector<PartInstance *> partObjects;
};
