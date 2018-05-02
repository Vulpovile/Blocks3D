#pragma once
#include "instance.h"

class WorkspaceInstance :
	public Instance
{
public:
	float timer;
	int score;
	WorkspaceInstance(void);
	~WorkspaceInstance(void);
};
