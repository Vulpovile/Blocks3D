#pragma once
#include "tool.h"

class ArrowTool :
	public Tool
{
public:
	ArrowTool(void); //OnSelect?
	~ArrowTool(void); //OnDeselect?
	virtual void onButton1MouseDown(Mouse);
	virtual void onMouseMoved(Mouse mouse);
	virtual void onSelect(Mouse mouse); //Why is this not being called
};
