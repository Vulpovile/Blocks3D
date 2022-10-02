#include "DataModelV2/LevelInstance.h"
#include "Globals.h"
#include "SplashHTML.h"
#include <windows.h>
#include <MsHTML.h>
#include <Exdisp.h>
#include <ExDispid.h>
#include <shlwapi.h>

int SplashHTMLLoad(std::string strHTML)
//void CreateHTMLContainer()
{
	HWND NewWindow = CreateWindowEx(
		WS_EX_TOOLWINDOW,
		"", 
		"", 
		WS_OVERLAPPEDWINDOW|WS_VISIBLE, 
		0, 
		0, 
		500, 
		300, 
		0, 
		0, 
		HINSTANCE(NULL), 
		NULL); 
	ShowWindow(NewWindow, 1);
    UpdateWindow(NewWindow); 
	return 0;
}
int SplashHTMLLoadz(std::string strHTML)
{
	//CreateHTMLContainer();
	printf("%s \n", strHTML.c_str());
    CoInitialize(NULL);

    HRESULT InstanciateIEResult;
    HRESULT NavigateResult;
    HRESULT ShowBrowserResult;

    VARIANT empty;
    VariantInit(&empty);

    IWebBrowser2* browser = NULL;
    HRESULT hr = CoCreateInstance(CLSID_InternetExplorer, NULL,
            CLSCTX_LOCAL_SERVER, IID_IWebBrowser2, (void**)&browser);
	
	std::wstring HtmlWide;
	HtmlWide.assign( strHTML.begin(), strHTML.end() );

    if (browser)
    {
		BSTR URL = SysAllocString(L"about:blank");
		browser->put_AddressBar(false);
		browser->put_ToolBar(false);
		browser->put_TheaterMode(false);
		browser->put_Width(500);
		browser->put_Height(300);
		browser->Navigate(URL, &empty, &empty, &empty, &empty);
        SysFreeString(URL);

        ShowBrowserResult = browser->put_Visible(VARIANT_TRUE);
        browser->Release();
    }

    CoUninitialize();
    return 0;
}