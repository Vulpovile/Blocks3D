//#include "WindowFunctions.h"
#pragma once
#include "Globals.h"
#pragma once
#include <mshtml.h>
#include <exdisp.h>
#include <Mshtmhst.h>
#include "IEDispatcher.h"
#include "AudioPlayer.h"

class IEBrowser {
	public:
		IEBrowser(HWND attachHWnd);
		~IEBrowser(void);
		bool navigateSyncURL(wchar_t* url);
		HRESULT doExternal(std::wstring funcName,
  DISPID dispIdMember,
  REFIID riid,
  LCID lcid,
  WORD wFlags,
  DISPPARAMS FAR* pDispParams,
  VARIANT FAR* pVarResult,
  EXCEPINFO FAR* pExcepInfo,
  unsigned int FAR* puArgErr);
	private:
		IWebBrowser2* webBrowser;
		HWND parentHwnd;
};
