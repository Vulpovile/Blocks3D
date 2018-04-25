#include "BaseButtonInstance.h"

bool floatBottom = false;
bool floatRight = false;
bool floatCenter = false;
bool disabled = false;
bool selected = false;
ButtonListener* listener = NULL;

BaseButtonInstance::BaseButtonInstance(void)
{
	listener = NULL;
}

BaseButtonInstance::~BaseButtonInstance(void)
{
	delete listener;
}

void BaseButtonInstance::setButtonListener(ButtonListener* buttonListener)
{
	listener = buttonListener;
}

void BaseButtonInstance::drawObj(RenderDevice* rd, Vector2 mousePos, bool mouseDown){}

bool BaseButtonInstance::mouseInButton(float mousex, float mousey, RenderDevice* rd){return false;}

void BaseButtonInstance::onMouseClick()
{
	if(listener != NULL)
	{
		listener->onButton1MouseClick(this);
		
	}
}


bool BaseButtonInstance::mouseInArea(float point1x, float point1y, float point2x, float point2y, float mousex, float mousey)
{
	

	if(mousex >= point1x && mousey >= point1y)
	{
		if(mousex < point2x && mousey < point2y)
		{
			return true;
		}
	}
	return false;
}