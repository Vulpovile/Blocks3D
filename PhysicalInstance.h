#pragma once
#include "instance.h"

class PhysicalInstance :
	public Instance
{
public:
	PhysicalInstance(void);
	~PhysicalInstance(void);
	Vector3 size;
	Vector3 position;
	Vector3 velocity;
	Vector3 rotvelocity;
	Color3 color;
};
