#pragma once
#include "instance.h"
#pragma once
#include "ButtonListener.h"
class BaseButtonInstance : public Instance
{
public:
	BaseButtonInstance(void);
	virtual ~BaseButtonInstance(void);
	virtual void drawObj(RenderDevice* rd, Vector2 mousePos, bool mouseDown);
	virtual bool mouseInButton(float, float, RenderDevice* rd);
	virtual void onMouseClick();
	bool floatBottom;
	bool floatRight;
	bool floatCenter;
	bool disabled;
protected:
	bool mouseInArea(float, float, float, float, float, float);
	class ButtonListener* listener;
};
