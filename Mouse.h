#pragma once
#include "PartInstance.h"
#pragma once
#include "WorkspaceInstance.h"

#pragma once

class Mouse
{
public:
	Mouse();
	~Mouse(void);
	int x, y;
	int oldx, oldy;
	PartInstance * getTarget();
	Vector3 getPosition(std::vector<Instance *> ignore = std::vector<Instance *>());
	bool isMouseOnScreen();
	bool isMouseDown();
	void setMouseDown(bool mouseDown);
private:
	bool mouseDown;
};
