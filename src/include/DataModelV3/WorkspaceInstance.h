#pragma once
#include "GroupInstance.h"
#include "PartInstance.h"
namespace B3D
{
	class WorkspaceInstance : public GroupInstance
	{
	public:
		WorkspaceInstance(void);
		~WorkspaceInstance(void);
		void clearChildren();
		void zoomToExtents();
		std::vector<PartInstance *> partObjects;
	};
}