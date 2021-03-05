#include "Globals.h"
#include "Instance.h"
#include "ModeSelectionListener.h"
#include "Application.h"
#include "Tool/ArrowTool.h"

void ModeSelectionListener::onButton1MouseClick(BaseButtonInstance* button)
{
	//CoordinateFrame frame = g_usableApp->g3dCamera.getCoordinateFrame();
	int mode = g_usableApp->getMode();

	std::vector<Instance*> instances_2D = g_dataModel->getGuiRoot()->getAllChildren();
	for(size_t i = 0; i < instances_2D.size(); i++)
		{
			if(instances_2D.at(i)->name == "Cursor" || instances_2D.at(i)->name == "Resize" || instances_2D.at(i)->name == "Arrows")
			{
				BaseButtonInstance* button = (BaseButtonInstance*)instances_2D.at(i);
				button->selected = false;
			}
		}

	button->selected = true;
	if(button->name == "Cursor")
		g_usableApp->changeTool(new ArrowTool());
	else if(button->name == "Resize")
		g_usableApp->setMode(RESIZE);
	else if(button->name == "Arrows")
		g_usableApp->setMode(ARROWS);
}
