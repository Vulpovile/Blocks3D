#include "BaseButtonInstance.h"
#include "Globals.h"


ButtonListener* listener = NULL;

BaseButtonInstance::BaseButtonInstance(void)
{
	Instance::Instance();
	listener = NULL;
}

void BaseButtonInstance::render(RenderDevice* rd)
{
	DataModelInstance* dataModel = g_dataModel;
	Vector2 pos = Vector2(dataModel->mousex,dataModel->mousey);
	drawObj(rd, pos, dataModel->mouseButton1Down);
	Instance::render(rd);
}

BaseButtonInstance::~BaseButtonInstance(void)
{
	if(listener != NULL && listener->doDelete)
	{
		delete listener;
		listener = NULL;
	}
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