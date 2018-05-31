#pragma once
#include "instance.h"
#include "WorkspaceInstance.h"

class DataModelInstance :
	public Instance
{
public:
	DataModelInstance(void);
	~DataModelInstance(void);
	WorkspaceInstance* getWorkspace();
	Instance* getGuiRoot();
	float mousex;
	float mousey;
	bool mouseButton1Down;
};
