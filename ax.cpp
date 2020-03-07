// AX.CPP
#include <windows.h>
#include <comdef.h>
#include <exdisp.h>
#include <oledlg.h>
#include "ax.h"


#pragma warning (disable: 4311)
#pragma warning (disable: 4312)
#pragma warning (disable: 4244)
#pragma warning (disable: 4800)

// AXClientSite class
// ------- Implement member functions
AXClientSite :: AXClientSite()
   {
   refNum = 0;
   CalledCanInPlace = 0;
	InPlace = 0;
   }

AXClientSite :: ~AXClientSite()
	{
   }


STDMETHODIMP AXClientSite :: ShowContextMenu(DWORD dwID, POINT *ppt, IUnknown *pcmdtReserved, IDispatch *pdispReserved)
{
	return E_NOTIMPL;
}

STDMETHODIMP AXClientSite :: GetHostInfo(DOCHOSTUIINFO *pInfo)
{
	return E_NOTIMPL;
}

STDMETHODIMP AXClientSite :: ShowUI( DWORD dwID, IOleInPlaceActiveObject *pActiveObject, IOleCommandTarget *pCommandTarget, IOleInPlaceFrame *pFrame, IOleInPlaceUIWindow *pDoc)
{
	return E_NOTIMPL;
}

STDMETHODIMP AXClientSite :: HideUI( void)
{
	return E_NOTIMPL;
}

STDMETHODIMP AXClientSite :: UpdateUI( void)
{
	return E_NOTIMPL;
}

STDMETHODIMP AXClientSite :: OnDocWindowActivate(BOOL fActivate)
{
	return E_NOTIMPL;
}

STDMETHODIMP AXClientSite :: OnFrameWindowActivate(BOOL fActivate)
{
	return E_NOTIMPL;
}

STDMETHODIMP AXClientSite :: ResizeBorder( LPCRECT prcBorder, IOleInPlaceUIWindow *pUIWindow, BOOL fRameWindow)
{
	return E_NOTIMPL;
}

STDMETHODIMP AXClientSite :: TranslateAccelerator( LPMSG lpMsg, const GUID *pguidCmdGroup, DWORD nCmdID)
{
	return E_NOTIMPL;
}

STDMETHODIMP AXClientSite :: GetOptionKeyPath( LPOLESTR *pchKey, DWORD dw)
{
	return E_NOTIMPL;
}

STDMETHODIMP AXClientSite :: GetDropTarget( IDropTarget *pDropTarget, IDropTarget **ppDropTarget)
{
	return E_NOTIMPL;
}

STDMETHODIMP AXClientSite :: GetExternal(IDispatch **ppDispatch)
{
	//IDispatch* disp = ax->GetExternalDispatch();
	*ppDispatch = this;
	/* if (disp!=NULL)
	{
		*ppDispatch = this;
		return S_OK;
	} */
	return S_OK;
}

STDMETHODIMP AXClientSite ::TranslateUrl( DWORD dwTranslate, OLECHAR *pchURLIn, OLECHAR **ppchURLOut)
{
	return E_NOTIMPL;
}

STDMETHODIMP AXClientSite :: FilterDataObject( IDataObject *pDO, IDataObject **ppDORet)
{
	return E_NOTIMPL;
}

// IUnknown methods
STDMETHODIMP AXClientSite :: QueryInterface(REFIID iid,void**ppvObject)
      {
      *ppvObject = 0;
      if (iid == IID_IOleClientSite)
         *ppvObject = (IOleClientSite*)this;
      if (iid == IID_IUnknown)
         *ppvObject = this;
      if (iid == IID_IAdviseSink)
         *ppvObject = (IAdviseSink*)this;
      if (iid == IID_IDispatch)
         *ppvObject = (IDispatch*)this;
      if (ExternalPlace == false)
      	{
	      if (iid == IID_IOleInPlaceSite)
	         *ppvObject = (IOleInPlaceSite*)this;
	      if (iid == IID_IOleInPlaceFrame)
	         *ppvObject = (IOleInPlaceFrame*)this;
	      if (iid == IID_IOleInPlaceUIWindow)
	         *ppvObject = (IOleInPlaceUIWindow*)this;
		  if (iid == IID_IDocHostUIHandler)
	         *ppvObject = (IDocHostUIHandler*)this;
         }

      //* Log Call
      if (*ppvObject)
         {
         AddRef();
         return S_OK;
         }
      return E_NOINTERFACE;
      }

