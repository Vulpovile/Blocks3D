#pragma once
#include "oaidl.h"

class IEDispatcher : public IDispatch
{
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
