#pragma once
#include "instance.h"

class BaseButtonInstance : public Instance
{
public:
	BaseButtonInstance(void);
	~BaseButtonInstance(void);
	virtual void drawObj(RenderDevice* rd, Vector2 mousePos, bool mouseDown);
	bool floatBottom;
	bool floatRight;
	bool floatCenter;
protected:
	bool mouseInArea(float, float, float, float, float, float);
};
