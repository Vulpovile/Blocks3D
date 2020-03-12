#pragma once
#include "PartInstance.h"
#pragma once

class Mouse
{
public:
	Mouse(void);
	~Mouse(void);
	int x, y;
	Instance * getTarget();
	Vector3 getPosition();
	bool isMouseOnScreen();
	bool isMouseDown();
	void setMouseDown(bool mouseDown);
private:
	bool mouseDown;
};
