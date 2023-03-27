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

void JointsService::destroyPartSnap(PartInstance* Part)
{
	std::vector<Instance* > children = getChildren();
	for(size_t i = 0; i < children.size(); i++)
	{
		SnapInstance* Snap = (SnapInstance*)children.at(i);
		if((Snap->jPart1 == Part) || (Snap->jPart2 == Part))
		{
			Snap->remove();
		}
	}
}