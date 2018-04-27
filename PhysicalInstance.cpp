#include "PhysicalInstance.h"

bool canCollide = true;
bool anchored = false;
Vector3 size;
Vector3 position;
Vector3 velocity;
Vector3 rotVelocity;
CoordinateFrame cFrame;
Color3 color;

PhysicalInstance::PhysicalInstance(void)
{
	name = "Default PhysicalInstance";
	className = "Part";
	canCollide = true;
	anchored = true;
	size = Vector3(2,1,4);
	position = Vector3(0,0,0);
	cFrame = CoordinateFrame(position);
	color = Color3::gray();
	velocity = Vector3(0,0,0);
	rotVelocity = Vector3(0,0,0);
}

Vector3 PhysicalInstance::getPosition()
{
	return position;
}
void PhysicalInstance::setPosition(Vector3 pos)
{
	position = pos;
	cFrame = CoordinateFrame(pos);
}
CoordinateFrame PhysicalInstance::getCFrame()
{
	return cFrame;
}
void PhysicalInstance::setCFrame(CoordinateFrame coordinateFrame)
{
	cFrame = coordinateFrame;
	position = coordinateFrame.translation;
}

CoordinateFrame PhysicalInstance::getCFrameRenderBased()
{
	return CoordinateFrame(getCFrame().rotation,Vector3(getCFrame().translation.x/2, getCFrame().translation.y/2, getCFrame().translation.z/2));
}

Box PhysicalInstance::getBox()
{
	Box box = Box(Vector3(0+size.x/4, 0+size.y/4, 0+size.z/4) ,Vector3(0-size.x/4,0-size.y/4,0-size.z/4));
	CoordinateFrame c = getCFrameRenderBased();
	return c.toWorldSpace(box);
}

PhysicalInstance::~PhysicalInstance(void)
{
}




