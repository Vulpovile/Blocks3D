#pragma once
#include "Instance.h"
#include "Enum.h"
#include <ode/ode.h>

namespace B3D {
	class PVInstance : public Instance
	{
	public:
		~PVInstance(void);

		virtual void postRender(RenderDevice* rd);
		Reflection::ReflectionProperty<bool> nameShown;
		Reflection::ReflectionProperty<bool> controllerFlagShown;
		Reflection::ReflectionProperty<Enum::Controller::Value> controller;
	protected:
		PVInstance(void);
		PVInstance(std::string);

		Reflection::ReflectionProperty<CoordinateFrame> cFrame;
		//TODO move elsewhere?
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
}