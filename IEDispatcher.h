#pragma once
#include "oaidl.h"

class IEDispatcher : public IDispatch
{
public:
	IEDispatcher(void);
	~IEDispatcher(void);
	int IEDispatcher::QueryInterface(const IID &riid, void **ppvObject);
	ULONG IEDispatcher::AddRef();
	HRESULT IEDispatcher::GetIDsOfNames(const IID &rrid, LPOLESTR *rgszNames, UINT cNames, LCID lcid, DISPID *rgDispId);
	ULONG IEDispatcher::Release();
};
