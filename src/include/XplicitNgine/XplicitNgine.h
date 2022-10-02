#pragma once
#include <ode/ode.h>
#include "DatamodelV2/Instance.h"
#include "DatamodelV2/PartInstance.h"

class XplicitNgine : Instance
{
public:
	XplicitNgine();
	~XplicitNgine();
	dWorldID physWorld;
	dSpaceID physSpace;
	dJointGroupID contactgroup;

	void createBody(PartInstance* partInstance);
};