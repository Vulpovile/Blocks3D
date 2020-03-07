#include "MenuButtonListener.h"
#include "toggleimagebuttoninstance.h"
#include "Globals.h"
void onButton1MouseClick(BaseButtonInstance* button)
{
	if(button->name == "go")
	{
		g_dataModel->toggleRun();
		((ToggleImageButtonInstance*)button)->checked = g_dataModel->isRunning();
	}
}