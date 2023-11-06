#pragma once
#include "PartInstance.h"
namespace B3D{
	class GroupInstance : public PVInstance
	{
	public:
		GroupInstance(void);
		~GroupInstance(void);
		GroupInstance(const GroupInstance &oinst);
		std::vector<Instance *> unGroup();
		PartInstance * primaryPart;
		//This is used to render the controllerflag, we may want to move it elsewhere?
		void render(RenderDevice * r);
	protected:
		GroupInstance(std::string className);
	};
}