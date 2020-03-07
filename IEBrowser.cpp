#ifndef WIN32_LEAN_AND_MEAN
	#define WIN32_LEAN_AND_MEAN
#endif


#include <windows.h>

#include "IEBrowser.h"
#include "Globals.h"
#include "ax.h"

//#include "IEDispatcher.h"

void IEBrowser::Boop(char* test)
{
}

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

// Something goes here
int IEBrowser::setExternal(IDispatch** ext)
{
	std::cout << &m_IEDispatcher;
	IInternetHostSecurityManager* spSecMan;
	spDocument2->QueryInterface(IID_IInternetHostSecurityManager,
			(void **) &spSecMan);

	// TODO: hr needs to say: 'S_OK'
	//spSecMan->QueryCustomPolicy
	HRESULT hr = spSecMan->ProcessUrlAction(URLACTION_ACTIVEX_OVERRIDE_OBJECT_SAFETY,
		NULL, 0, NULL, 0, 0, PUAF_WARN_IF_DENIED);

	(*ext) = &m_IEDispatcher;
	return 1;
}

bool IEBrowser::navigateSyncURL(wchar_t* url)
{
	MSG messages;
	if (webBrowser)
	{
		webBrowser->Navigate(url,0,0,0,0);
	}
	else
	{
		MessageBox(NULL,"Cannot read IWebBrowser2...",(g_PlaceholderName+" Crash").c_str(),MB_OK);
	}

	return false;
}
