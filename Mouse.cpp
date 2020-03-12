#include "Mouse.h"
Mouse::Mouse(){
	x = y = 0;
}
Mouse::~Mouse(){}


Instance * Mouse::getTarget()
{
	return NULL;
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