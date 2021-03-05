#pragma once
#include "instance.h"
#include "enum.h"

class PVInstance :
	public Instance
{
public:
	PVInstance(void);
	~PVInstance(void);
	PVInstance(const PVInstance &oinst);
	virtual void postRender(RenderDevice* rd);
	virtual std::vector<PROPGRIDITEM> getProperties();
	virtual void PropUpdate(LPPROPGRIDITEM &pItem);
	bool nameShown;
	bool controllerFlagShown;
	Enum::Controller::Value controller;
protected:
	static G3D::Color3 getControllerColor(int controller)
	{
		switch(controller)
		{
			case Enum::Controller::KeyboardLeft:
				return Color3::red();
			case Enum::Controller::KeyboardRight:
				return Color3::blue();
			case Enum::Controller::Chase:
				return Color3::black();
			case Enum::Controller::Flee:
				return Color3::yellow();
		}
		return Color3::gray();
	}
};
