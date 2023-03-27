#pragma once
#include "Instance.h"
#include "PartInstance.h"

class SnapInstance:
	public Instance
{
public:
	SnapInstance(PartInstance* Part1, PartInstance* Part2);
	~SnapInstance(void);
	PartInstance* jPart1;
	PartInstance* jPart2;
	dJointID JointID;
};
