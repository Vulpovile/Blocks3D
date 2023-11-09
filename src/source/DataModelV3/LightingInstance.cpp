#include "DataModelV3/LightingInstance.h"
#include "DataModelV3/DataModelInstance.h"

#include "StringFunctions.h"
//#include "Listener/ModeSelectionListener.h"

using namespace B3D;

LightingInstance::LightingInstance(void) : Instance("Lighting")
{
	name = "Lighting";
	canDelete = false;
	_hideSky = false;

	
	topAmbient = Reflection::ReflectionProperty<Color3>("TopAmbient", Color3(0.5F, 0.5F, 0.5F), TYPE_COLOR3, this->dataTable);
	bottomAmbient = Reflection::ReflectionProperty<Color3>("BottomAmbient", Color3(0.8F, 0.8F, 0.8F), TYPE_COLOR3, this->dataTable);
	spotLight = Reflection::ReflectionProperty<Color3>("SpotLight", Color3(0.5F, 0.5F, 0.5F), TYPE_COLOR3, this->dataTable);
	clearColor = Reflection::ReflectionProperty<Color4>("ClearColor", Color4(0.0F, 0.0F, 0.0F, 0.0F), TYPE_COLOR4, this->dataTable);


	lighting.setTime(G3D::toSeconds(2, 00, 00, PM));

	// Maybe this is Top and Bottom Ambient?
	lighting.ambient = topAmbient.getValue();
	lighting.lightColor = bottomAmbient.getValue();

	sky = Sky::create(NULL, ExePath() + "/content/sky/");
}

LightingInstance::~LightingInstance(void)
{
	sky->~Sky();
}

// Getters
G3D::SkyRef LightingInstance::getSky()
{
	return sky;
}

G3D::LightingParameters LightingInstance::getLightingParameters()
{
	return lighting;
}

// Functions
void LightingInstance::suppressSky(bool doSuppress)
{
	_hideSky = doSuppress;
}

void LightingInstance::update(RenderDevice* rd)
{

    
	if(!_hideSky) {
		rd->clear(sky.isNull(), true, true);
		if (sky.notNull()) sky->render(rd, lighting);
	} else {
		rd->setColorClearValue(clearColor.getValue());
		rd->clear(true, true, true);
		suppressSky(false);
	}
	
    // Setup lighting
    rd->enableLighting();

	rd->setShadeMode(RenderDevice::SHADE_SMOOTH);
	rd->setAmbientLightColor(Color3(1,1,1));

	rd->setLight(0, GLight::directional(lighting.lightDirection, lighting.lightColor, true, true));
	rd->setAmbientLightColor(lighting.ambient);

	rd->beforePrimitive();
	CoordinateFrame forDraw = rd->getObjectToWorldMatrix();
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_COLOR_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);
	parentDataModel->getWorkspace()->render(rd);
	parentDataModel->getWorkspace()->renderName(rd);
	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_COLOR_ARRAY);
	glDisableClientState(GL_NORMAL_ARRAY);
	rd->setObjectToWorldMatrix(forDraw);
	rd->afterPrimitive();

	parentDataModel->getSelectionService()->render(rd);

	// TODO Mouse and tool will be handled by datamodel
	//g_usableApp->tool->render(rd, g_usableApp->mouse);
	

    rd->disableLighting();

	drawEffects(rd);
}

void LightingInstance::drawEffects(RenderDevice* rd)
{
    if (sky.notNull()) {
        sky->renderLensFlare(rd, lighting);
    }
}
