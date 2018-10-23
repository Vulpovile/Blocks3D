#define _WINSOCKAPI_
#include <windows.h>
#include "WindowFunctions.h"
#include "resource.h"
#include "PropertyWindow.h"

/*typedef struct typPRGP {
    Instance* instance;   // Declare member types
    Property &prop;
} PRGP;*/

std::vector<PROPGRIDITEM> prop;
Instance* selectedInstance;
LRESULT CALLBACK PropProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	PropertyWindow *propWind = (PropertyWindow *)GetWindowLongPtr(hwnd, GWL_USERDATA);
	if (propWind==NULL)
	{
		return DefWindowProc(hwnd, msg, wParam, lParam);
	}
	switch(msg)
    {
		case WM_CLOSE:
		{
			ShowWindow(hwnd, SW_HIDE);
		}
		break;
		case WM_SIZE:
		{
			propWind->onResize();
		}
		break;
		case WM_NOTIFY:
		{
			switch(((LPNMHDR)lParam)->code)
            {
                case PGN_PROPERTYCHANGE:
				{
					if (IDC_PROPERTYGRID==wParam) {
                        LPNMHDR pnm = (LPNMHDR)lParam;
                        LPNMPROPGRID lpnmp = (LPNMPROPGRID)pnm;
                        LPPROPGRIDITEM item = PropGrid_GetItemData(pnm->hwndFrom,lpnmp->iIndex);
						selectedInstance->PropUpdate(item);
                    }
				}
                break;
            }
            //MessageBox(NULL,"Test","Test",0);
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
			"PropertyGrid",
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
		pItem.lpszPropName="Offset";
		pItem.lpszzCmbItems="What";
		pItem.lpszPropDesc="Description";
		pItem.lpCurValue=(LPARAM)"0, 0, 0";

		pItem.iItemType=PIT_EDIT;

		PROPGRIDITEM pItem2;
		PropGrid_ItemInit(pItem2);

		pItem2.lpszCatalog="Test";
		pItem2.lpszPropName="s";
		pItem2.lpszzCmbItems="itemlist\0itemlist2\0itemlist3";
		pItem2.lpszPropDesc="";
		pItem2.lpCurValue=0;

		pItem2.iItemType=PIT_COMBO;

		/*PROPGRIDITEM FauxExplorerItem;
		PropGrid_ItemInit(FauxExplorerItem);
		FauxExplorerItem.lpszCatalog="Test";
		FauxExplorerItem.lpszPropName = "Editable Combo Field";
		FauxExplorerItem.lpszzCmbItems = "Test1\0Test2\0Test3";
		FauxExplorerItem.lpszPropDesc = "Press F4 to view drop down.";
		FauxExplorerItem.iItemType = PIT_EDITCOMBO;
		FauxExplorerItem.lpCurValue = 1;
		PropGrid_AddItem(_propGrid, &FauxExplorerItem);*/

		PropGrid_Enable(_propGrid,true);
		ShowWindow(_propGrid,SW_SHOW);
		PropGrid_AddItem(_propGrid,&pItem);
		PropGrid_AddItem(_propGrid,&pItem2);
		PropGrid_SetItemHeight(_propGrid,20);
		PropGrid_ShowToolTips(_propGrid,TRUE);
		PropGrid_ShowPropertyDescriptions(_propGrid,TRUE);
		PropGrid_ExpandAllCatalogs(_propGrid);

		SetWindowLongPtr(_hwndProp,GWL_USERDATA,(LONG)this);
		_redraw();

		return true;
}

PropertyWindow::PropertyWindow(int x, int y, int sx, int sy, HMODULE hThisInstance) {
	onCreate(x, y, sx, sy, hThisInstance);
}

void PropertyWindow::onResize()
{
	_redraw();
}

void PropertyWindow::_redraw()
{
	RECT rect;
	GetClientRect(_hwndProp,&rect);
	SetWindowPos(_propGrid, NULL, 0, 20, rect.right, rect.bottom-20, SWP_NOZORDER | SWP_NOACTIVATE);
}

void PropertyWindow::SetProperties(Instance * instance)
{
	PropGrid_ResetContent(_propGrid);
	prop = instance->getProperties();
	selectedInstance = instance;
	for(size_t i = 0; i < prop.size(); i++)
	{
		::PROPGRIDITEM item = prop.at(i);
		PropGrid_AddItem(_propGrid, &item);
		//PRGP propgp;
		//propgp.instance = instance;
		//propgp.prop = prop.at(i);
	}
	PropGrid_ExpandAllCatalogs(_propGrid);
	SetWindowLongPtr(_propGrid,GWL_USERDATA,(LONG)this);
	_redraw();
}