STDMETHODIMP_(ULONG)  AXClientSite :: AddRef()
      {
      refNum++;
      return refNum;
      }

STDMETHODIMP_(ULONG)  AXClientSite :: Release()
      {
      refNum--;
      return refNum;
      }


// IOleClientSite methods
STDMETHODIMP AXClientSite :: SaveObject()
      {
      return S_OK;
      }

STDMETHODIMP AXClientSite :: GetMoniker(DWORD dwA,DWORD dwW,IMoniker**pm)
      {
      *pm = 0;
      return E_NOTIMPL;
      }

STDMETHODIMP AXClientSite :: GetContainer(IOleContainer**pc)
      {
      *pc = 0;
      return E_FAIL;
      }

STDMETHODIMP AXClientSite :: ShowObject()
      {
      return S_OK;
      }

STDMETHODIMP AXClientSite :: OnShowWindow(BOOL f)
      {
      InvalidateRect(Window, 0, TRUE);
      InvalidateRect(Parent, 0, TRUE);
      return S_OK;
      }

STDMETHODIMP AXClientSite :: RequestNewObjectLayout()
      {
      return S_OK;
      }

STDMETHODIMP_(void) AXClientSite :: OnViewChange(DWORD dwAspect,LONG lIndex)
      {
      }

STDMETHODIMP_(void) AXClientSite :: OnRename(IMoniker * pmk)
      {
      }

STDMETHODIMP_(void) AXClientSite :: OnSave()
      {
      }

STDMETHODIMP_(void) AXClientSite :: OnClose()
      {
      }


   // IOleInPlaceSite methods
STDMETHODIMP AXClientSite :: GetWindow(HWND *p)
      {
      *p = Window;
      return S_OK;
      }

STDMETHODIMP AXClientSite :: ContextSensitiveHelp(BOOL)
      {
      return E_NOTIMPL;
      }


STDMETHODIMP AXClientSite :: CanInPlaceActivate()
      {
      if (InPlace)
         {
         CalledCanInPlace = true;
         return S_OK;
         }
      return S_FALSE;
      }

STDMETHODIMP AXClientSite :: OnInPlaceActivate()
      {
      return S_OK;
      }

STDMETHODIMP AXClientSite :: OnUIActivate()
      {
      return S_OK;
      }

STDMETHODIMP AXClientSite :: GetWindowContext(IOleInPlaceFrame** ppFrame,IOleInPlaceUIWindow **ppDoc,LPRECT r1,LPRECT r2,LPOLEINPLACEFRAMEINFO o)
      {
      *ppFrame = (IOleInPlaceFrame*)this;
      AddRef();

      *ppDoc = NULL;
      GetClientRect(Window,r1);
      GetClientRect(Window,r2);
      o->cb = sizeof(OLEINPLACEFRAMEINFO);
      o->fMDIApp = false;
      o->hwndFrame = Parent;
      o->haccel = 0;
      o->cAccelEntries = 0;

      return S_OK;
      }

STDMETHODIMP AXClientSite :: Scroll(SIZE s)
      {
      return E_NOTIMPL;
      }

STDMETHODIMP AXClientSite :: OnUIDeactivate(int)
      {
      return S_OK;
      }

STDMETHODIMP AXClientSite :: OnInPlaceDeactivate()
      {
      return S_OK;
      }

STDMETHODIMP AXClientSite :: DiscardUndoState()
      {
      return S_OK;
      }

STDMETHODIMP AXClientSite :: DeactivateAndUndo()
      {
      return S_OK;
      }

STDMETHODIMP AXClientSite :: OnPosRectChange(LPCRECT)
      {
      return S_OK;
      }


// IOleInPlaceFrame methods
 STDMETHODIMP AXClientSite :: GetBorder(LPRECT l)
      {
      GetClientRect(Window,l);
      return S_OK;
      }

STDMETHODIMP AXClientSite :: RequestBorderSpace(LPCBORDERWIDTHS b)
      {
      //return S_OK;
      return E_NOTIMPL;
      }

