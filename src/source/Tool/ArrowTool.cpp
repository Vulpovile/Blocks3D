#include "Tool/ArrowTool.h"
#include "Application.h"

ArrowTool::ArrowTool(void)
{
	// Should solve issue of resize and move handles being drawn when they don't need to be
	g_usableApp->unSetMode();
	lctrlDown = false;
	rctrlDown = false;
	dragging = false;
	mouseDown = false;
}

ArrowTool::~ArrowTool(void)
{
}

void ArrowTool::onButton1MouseDown(Mouse mouse)
{
	mouseDownStartx = mouse.x;
	mouseDownStarty = mouse.y;
	mouseDown = true;
	if(!lctrlDown && !rctrlDown)
		g_selectedInstances.clear();
	PartInstance * target = mouse.getTarget();
	if(target != NULL && std::find(g_selectedInstances.begin(), g_selectedInstances.end(), target) == g_selectedInstances.end())
		g_selectedInstances.push_back(target);
	if(g_selectedInstances.size() == 0)
		g_selectedInstances.push_back(g_dataModel);
	g_usableApp->_propWindow->UpdateSelected(g_selectedInstances[0]);
}
void ArrowTool::onButton1MouseUp(Mouse mouse)
{
	mouseDown = false;
	dragging = false;
}

void ArrowTool::onMouseMoved(Mouse mouse)
{
	if(mouseDown)
	{
		if(!dragging)
		{
			if(abs(mouse.x-mouseDownStartx) > 5 || abs(mouse.y-mouseDownStarty) > 5)
			{
				dragging = true;
			}
			else return;
		}
		for(size_t i = 0; i < g_selectedInstances.size(); i++) //This will later decide primary and move all parts according to primary
		{
			if(PartInstance * part = dynamic_cast<PartInstance *>(g_selectedInstances[i]))
			{
				part->setPosition(mouse.getPosition(g_selectedInstances));
			}
		}
		return;
	}
	PartInstance * target = mouse.getTarget();
	//if(target == NULL)
}
void ArrowTool::onSelect(Mouse mouse)
{
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