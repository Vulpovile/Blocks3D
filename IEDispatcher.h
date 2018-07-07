#pragma once
#include "oaidl.h"

class IEDispatcher : public IDispatch
{
public:
	IEDispatcher(void);
	~IEDispatcher(void);
	HRESULT IEDispatcher::QueryInterface();
	HRESULT IEDispatcher::QueryInterface(const IID &riid, void **ppvObject);
};
