#pragma once
#include "GroupInstance.h"

class WorkspaceInstance :
	public GroupInstance
{
public:
	float timer;
	int score;
	WorkspaceInstance(void);
	~WorkspaceInstance(void);
};
