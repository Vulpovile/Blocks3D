#include "DataModelV2/LevelInstance.h"
#include "Globals.h"
#include "SplashHTML.h"
#include <windows.h>
#include <MsHTML.h>
#include <Exdisp.h>
#include <ExDispid.h>
#include <shlwapi.h>

int SplashHTMLLoad(std::string strHTML)
{
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
		browser->Navigate(URL, &empty, &empty, &empty, &empty);
        SysFreeString(URL);

        ShowBrowserResult = browser->put_Visible(VARIANT_TRUE);
        browser->Release();
    }

    CoUninitialize();
    return 0;
}