STDMETHODIMP AXClientSite :: SetBorderSpace(LPCBORDERWIDTHS b)
      {
      return S_OK;
      }

STDMETHODIMP AXClientSite :: SetActiveObject(IOleInPlaceActiveObject*pV,LPCOLESTR s)
      {
      ax->Pao = pV;
      return S_OK;
      }


STDMETHODIMP AXClientSite :: SetStatusText(LPCOLESTR t)
{
      return E_NOTIMPL;
}

STDMETHODIMP AXClientSite :: EnableModeless(BOOL f)
      {
      return E_NOTIMPL;
      }

STDMETHODIMP AXClientSite :: TranslateAccelerator(LPMSG,WORD)
      {
      return E_NOTIMPL;
      }


// IDispatch Methods
HRESULT _stdcall AXClientSite :: GetTypeInfoCount(
        unsigned int * pctinfo) {return E_NOTIMPL;}

HRESULT _stdcall AXClientSite :: GetTypeInfo(
  unsigned int iTInfo,
  LCID lcid,
  ITypeInfo FAR* FAR* ppTInfo)
{
	  return E_NOTIMPL;
}

HRESULT _stdcall AXClientSite :: GetIDsOfNames(
  REFIID riid,
  OLECHAR FAR* FAR* ext_function_name,
  unsigned int cNames,
  LCID lcid,
  DISPID FAR* )
{
	m_lastExternalName = *ext_function_name;
	return S_OK;
}


// Other Methods
void AX :: Init(char* cls)
	{
   wchar_t x[1000] = {0};
   MultiByteToWideChar(CP_ACP,0,cls,-1,x,1000);
   CLSIDFromString(x,&clsid);
   iid = (IID*)&IID_IOleObject;
   OleObject = 0;
   Storage = 0;
   View = 0;
   Data = 0;
   Unk = 0;
   Pao = 0;
   AdviseToken = 0;
   memset(DAdviseToken,0,sizeof(DAdviseToken));
   Site.ax = this;
	m_externalDisp = 0;
	}

AX :: AX(char* cls)
   {
	Init(cls);
   }


void AX :: SetExternalDispatch(IDispatch* externalDisp)
{
	m_externalDisp = externalDisp;
}

IDispatch* AX :: GetExternalDispatch()
{
	return m_externalDisp;
}

void AX :: Clean()
      {
      if (Site.InPlace == true)
        {
        Site.InPlace = false;
        IOleInPlaceObject* iib = 0;
        if (OleObject)
          OleObject->QueryInterface(IID_IOleInPlaceObject,(void**)&iib);
        if (iib)
          {
          iib->UIDeactivate();
          iib->InPlaceDeactivate();
          iib->Release();
          }
        }

      if (AdviseToken && OleObject)
        {
        OleObject->Unadvise(AdviseToken);
        AdviseToken = 0;
        }
      if (Data)
        {
        for(int i = 0 ; i < 100 ; i++)
          if (DAdviseToken[i])
            Data->DUnadvise(DAdviseToken[i]);
        memset(DAdviseToken,0,sizeof(DAdviseToken));
        }


      if (Pao) Pao->Release();
      if (Unk) Unk->Release();
      if (Data) Data->Release();
      if (View) View->Release();
      if (Storage) Storage->Release();
      if (OleObject) OleObject->Release();
      Unk = 0;
      Data = 0;
      View = 0;
      Storage = 0;
      OleObject = 0;

	}

AX :: ~AX()
	{
	Clean();
   }

CLSID AX :: GetCLSID()
      {
      return clsid;
      }

HRESULT _stdcall AXClientSite :: InsertMenus(HMENU h,LPOLEMENUGROUPWIDTHS x)
      {
/*      AX * t = (AX*)ax;
      if (t->AddMenu)
        {
        x->width[0] = 0;
        x->width[2] = 0;
        x->width[4] = 0;
        //InsertMenu(h,0,MF_BYPOSITION | MF_POPUP,(int)Menu,"test");
        return S_OK;
        }
*/
		return E_NOTIMPL;
      }
