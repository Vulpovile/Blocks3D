#include "ArrowTool.h"

ArrowTool::ArrowTool(void)
{
}

ArrowTool::~ArrowTool(void)
{
}

void ArrowTool::onButton1MouseDown(Mouse mouse)
{
	g_selectedInstances.clear();
	PartInstance * target = mouse.getTarget();
	if(target != NULL)
		g_selectedInstances.push_back(target);
}
void ArrowTool::onMouseMoved(Mouse mouse)
{
	PartInstance * target = mouse.getTarget();
	if(target == NULL)
		this->setCursor(GetFileInPath("/content/images/ArrowCursor.png"));
	else this->setCursor(GetFileInPath("/content/images/DragCursor.png"));
}
void ArrowTool::onSelect(Mouse mouse)
{
	this->setCursor(GetFileInPath("/content/images/ArrowCursor.png"));
}