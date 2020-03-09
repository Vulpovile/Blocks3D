#pragma once
#include "PartInstance.h"

class GroupInstance :
	public PVInstance
{
public:
	GroupInstance(void);
	~GroupInstance(void);
	GroupInstance(const GroupInstance &oinst);
	virtual std::vector<PROPGRIDITEM> getProperties();
	virtual void PropUpdate(LPPROPGRIDITEM &pItem);
	std::vector<Instance *> unGroup();
	PartInstance * primaryPart;
};
