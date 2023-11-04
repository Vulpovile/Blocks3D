#pragma once
#include "ArrowTool.h"

class DraggerTool :
	public ArrowTool
{
public:
	DraggerTool(void);
	~DraggerTool(void);
	void onButton1MouseDown(Mouse);
	void onButton1MouseUp(Mouse);
	void onMouseMoved(Mouse mouse);
	void onSelect(Mouse mouse); 
	void onKeyDown(int key);
	void onKeyUp(int key);
	void render(RenderDevice * rd, Mouse mouse);
private:
	void createHandles();
	void grabHandle(Mouse mouse);
	bool hasHandles;
	int handleGrabbed;
	Vector3 center;
	Vector3 centerOffset;
	Sphere handles[6];
};
