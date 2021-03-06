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
	else if(button->name == "file")
	{
		HMENU hPopupMenu = CreatePopupMenu();
		HWND hwnd = CreateWindowEx(
			WS_EX_APPWINDOW,
			"MenuWindow",
			"Main test",
			WS_OVERLAPPEDWINDOW,
			CW_USEDEFAULT,
			CW_USEDEFAULT,
			800,
			660,
			NULL, // parent
			NULL, // menu
			GetModuleHandle(NULL),
			NULL
		);

		AppendMenu(hPopupMenu, MF_STRING, 0, "Test");
		if(hPopupMenu == NULL)
		{
			MessageBox(NULL, "Menu is null!", "Failed", MB_OK);
		}
		else if(hwnd == NULL)
		{
			MessageBox(NULL, "HWND is null!", "Failed", MB_OK);
		}
		else if(!TrackPopupMenu(hPopupMenu, TPM_LEFTBUTTON, 100, 100, 0, hwnd, 0))
		{
			MessageBox(NULL, "Failed to track!", "Failed", MB_OK);
		}
	}
}