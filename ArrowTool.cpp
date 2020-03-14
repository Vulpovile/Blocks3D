#include "ArrowTool.h"
#include "Application.h"

ArrowTool::ArrowTool(void)
{
	lctrlDown = false;
	rctrlDown = false;
}

ArrowTool::~ArrowTool(void)
{
}

void ArrowTool::onButton1MouseDown(Mouse mouse)
{
	if(!lctrlDown && !rctrlDown)
		g_selectedInstances.clear();
	PartInstance * target = mouse.getTarget();
	if(target != NULL && std::find(g_selectedInstances.begin(), g_selectedInstances.end(), target) == g_selectedInstances.end())
		g_selectedInstances.push_back(target);
	if(g_selectedInstances.size() == 0)
		g_selectedInstances.push_back(g_dataModel);
	g_usableApp->_propWindow->UpdateSelected(g_selectedInstances[0]);
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

void ArrowTool::onKeyDown(int key)
{
	if(key == VK_CONTROL)
	{
		lctrlDown = true;
	}
}

void ArrowTool::onKeyUp(int key)
{
	if(key == VK_CONTROL)
		lctrlDown = false;
}