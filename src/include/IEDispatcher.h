#pragma once
#include "oaidl.h"
//DEFINE_GUID(CLSID_G3d, 0xB323F8E0L, 0x2E68, 0x11D0, 0x90, 0xEA, 0x00, 0xAA, 0x00, 0x60, 0xF8, 0x6F);

class IEDispatcher : public IDispatch
{
/*
EXTERN_C const IID IID_IDispatch;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("B323F8E0-2E68-11D0-90EA-00AA0060F86F")
    IEDispatcher : public IDispatch
	{
*/
public:
	IEDispatcher(void);
	~IEDispatcher(void);
	HRESULT STDMETHODCALLTYPE IEDispatcher::QueryInterface(const IID &riid, void **ppvObject);
	ULONG STDMETHODCALLTYPE IEDispatcher::AddRef();
	ULONG STDMETHODCALLTYPE IEDispatcher::Release();
	HRESULT STDMETHODCALLTYPE IEDispatcher::GetTypeInfoCount(UINT *pctinfo);
	HRESULT STDMETHODCALLTYPE IEDispatcher::GetTypeInfo(UINT, LCID, ITypeInfo **);
	HRESULT STDMETHODCALLTYPE IEDispatcher::GetIDsOfNames(const IID &, LPOLESTR *, UINT, LCID, DISPID *);
	HRESULT STDMETHODCALLTYPE IEDispatcher::Invoke(DISPID, const IID &, LCID, WORD, DISPPARAMS *, VARIANT *, EXCEPINFO *, UINT *);
	
};

//#endif
