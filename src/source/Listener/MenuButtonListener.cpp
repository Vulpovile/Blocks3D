#include "Listener/MenuButtonListener.h"
#include "DataModelV2/ToggleImageButtonInstance.h"
#include "Application.h"
#include "Globals.h"
void MenuButtonListener::onButton1MouseClick(BaseButtonInstance* button)
{
	if(button->name == "go")
	{
		bool isRunning = g_dataModel->isRunning();
		if(isRunning)
			g_dataModel->getRunService()->pause();
		else
			g_dataModel->getRunService()->run();
		//((ToggleImageButtonInstance*)button)->checked = !isRunning;
	}
	else if(button->name == "file")
	{
		HMENU mainmenu = CreatePopupMenu();
		AppendMenu(mainmenu, MF_STRING, 100, "New");
		AppendMenu(mainmenu, MF_STRING, 101, "Open...");
		AppendMenu(mainmenu, MF_STRING, 102, "Close");
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
		}
	}
	else if(button->name == "view")
	{
		HMENU mainmenu = CreatePopupMenu();
		AppendMenu(mainmenu, MF_STRING, 103, "Image Server Model View");
		
		POINT p;
		GetCursorPos(&p);
		int menuClick = TrackPopupMenu(mainmenu, TPM_LEFTBUTTON | TPM_RETURNCMD, p.x, p.y, 0, Globals::mainHwnd, 0);
		switch (menuClick)
		{
		case 103:
			g_dataModel->getThumbnailGenerator()->click("PNG", 512, 512, true);
			break;
		}
	}
}