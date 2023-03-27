#include "DataModelV2/SnapInstance.h"
#include "XplicitNgine/XplicitNgine.h"
#include "StringFunctions.h"
#include "Globals.h"

SnapInstance::SnapInstance(PartInstance* Part1, PartInstance* Part2)
{
	XplicitNgine* Phys = g_xplicitNgine;
	name = "Snap";
	className = "Snap";
	jPart1 = Part1;
	jPart2 = Part2;
	
	if (Part1->physBody == NULL)
		Phys->createBody(Part1);

	if (Part2->physBody == NULL)
		Phys->createBody(Part2);

	JointID = Phys->createJoint(Part1, Part2);
}

SnapInstance::~SnapInstance(void)
{
	//XplicitNgine* Phys = g_xplicitNgine;
	printf("SnapInstance destroyed...");
	if (JointID != NULL)
		dJointDestroy(JointID);
}
