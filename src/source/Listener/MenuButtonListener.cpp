#include "Listener/MenuButtonListener.h"
#include "DataModel/ToggleImageButtonInstance.h"
#include "Globals.h"
void MenuButtonListener::onButton1MouseClick(BaseButtonInstance* button)
{
	if(button->name == "go")
	{
		g_dataModel->toggleRun();
		((ToggleImageButtonInstance*)button)->checked = g_dataModel->isRunning();
	}
}