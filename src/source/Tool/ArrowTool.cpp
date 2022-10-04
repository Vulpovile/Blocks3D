#include "Tool/ArrowTool.h"
#include "Application.h"
#include "DataModelV2/SelectionService.h"

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
		g_dataModel->getSelectionService()->clearSelection();
	PartInstance * target = mouse.getTarget();
	if(target != NULL)
		g_dataModel->getSelectionService()->addSelected(target);
	if(g_dataModel->getSelectionService()->getSelection().size() == 0)
		g_dataModel->getSelectionService()->addSelected(g_dataModel);
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
		for(size_t i = 0; i < g_dataModel->getSelectionService()->getSelection().size(); i++) //This will later decide primary and move all parts according to primary
		{
			if(PartInstance * part = dynamic_cast<PartInstance *>(g_dataModel->getSelectionService()->getSelection()[i]))
			{
				part->setPosition(mouse.getPosition(g_dataModel->getSelectionService()->getSelection()));
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