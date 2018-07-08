#ifndef WIN32_LEAN_AND_MEAN
	#define WIN32_LEAN_AND_MEAN
#endif

#include <windows.h>

#include "IEBrowser.h"
#include "Globals.h"
#include "ax.h"


IEBrowser::IEBrowser(HWND attachHWnd) {
	MSG messages;
	while (PeekMessage (&messages, NULL, 0, 0,PM_REMOVE))
	{
		if (IsDialogMessage(hwnd, &messages) == 0)
		{
			TranslateMessage(&messages);
			DispatchMessage(&messages);
		}
	}
	hwnd = attachHWnd;
	spDocument = 0;
	webBrowser = 0;
	SendMessage(hwnd,AX_INPLACE,1,0);
	SendMessage(hwnd,AX_QUERYINTERFACE,(WPARAM)&IID_IWebBrowser2,(LPARAM)&webBrowser);
}

IEBrowser::~IEBrowser(void) {
	if (webBrowser)
	{
		webBrowser->Release();
	}
}

bool IEBrowser::navigateSyncURL(wchar_t* url)
{
	MSG messages;
	if (webBrowser)
	{
		webBrowser->Navigate(url,0,0,0,0);
		for (int i=1;i<1000;i++)
		{
			while (PeekMessage (&messages, NULL, 0, 0,PM_REMOVE))
			{
				if (IsDialogMessage(hwnd, &messages) == 0)
				{
					TranslateMessage(&messages);
					DispatchMessage(&messages);
				}
			}
			Sleep(30);
			HRESULT hresult = webBrowser->get_Document(&spDocument);
			if (&spDocument!=0)
			{
				return true;
			}
		}
	}
	else
	{
		MessageBox(NULL,"Cannot read IWebBrowser2...",Globals::PlaceholderName.c_str(),MB_OK);
	}
	return false;
}