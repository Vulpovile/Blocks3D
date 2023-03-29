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

void JointsService::solvePartSnap(PartInstance* Part1, PartInstance* Part2)
{
	XplicitNgine* Phys = g_dataModel->getEngine();
	float TopSurface = (Part1->getPosition().y + Part1->getSize().y / 2);
	float BottomSurface2 = (Part2->getPosition().y - Part2->getSize().y / 2);
	const int N = 4;
	if (TopSurface == BottomSurface2)
	{
		Phys->createBody(Part1);
		Phys->createBody(Part2);
		dContact contact[N];
		int n = dCollide (Part1->physGeom[0],Part2->physGeom[0],N,&contact[0].geom,sizeof(dContact));
		if (n > 0)
			createSnap(Part1, Part2);
	}
}

void JointsService::solveWorkspaceSnaps()
{
	std::vector<Instance* > children = g_dataModel->getWorkspace()->getAllChildren();
	for(size_t i = 0; i < children.size(); i++)
	{
		PartInstance* Part1 = (PartInstance*)children.at(i);
		if (Part1->isA("Part"))
		{
			for(size_t c = 0; c < children.size(); c++) //horrible
			{
				PartInstance* Part2 = (PartInstance*)children.at(c);
				if (Part1 != Part2)
					solvePartSnap(Part1, Part2);
			}
		}
	}
}