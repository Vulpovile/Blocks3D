#pragma once
#include "Instance.h"

class RunService :
	public Instance
{
public:
	RunService(void);
	~RunService(void);

	void run();
	void pause();
	void reset();
};
