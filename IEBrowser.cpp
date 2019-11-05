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
	return 1;
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
			if (SUCCEEDED(hresult) && (spDocument != 0))
			{
				
				IOleObject* spOleObject;
				if (SUCCEEDED(spDocument->QueryInterface(IID_IOleObject,(void**)&spOleObject)))
				{
					IOleClientSite* spClientSite;
					hresult = spOleObject->GetClientSite(&spClientSite);
					if (SUCCEEDED(hresult) && spClientSite)
					{
						m_spDefaultDocHostUIHandler = spClientSite;
						ICustomDoc* spCustomDoc;

						//IEDispatcher* spIEDispatcher;
						if (SUCCEEDED(m_spDefaultDocHostUIHandler->QueryInterface(IID_IDocHostUIHandler,(void**)&m_spHandler)))
						{
							if (SUCCEEDED(spDocument->QueryInterface(IID_ICustomDoc,(void**)&spCustomDoc)))
							{
								spCustomDoc->SetUIHandler(m_spHandler);
				
								m_spHandler->GetExternal(&m_spExternal);
								
							}
						}
					}
				}
				


				return true;
			}
		}
	}
	else
	{
		MessageBox(NULL,"Cannot read IWebBrowser2...",(g_PlaceholderName+" Crash").c_str(),MB_OK);
	}
	return false;
}
