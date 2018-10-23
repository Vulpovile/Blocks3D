//#include "WindowFunctions.h"
#pragma once
#include <mshtml.h>
#include <exdisp.h>
//#include <Mshtmhst.h>

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
};
