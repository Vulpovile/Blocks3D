#pragma once
#include "PVInstance.h"

class GroupInstance :
	public PVInstance
{
public:
	GroupInstance(void);
	~GroupInstance(void);
	GroupInstance(const GroupInstance &oinst);
	virtual std::vector<PROPGRIDITEM> getProperties();
	virtual void PropUpdate(LPPROPGRIDITEM &pItem);
};
