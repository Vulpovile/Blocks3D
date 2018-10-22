#include <windows.h>
#include "WindowFunctions.h"
#include "propertyGrid.h"
#include "resource.h"
#include "PropertyWindow.h"

LRESULT CALLBACK PropProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	PropertyWindow *propWind = (PropertyWindow *)GetWindowLongPtr(hwnd, GWL_USERDATA);
	if (propWind==NULL)
	{
		return DefWindowProc(hwnd, msg, wParam, lParam);
	}
	switch(msg)
    {
		case WM_SIZE:
		{
			propWind->onResize();
		}
		break;
		default:
			return DefWindowProc(hwnd, msg, wParam, lParam); 
	}
	return 0; 
}

bool PropertyWindow::onCreate(int x, int y, int sx, int sy, HMODULE hThisInstance) {

	if (!createWindowClass("propHWND",PropProc,hThisInstance))
			return false;
		_hwndProp = CreateWindowEx(
			WS_EX_TOOLWINDOW,
			"propHWND",
			"Prop Test",
			WS_VISIBLE | WS_POPUPWINDOW | WS_THICKFRAME | WS_CAPTION,
			CW_USEDEFAULT,
			CW_USEDEFAULT,
			300,
			660,
			NULL, // parent
			NULL, // menu
			hThisInstance,
			NULL
		);

		_propGrid = New_PropertyGrid(_hwndProp,IDC_PROPERTYGRID);

		PROPGRIDITEM pItem;
		PropGrid_ItemInit(pItem);

		pItem.lpszCatalog="Test";
		pItem.lpszPropName="Test2";
		pItem.lpszzCmbItems="What";
		pItem.lpszPropDesc="Description";
		pItem.lpCurValue=0;

		pItem.iItemType=PIT_EDIT;
		PropGrid_Enable(_propGrid,true);
		ShowWindow(_propGrid,SW_SHOW);
		PropGrid_AddItem(_propGrid,&pItem);
		PropGrid_SetItemHeight(_propGrid,20);
		PropGrid_ShowToolTips(_propGrid,TRUE);
		PropGrid_ShowPropertyDescriptions(_propGrid,TRUE);
		PropGrid_ExpandAllCatalogs(_propGrid);

		SetWindowLongPtr(_propGrid,GWL_USERDATA,(LONG)this);
		_redraw(_hwndProp);

		return true;
}

PropertyWindow::PropertyWindow(int x, int y, int sx, int sy, HMODULE hThisInstance) {
	onCreate(x, y, sx, sy, hThisInstance);
}

void PropertyWindow::onResize()
{
	_redraw(_hwndProp);
}

void PropertyWindow::_redraw(HWND hwnd)
{
	RECT rect;
	GetClientRect(hwnd,&rect);
	SetWindowPos(_propGrid, NULL, 0, 0, rect.right, rect.bottom, SWP_NOMOVE | SWP_NOZORDER | SWP_NOACTIVATE);
}

