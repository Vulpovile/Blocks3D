//#include "WindowFunctions.h"
#pragma once
#include <mshtml.h>
#include <exdisp.h>
#include <Mshtmhst.h>
#include "IEDispatcher.h"

class IEBrowser {
	public:
		IEBrowser(HWND attachHWnd);
		~IEBrowser(void);
		bool navigateSyncURL(wchar_t* url);
		void Boop(char* test);
	private:
		IWebBrowser2* webBrowser;
		HWND hwnd;
		IDispatch* spDocument;
		IHTMLDocument* spDocument2;
		IDocHostUIHandler* m_spHandler;
		IDispatch* m_spExternal;
		IDispatch* m_newExternal;
		IEDispatcher m_IEDispatcher;
		IOleClientSite* m_spDefaultDocHostUIHandler;
		int setExternal(IDispatch** ext);
};
