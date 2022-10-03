#include "DataModelV2/LevelInstance.h"
#include "Globals.h"
#include "SplashHTML.h"
#include <windows.h>
#include <MsHTML.h>
#include <Exdisp.h>
#include <ExDispid.h>
#include <shlwapi.h>

void SplashHTMLContainer()
{
	HWND invisWindowHandle = CreateWindowEx(WS_EX_TOOLWINDOW,
	      "htmlWindow",
	      "Splash",
	      WS_OVERLAPPEDWINDOW & ~WS_MAXIMIZEBOX & ~WS_THICKFRAME,
	      200,
	      200,
	      500,
	      300,
	      NULL,
	      NULL,
	      NULL,
	      NULL);
	printf("Creating Window HWND: %u\n", invisWindowHandle);
	ShowWindow(invisWindowHandle, 1);
	UpdateWindow(invisWindowHandle);
}
int SplashHTMLLoad(std::string strHTML)
{
	IHTMLDocument2 *document = new IHTMLDocument2{}; // Declared earlier in the code
    BSTR bstr = SysAllocString(OLESTR("Written by IHTMLDocument2::write()."));
    // Creates a new one-dimensional array
    SAFEARRAY *psaStrings = SafeArrayCreateVector(VT_VARIANT, 0, 1);
    if (psaStrings == NULL) {
        goto cleanup;
    }
    VARIANT *param;
    HRESULT hr = SafeArrayAccessData(psaStrings, (LPVOID*)&param);
    param->vt = VT_BSTR;
    param->bstrVal = bstr;
    hr = SafeArrayUnaccessData(psaStrings);
    hr = document->write(psaStrings);
cleanup:
    // SafeArrayDestroy calls SysFreeString for each BSTR
    if (psaStrings != NULL) {
        SafeArrayDestroy(psaStrings);
    }
	return 0;
}
int PLACEHOLDER(std::wstring strHTML)
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