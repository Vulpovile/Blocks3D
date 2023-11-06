#pragma once
#include "Instance.h"

namespace B3D
{
	class LightingInstance : public Instance
	{
	public:
		LightingInstance(void);
		~LightingInstance(void);

		// Getters
		G3D::Color3 getTopAmbient();
		G3D::Color3 getBottomAmbient();
		G3D::Color3 getSpotLight();
		G3D::Color4 getClearColor();
		G3D::SkyRef getSky();
		G3D::LightingParameters getLightingParameters();

		// Setters
		void setTopAmbient(G3D::Color3 newValue);
		void setBottomAmbient(G3D::Color3 newValue);
		void setSpotLight(G3D::Color3 newValue);
		void setClearColor(G3D::Color3 clearColor);

		// Functions
		void drawSky(RenderDevice* rd);
		void suppressSky(bool doSuppress);
		void update(RenderDevice* rd);
		void drawEffects(RenderDevice* rd);

	private:
		Reflection::ReflectionProperty<G3D::Color3> topAmbient;
		Reflection::ReflectionProperty<G3D::Color3> bottomAmbient;
		Reflection::ReflectionProperty<G3D::Color3> spotLight;
		Reflection::ReflectionProperty<G3D::Color4> clearColor;
		G3D::SkyRef sky;
		G3D::LightingParameters lighting;
		bool _hideSky;
	};
}