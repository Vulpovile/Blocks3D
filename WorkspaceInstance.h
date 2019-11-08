#pragma once
#include "GroupInstance.h"
#include <set>

class WorkspaceInstance :
	public GroupInstance
{
public:
	WorkspaceInstance(void);
	~WorkspaceInstance(void);
	void removeFromPVector(PVInstance *);
	void addToPVector(PVInstance *);
	std::vector<PVInstance*> __pvVector;
	std::vector<PVInstance*>* getPVVector();
};
