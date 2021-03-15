#pragma once
#include "tool.h"
#include "Enum.h"

class SurfaceTool :
	public Tool
{
public:
	SurfaceTool(Enum::SurfaceType::Value surface, int extraParam); //OnSelect?
	~SurfaceTool(void); //OnDeselect?
	void onButton1MouseDown(Mouse);
	void onButton1MouseUp(Mouse);
	void onMouseMoved(Mouse mouse);
	void onSelect(Mouse mouse); 
	void onKeyDown(int key);
	void onKeyUp(int key);
private:
	Enum::SurfaceType::Value surface;
	int param;
};
