#include "Mouse.h"
#include "Application.h"
#include "Globals.h"
#include <math.h>

Mouse::Mouse()
{
	x = y = 0;
}

Mouse::~Mouse() 
{

}

PartInstance * selectedInstance = NULL;
Ray testRay;
float nearest = std::numeric_limits<float>::infinity();

void eprt(PartInstance * instance)
{
	float time = testRay.intersectionTime(instance->getBox());
	if (time != inf() && nearest > time) 
	{
		nearest = time;
		selectedInstance = instance;
	}
}

PartInstance * Mouse::getTarget()
{
	selectedInstance = NULL;
	testRay = g_usableApp->cameraController.getCamera()->worldRay(x, y, g_usableApp->getRenderDevice()->getViewport());
	nearest=std::numeric_limits<float>::infinity();
	for_each (g_dataModel->getWorkspace()->partObjects.begin(), g_dataModel->getWorkspace()->partObjects.end(), eprt);
	return selectedInstance;
}

G3D::Ray * Mouse::getRay()
{
	return &g_usableApp->cameraController.getCamera()->worldRay(x, y, g_usableApp->getRenderDevice()->getViewport());
}

G3D::Ray Mouse::getLastRay()
{
	return testRay;
}


double getVectorDistance(Vector3 vector1, Vector3 vector2)
{
	// what the
	return pow(pow((double)vector1.x - (double)vector2.x, 2) + pow((double)vector1.y - (double)vector2.y, 2) + pow((double)vector1.z - (double)vector2.z, 2), 0.5);
}

MousePoint Mouse::getPositionAndPart(std::vector<Instance *> ignore)
{
	testRay = g_usableApp->cameraController.getCamera()->worldRay(x, y, g_usableApp->getRenderDevice()->getViewport());
	PartInstance * currPart = NULL;
	Vector3 pos = testRay.closestPoint(Vector3(0, 0, 0));
	nearest = std::numeric_limits<float>::infinity();
	
	for(size_t i = 0; i < g_dataModel->getWorkspace()->partObjects.size(); i++)
	{
		PartInstance * p = g_dataModel->getWorkspace()->partObjects[i];
		
		if (std::find(ignore.begin(), ignore.end(), p) != ignore.end())
			continue;
		
		float newdistance = testRay.intersectionTime(p->getBox()); //testRay.distance(inter);
		if (G3D::isFinite(newdistance) && nearest > abs(newdistance))
        	{
			nearest = newdistance;
                	pos = testRay.origin + (testRay.direction * nearest);
			currPart = p;
        	}
	}

	// A scuffed fix for moving
	if (currPart == NULL) {
		if (PartInstance * part = dynamic_cast<PartInstance *>(ignore[0]))
		{
			return MousePoint(part->getPosition(), part);
		}
		return MousePoint(pos, currPart);
	}
		
	// A crude implementation of stud snapping
	Vector3 pSz = currPart->getSize();
	pos.x = ceil(pos.x);
	pos.y = ceil(pos.y);
	pos.z = ceil(pos.z);

	return MousePoint(pos, currPart);
}

Vector3 Mouse::getPosition(std::vector<Instance *> ignore)
{
	return getPositionAndPart(ignore).position;
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
