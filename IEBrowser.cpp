#ifndef WIN32_LEAN_AND_MEAN
	#define WIN32_LEAN_AND_MEAN
#endif


#include <windows.h>

#include "IEBrowser.h"
#include "Globals.h"
#pragma once
#include "ax.h"

HRESULT IEBrowser::doExternal(std::wstring funcName,
  DISPID dispIdMember,
  REFIID riid,
  LCID lcid,
  WORD wFlags,
  DISPPARAMS FAR* pDispParams,
  VARIANT FAR* pVarResult,
  EXCEPINFO FAR* pExcepInfo,
  unsigned int FAR* puArgErr)
{
	if (funcName==L"Insert")
	{
		
		MessageBoxW(NULL, pDispParams->rgvarg->bstrVal,L"Add insert here...",MB_OK);
		return S_OK;
	}
	else if (funcName==L"ToggleHopperBin")
	{
		MessageBox(NULL, "BOOP", "Boopity boop",MB_OK);
	}
	else if (funcName==L"SetController")
	{
		bool ding = false;
		//int len = SysStringLen(pDispParams->rgvarg->bstrVal)+1;
		//char * args = new char[len];
		//WideCharToMultiByte(CP_ACP, 0, pDispParams->rgvarg->bstrVal, len, args, len, NULL, (LPBOOL)TRUE);
		if(pDispParams->rgvarg->intVal < 0 || pDispParams->rgvarg->intVal > 7)
			return S_OK;
		Enum::Controller::Value cont = (Enum::Controller::Value)pDispParams->rgvarg->intVal;
		for(size_t i = 0; i < g_selectedInstances.size(); i++)
		{
			if(PVInstance* part = dynamic_cast<PVInstance*>(g_selectedInstances.at(i)))
			{
				ding = true;
				part->controller = cont;
			}
		}
		if(ding)
			AudioPlayer::playSound(dingSound);
		return S_OK;
	}
	else
	{
		return E_NOTIMPL;
	}
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
	//MSG messages;
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
