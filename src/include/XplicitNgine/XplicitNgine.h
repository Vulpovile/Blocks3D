#pragma once
#include <ode/ode.h>
#include "DatamodelV2/Instance.h"
#include "DatamodelV2/PartInstance.h"

class XplicitNgine : public Instance
{
public:
	XplicitNgine();
	~XplicitNgine();
	dWorldID physWorld;
	dSpaceID physSpace;
	dJointGroupID contactgroup;

	void step(float stepSize);
	void createBody(PartInstance* partInstance);
	void deleteBody(PartInstance* partInstance);
	void updateBody(PartInstance* partInstance);
};