HRESULT _stdcall AXClientSite :: SetMenu(HMENU h,HOLEMENU hO,HWND hw)
      {
      AX * t = (AX*)ax;
/*      if (t->AddMenu)
        {
        if (!h && !hO)
           {
           //::SetMenu(Window,Menu);
           //DrawMenuBar(Window);
           ::SetMenu(Parent,Menu);
           DrawMenuBar(Parent);
           return S_OK;
           }

        //::SetMenu(Window,h);
        //DrawMenuBar(Window);

        //HMENU hm = GetMenu(Parent);
        //AppendMenu(hm,MF_POPUP | MF_MENUBREAK,(int)h,0);
        //::SetMenu(Parent,hm);
        ::SetMenu(Parent,h);
        DrawMenuBar(Parent);

        //hOleWindow = hw;
        //OleSetMenuDescriptor(hO,Window,hw,0,0);
        OleSetMenuDescriptor(hO,Parent,hw,0,0);

        return S_OK;
	        }
*/
		return E_NOTIMPL;
      }

HRESULT _stdcall AXClientSite :: RemoveMenus(HMENU h)
      {
      AX * t = (AX*)ax;
      if (t->AddMenu)
        {
        if (!h)
           return S_OK;

        int c = GetMenuItemCount(h);
        for (int i = c ; i >= 0 ; i--)
           {
          HMENU hh = GetSubMenu(h,i);
          if (hh == Menu)
            RemoveMenu(h,i,MF_BYPOSITION);
          }
        if (h == Menu)
          DestroyMenu(h);

        //DrawMenuBar(Window);
        DrawMenuBar(Parent);
        return S_OK;
        }
      return E_NOTIMPL;
      }


HRESULT _stdcall AXClientSite :: Invoke(
  DISPID dispIdMember,
  REFIID riid,
  LCID lcid,
  WORD wFlags,
  DISPPARAMS FAR* pDispParams,
  VARIANT FAR* pVarResult,
  EXCEPINFO FAR* pExcepInfo,
  unsigned int FAR* puArgErr)
{

	if (m_lastExternalName==L"Insert")
	{
		
		MessageBoxW(NULL, pDispParams->rgvarg->bstrVal,L"Add insert here...",MB_OK);
		return S_OK;
	}
	else if (m_lastExternalName==L"Boop")
	{
		MessageBox(NULL, "BOOP", "Boopity boop",MB_OK);
	}
	else
	{
		return E_NOTIMPL;
	}
	return S_OK;
}


void _stdcall AXClientSite :: OnDataChange(FORMATETC *pFormatEtc,STGMEDIUM *pStgmed)
      {
      // Notify our app that a change is being requested
      return;
      }








