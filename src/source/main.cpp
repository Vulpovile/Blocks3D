// TODO: Move toolbar buttons with resized window.
#define _WIN32_WINNT 0x0400
#define _WIN32_WINDOWS 0x0400
#define WINVER 0x0400
#define _CRTBLD

#include "resource.h"
#include "Application.h"
#include "WindowFunctions.h"
#include "ax.h"
#include <commctrl.h>
#include "ErrorFunctions.h"

#if G3D_VER < 61000
	#error Requires G3D 6.10
#endif
HWND hwnd;

HRESULT hresult;
OLECHAR dat = ((OLECHAR)"SayHello");
OLECHAR * szMember = &dat;
DISPID dispid;
DISPPARAMS dispparamsNoArgs = {NULL, NULL, 0, 0};
EXCEPINFO excepinfo;
UINT nArgErr;

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	Application *app = (Application *)GetWindowLongPtr(hwnd, GWL_USERDATA);
	if (app==NULL)
	{
		return DefWindowProc(hwnd, msg, wParam, lParam);
	}
    switch(msg)
    {
		case WM_KEYDOWN:
			if ((HIWORD(lParam)&0x4000)==0) // single key press
			{
				app->onKeyPressed(wParam);
			}
		break;
		case WM_KEYUP:
		{
			app->onKeyUp(wParam);
		}
		break;
		case WM_MOUSEWHEEL:
			app->onMouseWheel(LOWORD(lParam),HIWORD(lParam),HIWORD(wParam));
		break;
		case WM_SIZE:
			app->resizeWithParent(hwnd);
		break;
		case WM_ACTIVATE:
			if(wParam > WA_INACTIVE) app->setFocus(false);
			else app->setFocus(true);
        default:
		{
            return DefWindowProc(hwnd, msg, wParam, lParam);
		}
    }
    return 0;
}

LRESULT CALLBACK ToolboxProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	MessageBox(NULL, (LPCSTR)wParam, (LPCSTR)lParam, 1);
	switch(msg)
    {
		case WM_SIZE:
		break;
        default:
		{
            return DefWindowProc(hwnd, msg, wParam, lParam);
		}
    }
    return 0;
}

LRESULT CALLBACK G3DProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    Application *app = (Application *)GetWindowLongPtr(hwnd, GWL_USERDATA);
	if (app==NULL)
	{
		return DefWindowProc(hwnd, msg, wParam, lParam);
	}
    switch(msg)
    {
        case WM_QUIT:
			app->QuitApp();
        break;
        case WM_DESTROY:
            app->QuitApp();
        break;
		case WM_LBUTTONDOWN:
			app->onMouseLeftPressed(hwnd,LOWORD(lParam),HIWORD(lParam));
		break;
		case WM_LBUTTONUP:
			app->onMouseLeftUp(app->getRenderDevice(),LOWORD(lParam),HIWORD(lParam));
		break;
		case WM_RBUTTONDOWN:
			app->onMouseRightPressed(LOWORD(lParam),HIWORD(lParam));
		break;
		case WM_RBUTTONUP:
			app->onMouseRightUp(LOWORD(lParam),HIWORD(lParam));
		break;
		case WM_MOUSEMOVE:
			app->onMouseMoved(LOWORD(lParam),HIWORD(lParam));
		break;
		case WM_KEYDOWN:
			if ((HIWORD(lParam)&0x4000)==0) // single key press
			{
				app->onKeyPressed(wParam);
			}
		break;
		case WM_KEYUP:
		{
			app->onKeyUp(wParam);
		}
		break;
		case WM_SYSKEYDOWN:
			if ((HIWORD(lParam)&0x4000)==0) // single key press
			{
				app->onKeyPressed(wParam);
			}
		break;
		case WM_SYSKEYUP:
		{
			app->onKeyUp(wParam);
		}
		case WM_SIZE:
		{
			app->onGraphics(app->getRenderDevice());
		}
		break;
        default:
		{
            return DefWindowProc(hwnd, msg, wParam, lParam);
		}
    }
    return 0;
}


int main(int argc, char** argv) {
#ifndef _DEBUG
	try{
#endif
		hresult = OleInitialize(NULL);
		if (!AXRegister())
			return 0;

			
		INITCOMMONCONTROLSEX icc;

		/* Initialize common controls. Also needed for MANIFEST's */

		icc.dwSize = sizeof(icc);
		icc.dwICC = ICC_WIN95_CLASSES/*|ICC_COOL_CLASSES|ICC_DATE_CLASSES|
					   ICC_PAGESCROLLER_CLASS|ICC_USEREX_CLASSES*/;
		InitCommonControlsEx(&icc);
		HMODULE hThisInstance = GetModuleHandle(NULL);

		if (!createWindowClass("mainHWND",WndProc,hThisInstance))
			return false;
		if (!createWindowClass("toolboxHWND",ToolboxProc,hThisInstance))
			return false;
		if (!createWindowClass("G3DWindow",G3DProc,hThisInstance))
			return false;

		HWND hwndMain = CreateWindowEx(
			WS_EX_APPWINDOW,
			"mainHWND",
			"Main test",
			WS_OVERLAPPEDWINDOW,
			CW_USEDEFAULT,
			CW_USEDEFAULT,
			800,
			660,
			NULL, // parent
			NULL, // menu
			hThisInstance,
			NULL
		);
		if(hwndMain == NULL)
		{
			MessageBox(NULL, "Critical error loading: Failed to create HWND, must exit", (g_appName + " Crash").c_str() , MB_OK);
			return 0;
		}
		SendMessage(hwndMain, WM_SETICON, ICON_BIG,(LPARAM)LoadImage(GetModuleHandle(NULL), (LPCSTR)MAKEINTRESOURCEW(IDI_ICON1), IMAGE_ICON, 0, 0, LR_DEFAULTCOLOR | LR_DEFAULTSIZE));
		
		Globals::mainHwnd = hwndMain;
		Application app = Application(hwndMain);
		app.run();	
#ifndef _DEBUG
	}
	catch(...)
	{
		OnError(-1);
	}
#endif
    return 0;
}
