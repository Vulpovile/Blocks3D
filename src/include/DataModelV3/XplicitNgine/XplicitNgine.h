#pragma once
#include <ode/ode.h>
#include "DatamodelV3/Instance.h"
#include "DatamodelV3/PartInstance.h"

namespace B3D{
	struct PhysWorldData{
		dWorldID physWorld;
		dSpaceID physSpace;
		dJointGroupID contactgroup;
	};
	class XplicitNgine : public Instance
	{
	public:
		XplicitNgine();
		~XplicitNgine();
		dWorldID physWorld;
		dSpaceID physSpace;
		PhysWorldData physWorldData;
		dJointGroupID contactgroup;

		void step(float stepSize);
		void createBody(PartInstance* partInstance);
		void deleteBody(PartInstance* partInstance);
		void updateBody(PartInstance* partInstance);
		void resetBody(PartInstance* partInstance);
	};
}