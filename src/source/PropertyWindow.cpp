#define _WINSOCKAPI_
#include <windows.h>
#include "WindowFunctions.h"
#include "resource.h"
#include "PropertyWindow.h"
#include "strsafe.h"
#include "Application.h"

std::vector<PROPGRIDITEM> prop;
std::vector<Instance*> children;
Instance * selectedInstance;
Instance * parent = NULL;
const int CX_BITMAP = 16;
const int CY_BITMAP = 16;


HBITMAP CreateBitmapMask(HBITMAP hbmColour, COLORREF crTransparent)
{
    HDC hdcMem, hdcMem2;
    HBITMAP hbmMask;
    BITMAP bm;

    // Create monochrome (1 bit) mask bitmap.  

    GetObject(hbmColour, sizeof(BITMAP), &bm);
    hbmMask = CreateBitmap(bm.bmWidth, bm.bmHeight, 1, 1, NULL);

    // Get some HDCs that are compatible with the display driver

    hdcMem = CreateCompatibleDC(0);
    hdcMem2 = CreateCompatibleDC(0);

    SelectObject(hdcMem, hbmColour);
    SelectObject(hdcMem2, hbmMask);

    // Set the background colour of the colour image to the colour
    // you want to be transparent.
    SetBkColor(hdcMem, crTransparent);

    // Copy the bits from the colour image to the B+W mask... everything
    // with the background colour ends up white while everythig else ends up
    // black...Just what we wanted.

    BitBlt(hdcMem2, 0, 0, bm.bmWidth, bm.bmHeight, hdcMem, 0, 0, SRCCOPY);

    // Take our new mask and use it to turn the transparent colour in our
    // original colour image to black so the transparency effect will
    // work right.
    BitBlt(hdcMem, 0, 0, bm.bmWidth, bm.bmHeight, hdcMem2, 0, 0, SRCINVERT);

    // Clean up.

    DeleteDC(hdcMem);
    DeleteDC(hdcMem2);

    return hbmMask;
}

