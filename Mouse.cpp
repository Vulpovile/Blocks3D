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


double getVectorDistance(Vector3 vector1, Vector3 vector2)
{
	return pow(pow((double)vector1.x - (double)vector2.x, 2) + pow((double)vector1.y - (double)vector2.y, 2) + pow((double)vector1.z - (double)vector2.z, 2), 0.5);
}

Vector3 Mouse::getPosition()
{
	testRay = g_usableApp->cameraController.getCamera()->worldRay(x, y, g_usableApp->getRenderDevice()->getViewport());
	Vector3 pos = testRay.closestPoint(Vector3(0,0,0));
	nearest=std::numeric_limits<float>::infinity();
	//Vector3 camPos = g_usableApp->cameraController.getCamera()->getCoordinateFrame().translation;
	for(size_t i = 0; i < g_dataModel->getWorkspace()->partObjects.size(); i++)
	{
		PartInstance * p = g_dataModel->getWorkspace()->partObjects[i];
		if(G3D::isFinite(testRay.intersectionTime(p->getBox())))
		{

			/*if (nearest>testRay.intersectionTime(p->getBox()))
			{

				// BROKEN
				pos = (testRay.closestPoint(p->getPosition()/2));
			}*/

			 // This would be an overall better solution
			for(char i = 0; i < 6; i++)
			{
				Vector3 side1;
				Vector3 side2;
				Vector3 side3;
				Vector3 side4;
				p->getBox().getFaceCorners(i, side1, side2, side3, side4);
				Vector3 inter = testRay.intersection(G3D::Plane(side2, side3, side4));
				float newdistance = testRay.distance(inter);
				if(nearest > abs(newdistance))
				{
					nearest = newdistance;
					pos = inter;
				}
			}
		}
	}
	return pos;
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

