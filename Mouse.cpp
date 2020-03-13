#include "Mouse.h"
#include "Application.h"
#include "Globals.h"
Mouse::Mouse(){
	x = y = 0;
}
Mouse::~Mouse(){}

PartInstance * selectedInstance = NULL;
Ray testRay;
float nearest=std::numeric_limits<float>::infinity();
void eprt(PartInstance * instance)
{
		float time = testRay.intersectionTime(instance->getBox());
		if (time != inf()) 
		{
			if (nearest>time)
			{
				nearest=time;
				selectedInstance = instance;
				//This is where dead code below was
			}
		}
}

PartInstance * Mouse::getTarget()
{
	selectedInstance = NULL;
	testRay = g_usableApp->cameraController.getCamera()->worldRay(x, y, g_usableApp->getRenderDevice()->getViewport());
	nearest=std::numeric_limits<float>::infinity();
	//Vector3 camPos = g_usableApp->cameraController.getCamera()->getCoordinateFrame().translation;
	for_each (g_dataModel->getWorkspace()->partObjects.begin(), g_dataModel->getWorkspace()->partObjects.end(), eprt);
	return selectedInstance;
}






Vector3 Mouse::getPosition()
{
	return Vector3();
	//Not implemented
}
bool Mouse::isMouseOnScreen()
{
	//hm
	return true;
}

bool Mouse::isMouseDown()
{
	return mouseDown;
}

void Mouse::setMouseDown(bool bval)
{
	mouseDown = bval;
}



				//bool found = false;
				/*for(size_t i = 0; i < g_selectedInstances.size(); i++)
				{
					if(g_selectedInstances.at(i) == test)
					{
						found = true;
						//ShowWindow(_propWindow->_hwndProp, SW_SHOW);
						//SetActiveWindow(_propWindow->_hwndProp);
						//SetForegroundWindow(_propWindow->_hwndProp);
						break;
					}
				}
				if(!found)
				{
					selectedInstance = test;
					//if(!GetHoldKeyState(VK_RCONTROL) && !GetHoldKeyState(VK_LCONTROL))
						//g_selectedInstances.clear();
					//if(std::find(g_selectedInstances.begin(), g_selectedInstances.end(),test)==g_selectedInstances.end())
						//g_selectedInstances.push_back(test);
				}
				//selectInstance(test, _propWindow);
				//_message = "Dragging = true.";
				//_messageTime = System::time();
				//_dragging = true;*/

