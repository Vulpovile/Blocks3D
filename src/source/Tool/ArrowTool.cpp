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
	{
		Vector3 mousePos = mouse.getPosition(g_dataModel->getSelectionService()->getSelection());
		Vector3 targetPos = target->getPosition();
		
		g_dataModel->getSelectionService()->addSelected(target);
		draggingPartOffset = targetPos-mousePos;
	}
	if(g_dataModel->getSelectionService()->getSelection().size() == 0)
		g_dataModel->getSelectionService()->addSelected(g_dataModel);
}
void ArrowTool::onButton1MouseUp(Mouse mouse)
{
	mouseDown = false;
	dragging = false;

	for(size_t i = 0; i < g_dataModel->getSelectionService()->getSelection().size(); i++) //This will later decide primary and move all parts according to primary
	{
		if(PartInstance * part = dynamic_cast<PartInstance *>(g_dataModel->getSelectionService()->getSelection()[i]))
		{
			part->setDragging(false);
		}
	}
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
				Vector3 mousePos = mouse.getPosition(g_dataModel->getSelectionService()->getSelection());
				Vector3 vec = mousePos + draggingPartOffset;

				vec.x = (ceil(vec.x / 1) * 1);
				vec.y = (ceil(vec.y / 1) * 1);
				vec.z = (ceil(vec.z / 1) * 1);

				if ( ((int)part->getSize().x)%2 == 1 )
					vec.x += 0.5;

				vec.y = mousePos.y + part->getSize().y/2 - 0.5;

				if ( ((int)part->getSize().z)%2 == 1 )
					vec.z += 0.5;

				Matrix3 rot = part->getCFrame().rotation;
				Vector3 rotEulerAngles;

				rot.toEulerAnglesXYZ(rotEulerAngles.x, rotEulerAngles.y, rotEulerAngles.z);

				rotEulerAngles = Vector3(
					rotEulerAngles.x * 180 / M_PI,
					rotEulerAngles.y * 180 / M_PI,
					rotEulerAngles.z * 180 / M_PI
				);

				roundDeg(rotEulerAngles.x);
				roundDeg(rotEulerAngles.y);
				roundDeg(rotEulerAngles.z);

				rot = rot.fromEulerAnglesXYZ( rotEulerAngles.x * (M_PI / 180), rotEulerAngles.y * (M_PI / 180), rotEulerAngles.z * (M_PI / 180) );

				part->setPosition(vec);
				part->setDragging(true);
				part->setCFrame(CoordinateFrame(rot, vec));
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

void ArrowTool::roundDeg(float &degree)
{
	if ( ( degree < 0 && degree > -45 ) || ( degree > 0 && degree < 45 ) )
	{
		degree = 0;
	}
	else if ( ( degree < 0 && degree > -90 ) || ( degree > 45 && degree < 90 ) )
	{
		degree = 90;
	}
	else if ( ( degree < 0 && degree > -180 ) || ( degree > 90 && degree < 180 ) )
	{
		degree = 180;
	}
}