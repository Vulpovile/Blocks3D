#pragma once
#include "tool.h"

class ArrowTool :
	public Tool
{
public:
	ArrowTool(void); //OnSelect?
	~ArrowTool(void); //OnDeselect?
	virtual void onButton1MouseDown(Mouse);
	virtual void onButton1MouseUp(Mouse);
	virtual void onMouseMoved(Mouse mouse);
	virtual void onSelect(Mouse mouse); 
	virtual void onKeyDown(int key);
	virtual void onKeyUp(int key);
private:
	bool lctrlDown;
	bool rctrlDown;
	int mouseDownStartx;
	int mouseDownStarty;
	bool dragging;
	bool mouseDown;
};
