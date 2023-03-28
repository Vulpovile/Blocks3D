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

void JointsService::solvePartSnap(PartInstance* Part, PartInstance* Part2)
{
	float MoE = 0.05f;
	float TopSurface = (Part->getPosition().y + Part->getSize().y / 2);
	float RightRECT = (Part->getPosition().x + Part->getSize().x / 2) - MoE;
	float LeftRECT = (Part->getPosition().x - Part->getSize().x / 2) + MoE;
	float TopRECT = (Part->getPosition().z - Part->getSize().z / 2) + MoE;
	float BottomRECT = (Part->getPosition().z + Part->getSize().z / 2) - MoE;

	float BottomSurface2 = (Part2->getPosition().y - Part2->getSize().y / 2);
	float RightRECT2 = (Part2->getPosition().x + Part2->getSize().x / 2);
	float LeftRECT2 = (Part2->getPosition().x - Part2->getSize().x / 2);
	float TopRECT2 = (Part2->getPosition().z - Part2->getSize().z / 2);
	float BottomRECT2 = (Part2->getPosition().z + Part2->getSize().z / 2);

	std::cout << "TopSurface: " << TopSurface << std::endl;
	std::cout << "BottomSurface2: " << BottomSurface2 << std::endl;
	if (TopSurface == BottomSurface2)
	{
		std::cout << "Same Y cordinate!!!" << std::endl;
		//https://gamedev.stackexchange.com/questions/586/what-is-the-fastest-way-to-work-out-2d-bounding-box-intersection
		bool Intersect = !(LeftRECT2 > RightRECT
        || RightRECT2 < LeftRECT
        || TopRECT2 > BottomRECT
        || BottomRECT2 < TopRECT);
		if (Intersect){
			std::cout << "Intersects!!!" << std::endl;
			createSnap(Part, Part2);
		}else{
			std::cout << "Does not Intersect!!!" << std::endl;
		}
	}else{
		std::cout << "Y cordinate does not match!!!" << std::endl;
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