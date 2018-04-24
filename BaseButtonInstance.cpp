#include "BaseButtonInstance.h"

bool floatBottom;
bool floatRight;
bool floatCenter;
bool disabled;

BaseButtonInstance::BaseButtonInstance(void)
{
}

BaseButtonInstance::~BaseButtonInstance(void)
{
}

void BaseButtonInstance::drawObj(RenderDevice* rd, Vector2 mousePos, bool mouseDown){}

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