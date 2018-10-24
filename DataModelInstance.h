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
	WorkspaceInstance* getWorkspace();
	WorkspaceInstance* workspace;
	Instance* guiRoot;
	std::string message;
	bool showMessage;
	G3D::GFontRef font;
	Instance* getGuiRoot();
	float mousex;
	float mousey;
	Vector2 getMousePos();
	void setMousePos(int x,int y);
	void setMousePos(Vector2 pos);
	bool mouseButton1Down;
};