LRESULT CALLBACK PropProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	TCHAR achTemp[256];
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
		case WM_DRAWITEM:
			{
				COLORREF clrBackground;
				COLORREF clrForeground;
				TEXTMETRIC tm;
				int x;
				int y;
				HRESULT hr;
				size_t cch;

				LPDRAWITEMSTRUCT lpdis = (LPDRAWITEMSTRUCT) lParam;
			       
				if (lpdis->itemID == -1) // Empty item)
					break;

				// Get the food icon from the item data.
				HBITMAP hbmIcon = LoadBitmap(GetModuleHandle(NULL), MAKEINTRESOURCE(IDB_BITMAP1));
				HBITMAP hbmMask = CreateBitmapMask(hbmIcon, RGB(255, 0, 220));
				// The colors depend on whether the item is selected.
				clrForeground = SetTextColor(lpdis->hDC, 
					GetSysColor(lpdis->itemState & ODS_SELECTED ?
					COLOR_HIGHLIGHTTEXT : COLOR_WINDOWTEXT));

				clrBackground = SetBkColor(lpdis->hDC, 
					GetSysColor(lpdis->itemState & ODS_SELECTED ?
					COLOR_HIGHLIGHT : COLOR_WINDOW));

				// Calculate the vertical and horizontal position.
				GetTextMetrics(lpdis->hDC, &tm);
				y = (lpdis->rcItem.bottom + lpdis->rcItem.top - tm.tmHeight) / 2;
				x = LOWORD(GetDialogBaseUnits()) / 4;

				// Get and display the text for the list item.
				int mul = 0;
				SendMessage(lpdis->hwndItem, CB_GETLBTEXT, lpdis->itemID, (LPARAM) achTemp);
				
				if(lpdis->itemID >= 0)
				{
					mul = children[lpdis->itemID]->listicon;
				}
				//else mul = children[lpdis->itemID-1]->listicon;

				//mul = children[lpdis->itemID]->listicon;

				hr = StringCchLength(achTemp, 256, &cch);
				if (FAILED(hr))
				{
					// TODO: Write error handler.
				}

				ExtTextOut(lpdis->hDC, CX_BITMAP + 2 * x, y,
					ETO_CLIPPED | ETO_OPAQUE, &lpdis->rcItem,
					achTemp, (UINT)cch, NULL);

				// Restore the previous colors.
				SetTextColor(lpdis->hDC, clrForeground);
				SetBkColor(lpdis->hDC, clrBackground);
			    
				//  Draw the food icon for the item. 
				HDC hdc = CreateCompatibleDC(lpdis->hDC); 
				if (hdc == NULL) 
					break; 
			 
				SelectObject(hdc, hbmMask); 
				BitBlt(lpdis->hDC, x, lpdis->rcItem.top, 
					CX_BITMAP, CY_BITMAP, hdc, mul*16, 0, SRCAND); 
			 
				SelectObject(hdc, hbmIcon); 
				BitBlt(lpdis->hDC, x, lpdis->rcItem.top, 
					CX_BITMAP, CY_BITMAP, hdc, mul*16, 0, SRCPAINT); 
			 
				DeleteDC(hdc); 
			  
				// If the item has the focus, draw the focus rectangle.
				if (lpdis->itemState & ODS_FOCUS)
					DrawFocusRect(lpdis->hDC, &lpdis->rcItem);

		    
			}
		break;
		case WM_MEASUREITEM:
		{
			LPMEASUREITEMSTRUCT lpmis = (LPMEASUREITEMSTRUCT) lParam;
			if (lpmis->itemHeight < 18)
				lpmis->itemHeight = 18;
		}
		break;
		case WM_SIZE:
		{
			propWind->onResize();
		}
		break;
		case WM_COMMAND:
			{
				if(HIWORD(wParam) == CBN_SELCHANGE)
				{ 
					int ItemIndex = SendMessage((HWND) lParam, (UINT) CB_GETCURSEL, (WPARAM) 0, (LPARAM) 0);
					CHAR  ListItem[256];
					SendMessage((HWND) lParam, (UINT) CB_GETLBTEXT, (WPARAM) ItemIndex, (LPARAM) ListItem); 
					g_dataModel->getSelectionService()->clearSelection();
					g_dataModel->getSelectionService()->addSelected(children.at(ItemIndex));
				}
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
						//propWind->UpdateSelected(selectedInstance);
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

void PropertyWindow::clearExplorer()
{
	SendMessage(_explorerComboBox,CB_RESETCONTENT,0,0); 
	SendMessage(_explorerComboBox,CB_SETCURSEL,0,(LPARAM)0);
}

void PropertyWindow::refreshExplorer(std::vector<Instance*> selectedInstances)
{
	Instance * instance = selectedInstances[0];
	SendMessage(_explorerComboBox,CB_RESETCONTENT,0,0); 
	parent = NULL;
	children.clear();
	children.push_back(selectedInstance);
	SendMessage(_explorerComboBox, CB_ADDSTRING, 0, (LPARAM)selectedInstance->name.c_str()); 
	if(selectedInstance->getParent() != NULL)
	{
		std::string title = ".. (";
		title += selectedInstance->getParent()->name;
		title += ")";
		SendMessage(_explorerComboBox,CB_ADDSTRING, 0,(LPARAM)title.c_str());
		parent = selectedInstance->getParent();
		children.push_back(selectedInstance->getParent());
	}

	std::vector<Instance*> selectedChildren = selectedInstance->getChildren();
	for(size_t z = 0; z < selectedChildren.size(); z++)
	{
		children.push_back(selectedChildren.at(z));
		SendMessage(_explorerComboBox,CB_ADDSTRING, 0,(LPARAM)selectedChildren.at(z)->name.c_str()); 
	}
	//g_usableApp->selectInstance(selectedInstance, this);
	SendMessage(_explorerComboBox,CB_SETCURSEL,0,(LPARAM)0);
	//}
}

bool PropertyWindow::onCreate(int x, int y, int sx, int sy, HMODULE hThisInstance) {
	if (!createWindowClass("propHWND",PropProc,hThisInstance))
			return false;

		_hwndProp = CreateWindowEx(
			WS_EX_TOOLWINDOW,
			"propHWND",
			"PropertyGrid",
			WS_POPUPWINDOW | WS_THICKFRAME | WS_CAPTION,
			CW_USEDEFAULT,
			CW_USEDEFAULT,
			300,
			660,
			NULL, // parent
			NULL, // menu
			hThisInstance,
			NULL
		);
		
		_explorerComboBox = CreateWindowEx(
			NULL,
			"COMBOBOX",
			"Combo",
			WS_VISIBLE | WS_CHILD | CBS_DROPDOWNLIST | CBS_OWNERDRAWFIXED | CBS_HASSTRINGS ,
			0,
			0,
			0,
			0,
			_hwndProp, // parent
			NULL, // menu
			hThisInstance,
			NULL
		);
		SendMessage(_explorerComboBox, WM_SETFONT, (WPARAM)GetStockObject(DEFAULT_GUI_FONT), 0);

		_propGrid = New_PropertyGrid(_hwndProp,IDC_PROPERTYGRID);

		/*PROPGRIDITEM pItem;
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
//		PropGrid_AddItem(_propGrid,&pItem);
//		PropGrid_AddItem(_propGrid,&pItem2);
		PropGrid_SetItemHeight(_propGrid,20);
		PropGrid_ShowToolTips(_propGrid,TRUE);
		PropGrid_ShowPropertyDescriptions(_propGrid,TRUE);
		PropGrid_ExpandAllCatalogs(_propGrid);
		
		
		SetWindowLongPtr(_hwndProp,GWL_USERDATA,(LONG)this);

		//refreshExplorer();
		_resize();

		return true;
}

PropertyWindow::PropertyWindow(int x, int y, int sx, int sy, HMODULE hThisInstance) {
	onCreate(x, y, sx, sy, hThisInstance);
}

void PropertyWindow::onResize()
{
	_resize();
}

void PropertyWindow::_resize()
{
	RECT rect;
	GetClientRect(_hwndProp,&rect);
	SetWindowPos(_propGrid, NULL, 0, 20, rect.right, rect.bottom-20, SWP_NOZORDER | SWP_NOACTIVATE);
	SetWindowPos(_explorerComboBox, NULL, 0, 0, rect.right, 400, SWP_NOMOVE | SWP_NOZORDER | SWP_NOACTIVATE);
}

void PropertyWindow::UpdateSelected(std::vector<Instance *> instances)
{
	if(instances.size() <= 0)
	{
		ClearProperties();
		return;
	}
	Instance * instance = instances[0];
	PropGrid_ResetContent(_propGrid);
	prop = instance->getProperties();
	//if (selectedInstance != instance)
	{
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
		//SetWindowLongPtr(_propGrid,GWL_USERDATA,(LONG)this);

		refreshExplorer(instances);
		_resize();
	}
}

void PropertyWindow::ClearProperties()
{
	clearExplorer();
	PropGrid_ResetContent(_propGrid);
}