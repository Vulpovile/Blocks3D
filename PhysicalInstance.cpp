#include <G3DAll.h>
#include "PhysicalInstance.h"


bool collides = true;
bool anchored = false;
Vector3 size;
Vector3 position;
Color3 color;
//static const int type = PHYSICAL_INSTANCE;

PhysicalInstance::PhysicalInstance(void)
{
	name = "Default PhysicalInstance";
	collides = true;
	anchored = true;
	size = Vector3(2,1,4);
	position = Vector3(0,0,0);
	color = Color3::gray();
}

PhysicalInstance::~PhysicalInstance(void)
{
}


