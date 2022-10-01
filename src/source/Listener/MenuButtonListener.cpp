#include "Listener/MenuButtonListener.h"
#include "DataModelV2/ToggleImageButtonInstance.h"
#include "Application.h"
#include "Globals.h"
#include "../../resource.h"

INT_PTR CALLBACK InsertDlgProc(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam)
{
	switch(Message)
	{
		case WM_INITDIALOG:
		return TRUE;
		break;
		case WM_COMMAND:
			switch(LOWORD(wParam))
			{
				case IDOK:
					//g_dataModel->setMessage("lol u thought");
					EndDialog(hwnd, IDOK);
				break;
				case IDCANCEL:
					EndDialog(hwnd, IDCANCEL);
				break;
			}
		break;
		default:
			return FALSE;
	}
	return TRUE;
}

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
	else if(button->name == "insert")
	{
		//HWND aDiag = CreateDialog((HINSTANCE) GetWindowLong(Globals::mainHwnd, GWL_HINSTANCE), MAKEINTRESOURCE(IDD_DIALOG1), Globals::mainHwnd, (DLGPROC)InsertDlgProc);
		HWND aDiag2 = CreateDialog((HINSTANCE) GetWindowLong(Globals::mainHwnd, GWL_HINSTANCE), MAKEINTRESOURCE(IDD_DIALOG2), Globals::mainHwnd, (DLGPROC)InsertDlgProc);
	}
}


