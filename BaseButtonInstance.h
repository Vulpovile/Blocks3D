#pragma once
#include "instance.h"
#pragma once
#include "ButtonListener.h"
class ButtonListener;
class BaseButtonInstance : public Instance
{
public:
	BaseButtonInstance(void);
	virtual ~BaseButtonInstance(void);
	virtual void render(RenderDevice* rd);
	virtual void drawObj(RenderDevice* rd, Vector2 mousePos, bool mouseDown);
	virtual bool mouseInButton(float, float, RenderDevice* rd);
	virtual void onMouseClick();
	void setButtonListener(ButtonListener*);
	bool floatBottom;
	bool floatRight;
	bool floatCenter;
	volatile bool disabled;
	bool selected;
protected:
	bool mouseInArea(float, float, float, float, float, float);
	class ButtonListener* listener;
};
