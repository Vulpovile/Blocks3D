#include "PhysicalInstance.h"

bool canCollide = true;
bool anchored = false;
Vector3 size;
Vector3 position;
Vector3 velocity;
Vector3 rotVelocity;
Color3 color;

PhysicalInstance::PhysicalInstance(void)
{
	name = "Default PhysicalInstance";
	className = "Part";
	canCollide = true;
	anchored = true;
	size = Vector3(2,1,4);
	position = Vector3(0,0,0);
	color = Color3::gray();
	velocity = Vector3(0,0,0);
	rotVelocity = Vector3(0,0,0);
}

PhysicalInstance::~PhysicalInstance(void)
{
}


