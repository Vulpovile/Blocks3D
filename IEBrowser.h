//#include "WindowFunctions.h"
#include <mshtml.h>
#include <exdisp.h>
//#include <Mshtmhst.h>

class IEBrowser {
	public:
		IEBrowser(HWND attachHWnd);
		~IEBrowser(void);
		bool navigateSyncURL(wchar_t* url);
	private:
		IWebBrowser2* webBrowser;
		HWND hwnd;
		IDispatch* spDocument;
};
