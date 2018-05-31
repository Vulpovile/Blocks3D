#pragma once
#include "instance.h"
#include "WorkspaceInstance.h"

class DataModelInstance :
	public Instance
{
public:
	DataModelInstance(void);
	~DataModelInstance(void);
	void setMessage(std::string);
	void clearMessage();
	void drawMessage(RenderDevice*);
	GFontRef font;
	WorkspaceInstance* getWorkspace();
	Instance* getGuiRoot();
	float mousex;
	float mousey;
	bool mouseButton1Down;
};
