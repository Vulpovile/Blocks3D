#pragma once
#include "Instance.h"
#include "PartInstance.h"

class JointsService:
	public Instance
{
public:
	JointsService(void);
	~JointsService(void);
	void createSnap(PartInstance* Part1, PartInstance* Part2);
	void destroyPartSnap(PartInstance* Part);
};
