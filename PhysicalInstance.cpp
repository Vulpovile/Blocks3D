#include <G3DAll.h>
#include "PhysicalInstance.h"

static const std::string className = "Part";
bool canCollide = true;
bool anchored = false;
Vector3 size;
Vector3 position;
Color3 color;

PhysicalInstance::PhysicalInstance(void)
{
	name = "Default PhysicalInstance";
	canCollide = true;
	anchored = true;
	size = Vector3(2,1,4);
	position = Vector3(0,0,0);
	color = Color3::gray();
	
}

PhysicalInstance::~PhysicalInstance(void)
{
}


