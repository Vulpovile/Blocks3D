#include "DataModelV2/LightingInstance.h"
#include "Application.h"
#include "Globals.h"
#include "StringFunctions.h"
#include "Listener/ModeSelectionListener.h"

LightingInstance::LightingInstance(void)
{
	Instance::Instance();
	name = "Lighting";
	className = "Lighting";
	listicon = 10;
	canDelete = false;

	_hideSky = false;

	lighting.setTime(G3D::toSeconds(2, 00, 00, PM));

	// Maybe this is Top and Bottom Ambient?
	lighting.ambient = Color3(0.5F, 0.5F, 0.5F);
	lighting.lightColor = Color3(0.8F, 0.8F, 0.8F);

	sky = Sky::create(NULL, ExePath() + "/content/sky/");
	clearColor = Color4(0.0F, 0.0F, 0.0F, 0.0F);
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

std::vector<PROPGRIDITEM> LightingInstance::getProperties()
{
	std::vector<PROPGRIDITEM> properties = Instance::getProperties();

	properties.push_back(createPGI("Appearance",
		"TopAmbient",
		"The color of the TopAmbient for 3D Objects",
		RGB((topAmbient.r*255),(topAmbient.g*255),(topAmbient.b*255)),
		PIT_COLOR
		));

	properties.push_back(createPGI("Appearance",
		"BottomAmbient",
		"The color of the BottomAmbient for 3D Objects",
		RGB((bottomAmbient.r*255),(bottomAmbient.g*255),(bottomAmbient.b*255)),
		PIT_COLOR
		));

	properties.push_back(createPGI("Appearance",
		"SpotLight",
		"The color of the SpotLight",
		RGB((spotLight.r*255),(spotLight.g*255),(spotLight.b*255)),
		PIT_COLOR
		));

	properties.push_back(createPGI("Appearance",
		"ClearColor",
		"",
		RGB((clearColor.r*255),(clearColor.g*255),(clearColor.b*255)),
		PIT_COLOR
		));
	return properties;
}


void LightingInstance::PropUpdate(LPPROPGRIDITEM &item)
{
	if(strcmp(item->lpszPropName, "TopAmbient") == 0)
	{
		topAmbient = Color3(
			GetRValue(item->lpCurValue)/255.0F,
			GetGValue(item->lpCurValue)/255.0F,
			GetBValue(item->lpCurValue)/255.0F
		);
	}
	if(strcmp(item->lpszPropName, "BottomAmbient") == 0)
	{
		bottomAmbient = Color3(
			GetRValue(item->lpCurValue)/255.0F,
			GetGValue(item->lpCurValue)/255.0F,
			GetBValue(item->lpCurValue)/255.0F
		);
	}
	if(strcmp(item->lpszPropName, "SpotLight") == 0)
	{
		spotLight = Color3(
			GetRValue(item->lpCurValue)/255.0F,
			GetGValue(item->lpCurValue)/255.0F,
			GetBValue(item->lpCurValue)/255.0F
		);
	}
	if(strcmp(item->lpszPropName, "ClearColor") == 0)
	{
		clearColor = Color3(
			GetRValue(item->lpCurValue)/255.0F,
			GetGValue(item->lpCurValue)/255.0F,
			GetBValue(item->lpCurValue)/255.0F
		);
	}
	
	else
		Instance::PropUpdate(item);
}


// Functions
void LightingInstance::suppressSky(bool doSuppress)
{
	_hideSky = doSuppress;
}

void LightingInstance::update()
{
	RenderDevice* rd = g_usableApp->getRenderDevice();

    
	if(!_hideSky) {
		rd->clear(sky.isNull(), true, true);
		if (sky.notNull()) sky->render(rd, lighting);
	} else {
		rd->setColorClearValue(clearColor);
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
	g_dataModel->getWorkspace()->render(rd);
	g_dataModel->getWorkspace()->renderName(rd);
	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_COLOR_ARRAY);
	glDisableClientState(GL_NORMAL_ARRAY);
	rd->setObjectToWorldMatrix(forDraw);
	rd->afterPrimitive();

	g_dataModel->getSelectionService()->render(rd);
	g_usableApp->tool->render(rd, g_usableApp->mouse);
	

    rd->disableLighting();

	drawEffects();
}

void LightingInstance::drawEffects()
{
	RenderDevice* rd = g_usableApp->getRenderDevice();
    if (sky.notNull()) {
        sky->renderLensFlare(rd, lighting);
    }
}