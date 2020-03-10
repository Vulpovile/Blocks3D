// AX.H
#pragma once
#include "Globals.h"
#include <mshtmhst.h>
#include <string>

// messages
#define AX_QUERYINTERFACE (WM_USER + 1)
#define AX_INPLACE (WM_USER + 2)
#define AX_GETAXINTERFACE (WM_USER + 3)
#define AX_CONNECTOBJECT (WM_USER + 4)
#define AX_DISCONNECTOBJECT (WM_USER + 5)
#define AX_SETDATAADVISE (WM_USER + 6)
#define AX_DOVERB (WM_USER + 7)

// Registration function
ATOM AXRegister();


// Class AXClientSide
class AXClientSite :
   public IOleClientSite,
   public IDispatch,
   public IAdviseSink,
   public IOleInPlaceSite,
   public IOleInPlaceFrame,
   public IDocHostUIHandler
   {
   protected:

		int refNum;

   public:

		HWND Window;
		HWND Parent;
		HMENU Menu;
		bool InPlace;
		bool ExternalPlace;
		bool CalledCanInPlace;

		class AX* ax;

	   // MyClientSite Methods
		AXClientSite();
		virtual ~AXClientSite();
		STDMETHODIMP_(void) OnDataChange2(FORMATETC*);

		// IUnknown methods
		STDMETHODIMP QueryInterface(REFIID iid,void**ppvObject);
		STDMETHODIMP_(ULONG) AddRef();
		STDMETHODIMP_(ULONG) Release();

		// IOleClientSite methods
		STDMETHODIMP SaveObject();
		STDMETHODIMP GetMoniker(DWORD dwA,DWORD dwW,IMoniker**pm);
		STDMETHODIMP GetContainer(IOleContainer**pc);
		STDMETHODIMP ShowObject();
		STDMETHODIMP OnShowWindow(BOOL f);
		STDMETHODIMP RequestNewObjectLayout();

		// IDDocHandler methods
		STDMETHODIMP ShowContextMenu( 
            /* [in] */ DWORD dwID,
            /* [in] */ POINT *ppt,
            /* [in] */ IUnknown *pcmdtReserved,
            /* [in] */ IDispatch *pdispReserved);
        
        STDMETHODIMP GetHostInfo( 
            /* [out][in] */ DOCHOSTUIINFO *pInfo);
        
        STDMETHODIMP ShowUI( 
            /* [in] */ DWORD dwID,
            /* [in] */ IOleInPlaceActiveObject *pActiveObject,
            /* [in] */ IOleCommandTarget *pCommandTarget,
            /* [in] */ IOleInPlaceFrame *pFrame,
            /* [in] */ IOleInPlaceUIWindow *pDoc);
        
        STDMETHODIMP HideUI( void);
        
        STDMETHODIMP UpdateUI( void);
        
        STDMETHODIMP OnDocWindowActivate( 
            /* [in] */ BOOL fActivate);
        
        STDMETHODIMP OnFrameWindowActivate( 
            /* [in] */ BOOL fActivate);
        
        STDMETHODIMP ResizeBorder( 
            /* [in] */ LPCRECT prcBorder,
            /* [in] */ IOleInPlaceUIWindow *pUIWindow,
            /* [in] */ BOOL fRameWindow);
        
        STDMETHODIMP TranslateAccelerator( 
            /* [in] */ LPMSG lpMsg,
            /* [in] */ const GUID *pguidCmdGroup,
            /* [in] */ DWORD nCmdID);
        
        STDMETHODIMP GetOptionKeyPath( 
            /* [out] */ LPOLESTR *pchKey,
            /* [in] */ DWORD dw);
        
        STDMETHODIMP GetDropTarget( 
            /* [in] */ IDropTarget *pDropTarget,
            /* [out] */ IDropTarget **ppDropTarget);
        
        STDMETHODIMP GetExternal( 
            /* [out] */ IDispatch **ppDispatch);
        
        STDMETHODIMP TranslateUrl( 
            /* [in] */ DWORD dwTranslate,
            /* [in] */ OLECHAR *pchURLIn,
            /* [out] */ OLECHAR **ppchURLOut);
        
        STDMETHODIMP FilterDataObject( 
            /* [in] */ IDataObject *pDO,
            /* [out] */ IDataObject **ppDORet);

		// IAdviseSink methods
		STDMETHODIMP_(void) OnDataChange(FORMATETC *pFormatEtc,STGMEDIUM *pStgmed);
	
	   STDMETHODIMP_(void) OnViewChange(DWORD dwAspect,LONG lIndex);
	   STDMETHODIMP_(void) OnRename(IMoniker * pmk);
	   STDMETHODIMP_(void) OnSave();
	   STDMETHODIMP_(void) OnClose();
	
	   // IOleInPlaceSite methods
	   STDMETHODIMP GetWindow(HWND *p);
	   STDMETHODIMP ContextSensitiveHelp(BOOL);
	   STDMETHODIMP CanInPlaceActivate();
	   STDMETHODIMP OnInPlaceActivate();
	   STDMETHODIMP OnUIActivate();
	   STDMETHODIMP GetWindowContext(IOleInPlaceFrame** ppFrame,IOleInPlaceUIWindow **ppDoc,LPRECT r1,LPRECT r2,LPOLEINPLACEFRAMEINFO o);
	   STDMETHODIMP Scroll(SIZE s);
	   STDMETHODIMP OnUIDeactivate(int);
	   STDMETHODIMP OnInPlaceDeactivate();
	   STDMETHODIMP DiscardUndoState();
	   STDMETHODIMP DeactivateAndUndo();
	   STDMETHODIMP OnPosRectChange(LPCRECT);
	
	   // IOleInPlaceFrame methods
	   STDMETHODIMP GetBorder(LPRECT l);
	   STDMETHODIMP RequestBorderSpace(LPCBORDERWIDTHS);
	   STDMETHODIMP SetBorderSpace(LPCBORDERWIDTHS w);
	   STDMETHODIMP SetActiveObject(IOleInPlaceActiveObject*pV,LPCOLESTR s);
	   STDMETHODIMP InsertMenus(HMENU h,LPOLEMENUGROUPWIDTHS x);
	   STDMETHODIMP SetMenu(HMENU h,HOLEMENU hO,HWND hw);
	   STDMETHODIMP RemoveMenus(HMENU h);
	   STDMETHODIMP SetStatusText(LPCOLESTR t);
	   STDMETHODIMP EnableModeless(BOOL f);
	   STDMETHODIMP TranslateAccelerator(LPMSG,WORD);
	
	   std::wstring m_lastExternalName;

	   // IDispatch Methods
	   HRESULT _stdcall GetTypeInfoCount(unsigned int * pctinfo);
	   HRESULT _stdcall GetTypeInfo(unsigned int iTInfo,LCID lcid,ITypeInfo FAR* FAR* ppTInfo);
		HRESULT _stdcall GetIDsOfNames(REFIID riid,OLECHAR FAR* FAR*,unsigned int cNames,LCID lcid,DISPID FAR* );
		HRESULT _stdcall Invoke(DISPID dispIdMember,REFIID riid,LCID lcid,WORD wFlags,DISPPARAMS FAR* pDispParams,VARIANT FAR* pVarResult,EXCEPINFO FAR* pExcepInfo,unsigned int FAR* puArgErr);
   };




// Class AX
class AX
	{
	public:

		AX(char* clsid);
	   CLSID GetCLSID();
		~AX();


		void Init(char* clsid);
		void Clean();

		AXClientSite Site;
		IID* iid;
	   IOleObject* OleObject;
	   IStorage* Storage;
	   IViewObject* View;
	   IDataObject* Data;
	   IUnknown* Unk;
	   IOleInPlaceActiveObject* Pao;
	   //AX_CONNECTSTRUCT* tcs;
	   bool AddMenu;
	   DWORD AdviseToken;
		DWORD DAdviseToken[100];	

	private:
		CLSID clsid;


	};
	

