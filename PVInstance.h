#pragma once
#include "instance.h"

class PVInstance :
	public Instance
{
public:
	PVInstance(void);
	~PVInstance(void);
	PVInstance(const PVInstance &oinst);
	virtual void postRender(RenderDevice* rd);
	virtual void setParent(Instance* newParent);
	virtual std::vector<PROPGRIDITEM> getProperties();
	virtual void PropUpdate(LPPROPGRIDITEM &pItem);
	virtual void render(RenderDevice* rd);
	bool nameShown;
};
