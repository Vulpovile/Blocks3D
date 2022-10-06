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
		AppendMenu(mainmenu, MF_STRING, 102, "Close");
		AppendMenu(mainmenu, MF_STRING, 103, "ThumbnailGenerator::click");
		AppendMenu(mainmenu, MF_SEPARATOR, 0, NULL);
		POINT p;
		GetCursorPos(&p);
		int menuClick = TrackPopupMenu(mainmenu, TPM_LEFTBUTTON | TPM_RETURNCMD, p.x, p.y, 0, Globals::mainHwnd, 0);
		switch (menuClick)
		{
		case 100:
			g_usableApp->clearInstances();
			g_usableApp->onInit();
			break;
		case 101:
			g_dataModel->getOpen();
			break;
		case 102:
			g_usableApp->QuitApp();
			break;
		case 103:
			g_dataModel->getThumbnailGenerator()->click("PNG", 256, 256, true);
		}
	}
}