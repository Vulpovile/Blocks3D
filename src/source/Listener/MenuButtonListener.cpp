#include "Listener/MenuButtonListener.h"
#include "DataModelV2/ToggleImageButtonInstance.h"
#include "Application.h"
#include "Globals.h"
void MenuButtonListener::onButton1MouseClick(BaseButtonInstance* button)
{
	if(button->name == "go")
	{
		g_dataModel->toggleRun();
		((ToggleImageButtonInstance*)button)->checked = g_dataModel->isRunning();
	}
	else if(button->name == "file")
	{
		HMENU mainmenu = CreatePopupMenu();
		AppendMenu(mainmenu, MF_STRING, 100, "New");
		AppendMenu(mainmenu, MF_STRING, 101, "Open...");
		AppendMenu(mainmenu, MF_STRING, 101, "Close");
		AppendMenu(mainmenu, MF_SEPARATOR, 0, NULL);
		POINT p;
		GetCursorPos(&p);
		TrackPopupMenu(mainmenu, TPM_LEFTBUTTON, p.x, p.y, 0, Globals::mainHwnd, 0);
	}
}