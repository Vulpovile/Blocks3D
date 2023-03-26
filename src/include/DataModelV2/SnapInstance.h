#pragma once
#include "Instance.h"
#include "PartInstance.h"

class SnapInstance:
	public Instance
{
public:
	SnapInstance(PartInstance* Part1, PartInstance* Part2);
	~SnapInstance(void);
	PartInstance* Joint1;
	PartInstance* Joint2;
};
