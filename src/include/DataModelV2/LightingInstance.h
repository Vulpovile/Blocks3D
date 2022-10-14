#pragma once
#include "Instance.h"

class LightingInstance :
	public Instance
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
	void setClearColor(G3D::Color4 clearColor);

	// Functions
	void drawSky();
	void suppressSky(bool doSuppress);
	void update();
	void drawEffects();
	void drawOutlines(Vector3 from, Vector3 to, RenderDevice* rd, Vector3 size, Vector3 pos, CoordinateFrame c);

	// Properties
	void PropUpdate(LPPROPGRIDITEM &pItem);
	std::vector<PROPGRIDITEM> getProperties();

private:
	G3D::Color3 topAmbient;
	G3D::Color3 bottomAmbient;
	G3D::Color3 spotLight;
	G3D::Color4 clearColor;
	G3D::SkyRef sky;
	G3D::LightingParameters lighting;
	bool _hideSky;
};