// Window Procedure for AX control
LRESULT CALLBACK AXWndProc(HWND hh,UINT mm,WPARAM ww,LPARAM ll)
	{
   if (mm == WM_CREATE)
      {
      char tit[1000] = {0};
		HRESULT hr;

      GetWindowTextA(hh,tit,1000);

      AX* ax;
      ax = new AX(tit);

      SetWindowLong(hh,GWL_USERDATA,(LONG)ax);
      ax->Site.Window = hh;
      ax->Site.Parent = GetParent(hh);

      hr = StgCreateDocfile(0,STGM_READWRITE | STGM_SHARE_EXCLUSIVE | STGM_DIRECT | STGM_CREATE,0,&ax->Storage);
      ax->Site.Window = hh;

		REFIID rid = *ax->iid;
      hr = OleCreate(ax->GetCLSID(),rid,OLERENDER_DRAW,0,&ax->Site,ax->Storage,(void**)&ax->OleObject);



      if (!ax->OleObject)
         {
         delete ax;
         SetWindowLong(hh,GWL_USERDATA,0);
         return -1;
         }

     	hr = OleSetContainedObject(ax->OleObject, TRUE);
      hr = ax->OleObject->Advise(&ax->Site,&ax->AdviseToken);
      hr = ax->OleObject->QueryInterface(IID_IViewObject,(void**)&ax->View);
      hr = ax->OleObject->QueryInterface(IID_IDataObject,(void**)&ax->Data);
      if (ax->View)
         hr = ax->View->SetAdvise(DVASPECT_CONTENT,0,&ax->Site);



      return 0;
      }



   if (mm == WM_DESTROY)
      {
      AX* ax = (AX*)GetWindowLong(hh,GWL_USERDATA);
      if (!ax)
         return 0;
		ax->Clean();
      return true;
      }

   if (mm == AX_SETDATAADVISE)
      {
      AX* ax = (AX*)GetWindowLong(hh,GWL_USERDATA);
      if (!ax)
         return 0;

      // 1.Enum available FORMATETC structures
      // 2.Set Data Advise specified to index ww
      if (!ax->Data)
        return 0;

      IEnumFORMATETC* ief = 0;
      int i = 0;

      FORMATETC fe;
      ax->Data->EnumFormatEtc((LPARAM)ll,&ief);
      if (!ief)
        return 0;
      for(;;)
        {
        HRESULT hr = ief->Next(1,&fe,0);
        if (hr != S_OK)
          break;
        if (ww == i)
          break;
        i++;
        }
      ief->Release();
      if (ww == -1)
        return i;

      if (ax->Data)
         ax->Data->DAdvise(&fe,0,&ax->Site,&ax->DAdviseToken[ww]);

      return true;
      }
	if (mm == AX_SETEXTERNALDISP)
	{
		AX* ax = (AX*)GetWindowLong(hh,GWL_USERDATA);
		ax->SetExternalDispatch((IDispatch*)ll);
	}

   if (mm == AX_GETAXINTERFACE)
      {
      AX* ax = (AX*)GetWindowLong(hh,GWL_USERDATA);
      return (LONG)ax;
      }

   if (mm == AX_QUERYINTERFACE)
      {
      char* p = (char*)ww;
      AX* ax = (AX*)GetWindowLong(hh,GWL_USERDATA);
      if (!ax)
         return 0;
      return ax->OleObject->QueryInterface((REFIID)*p,(void**)ll);
      }

	if (mm == WM_LBUTTONDBLCLK)
      {
      PostMessage(hh,AX_INPLACE,1,0);
      return 0;
      }


   if (mm == AX_INPLACE)
      {
      AX* ax = (AX*)GetWindowLong(hh,GWL_USERDATA);
      if (!ax)
        return 0;
      if (!ax->OleObject)
        return 0;
      RECT rect;
		HRESULT hr;
    	::GetClientRect(hh,&rect);

      if (ax->Site.InPlace == false && ww == 1) // Activate In Place
         {
         ax->Site.InPlace = true;
         ax->Site.ExternalPlace = ll;
         hr = ax->OleObject->DoVerb(OLEIVERB_INPLACEACTIVATE,0,&ax->Site,0,hh,&rect);
         InvalidateRect(hh,0,true);
         return 1;
         }

      if (ax->Site.InPlace == true && ww == 0) // Deactivate
         {
         ax->Site.InPlace = false;

         IOleInPlaceObject* iib;
         ax->OleObject->QueryInterface(IID_IOleInPlaceObject,(void**)&iib);
         if (iib)
          {
          iib->UIDeactivate();
          iib->InPlaceDeactivate();
          iib->Release();
          InvalidateRect(hh,0,true);
          return 1;
          }
         }
      return 0;
      }

   if (mm == WM_SIZE)
        {
        AX* ax = (AX*)GetWindowLong(hh,GWL_USERDATA);
        if (!ax)
          return 0;
        if (!ax->OleObject)
          return 0;

        DefWindowProc(hh,mm,ww,ll);

        if (ax->Site.InPlace == true)
				{
            SendMessage(hh,AX_INPLACE,0,0);
            InvalidateRect(hh,0,true);
            SendMessage(hh,AX_INPLACE,1,0);
            }

        IOleInPlaceObject* pl;
        ax->OleObject->QueryInterface(IID_IOleInPlaceObject,(void**)&pl);
        if (!pl)
        	return 0;
        RECT r;
        GetClientRect(ax->Site.Window,&r);
        pl->SetObjectRects(&r,&r);
        pl->Release();
        return 0;
        }

   return DefWindowProc(hh,mm,ww,ll);
	}

// Registration function
ATOM AXRegister()
	{
   WNDCLASSEXA wC = {0};

   wC.cbSize = sizeof(wC);
   wC.style = CS_GLOBALCLASS | CS_DBLCLKS;
   wC.lpfnWndProc = AXWndProc;
   wC.cbWndExtra = 4;
   wC.hInstance = GetModuleHandle(0);
   wC.lpszClassName = "AX";
   return RegisterClassExA(&wC);
	}

