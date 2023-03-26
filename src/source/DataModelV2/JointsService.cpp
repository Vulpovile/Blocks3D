#include "DataModelV2/JointsService.h"
#include "DataModelV2/SnapInstance.h"
#include "StringFunctions.h"
#include "Globals.h"

JointsService::JointsService()
{
	name = "JointsService";
	className = "JointsService";
	canDelete = false;
}

JointsService::~JointsService(void)
{
}

void JointsService::createSnap(PartInstance* Part1, PartInstance* Part2)
{
	SnapInstance* Snap = new SnapInstance(Part1, Part2);
	Snap->setParent(this);
}

//This is only for removing the Snap instance not for removing the joint
void JointsService::destroyPartSnap(PartInstance* Part)
{
	std::vector<Instance* > children = getChildren();
	for(size_t i = 0; i < children.size(); i++)
	{
		SnapInstance* Snap = (SnapInstance*)children.at(i);
		if((Snap->Joint1 == Part) || (Snap->Joint2 == Part))
		{
			removeChild(Snap);
		}
	}
}