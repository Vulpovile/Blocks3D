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
	
	// Draw outlines
	for(size_t i = 0; i < g_dataModel->getSelectionService()->getSelection().size(); i++)
	{
		if(PartInstance* part = dynamic_cast<PartInstance*>(g_dataModel->getSelectionService()->getSelection()[i]))
		{
			Vector3 size = part->getSize();
			Vector3 pos = part->getPosition();
			drawOutlines(
				Vector3(0+size.x/2, 0+size.y/2, 0+size.z/2) ,
				Vector3(0-size.x/2,0-size.y/2,0-size.z/2), 
				rd,
				Vector3(size.x/2, size.y/2, size.z/2), 
				Vector3(pos.x, pos.y, pos.z), 
				part->getCFrame()
			);
		}		
	}

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

void LightingInstance::drawOutlines(Vector3 from, Vector3 to, RenderDevice* rd, Vector3 size, Vector3 pos, CoordinateFrame c)
{
	Color3 outline = Color3::cyan();
	float offsetSize = 0.05F;
	
	//X
	Draw::box(c.toWorldSpace(Box(Vector3(from.x - offsetSize, from.y + offsetSize, from.z + offsetSize), Vector3(to.x + offsetSize, from.y - offsetSize, from.z - offsetSize))), rd, outline, Color4::clear()); 
	Draw::box(c.toWorldSpace(Box(Vector3(from.x - offsetSize, to.y + offsetSize, from.z + offsetSize), Vector3(to.x + offsetSize, to.y - offsetSize, from.z - offsetSize))), rd, outline, Color4::clear()); 
	Draw::box(c.toWorldSpace(Box(Vector3(from.x - offsetSize, to.y + offsetSize, to.z + offsetSize), Vector3(to.x + offsetSize, to.y - offsetSize, to.z - offsetSize))), rd, outline, Color4::clear()); 
	Draw::box(c.toWorldSpace(Box(Vector3(from.x - offsetSize, from.y + offsetSize, to.z + offsetSize), Vector3(to.x + offsetSize, from.y - offsetSize, to.z - offsetSize))), rd, outline, Color4::clear()); 
	//Y
	Draw::box(c.toWorldSpace(Box(Vector3(from.x + offsetSize, from.y - offsetSize + 0.1, from.z + offsetSize), Vector3(from.x - offsetSize, to.y + offsetSize - 0.1, from.z - offsetSize))), rd, outline, Color4::clear()); 
	Draw::box(c.toWorldSpace(Box(Vector3(to.x + offsetSize, from.y - offsetSize + 0.1, from.z + offsetSize), Vector3(to.x - offsetSize, to.y + offsetSize - 0.1, from.z - offsetSize))), rd, outline, Color4::clear()); 
	Draw::box(c.toWorldSpace(Box(Vector3(to.x + offsetSize, from.y - offsetSize + 0.1, to.z + offsetSize), Vector3(to.x - offsetSize, to.y + offsetSize-0.1, to.z - offsetSize))), rd, outline, Color4::clear()); 
	Draw::box(c.toWorldSpace(Box(Vector3(from.x + offsetSize, from.y - offsetSize + 0.1, to.z + offsetSize), Vector3(from.x - offsetSize, to.y + offsetSize - 0.1, to.z - offsetSize))), rd, outline, Color4::clear()); 

	//Z
	Draw::box(c.toWorldSpace(Box(Vector3(from.x + offsetSize, from.y + offsetSize, from.z - offsetSize), Vector3(from.x - offsetSize, from.y - offsetSize, to.z + offsetSize))), rd, outline, Color4::clear()); 
	Draw::box(c.toWorldSpace(Box(Vector3(from.x + offsetSize, to.y + offsetSize, from.z - offsetSize), Vector3(from.x - offsetSize, to.y - offsetSize, to.z + offsetSize))), rd, outline, Color4::clear()); 
	Draw::box(c.toWorldSpace(Box(Vector3(to.x + offsetSize, from.y + offsetSize, from.z - offsetSize), Vector3(to.x - offsetSize, from.y - offsetSize, to.z + offsetSize))), rd, outline, Color4::clear()); 
	Draw::box(c.toWorldSpace(Box(Vector3(to.x + offsetSize, to.y + offsetSize, from.z - offsetSize), Vector3(to.x - offsetSize, to.y - offsetSize, to.z + offsetSize))), rd, outline, Color4::clear()); 
	
	if(g_usableApp->getMode() == ARROWS)
	{
		AABox box;
		c.toWorldSpace(Box(from, to)).getBounds(box);
		float max = box.high().y - pos.y;

		Draw::arrow(pos, Vector3(0, 1.5+max, 0), rd);
		Draw::arrow(pos, Vector3(0, (-1.5)-max, 0), rd);
		
		max = box.high().x - pos.x;

		Draw::arrow(pos, Vector3(1.5+max, 0, 0), rd);
		Draw::arrow(pos, Vector3((-1.5)-max, 0, 0), rd);

		max = box.high().z - pos.z;

		Draw::arrow(pos, Vector3(0, 0, 1.5+max), rd);
		Draw::arrow(pos, Vector3(0, 0, (-1.5)-max), rd);
	}
	else if(g_usableApp->getMode() == RESIZE)
	{
		Color3 sphereColor = outline;
		Vector3 gamepoint = pos;
		Vector3 camerapoint = rd->getCameraToWorldMatrix().translation;
		float distance = pow(pow((double)gamepoint.x - (double)camerapoint.x, 2) + pow((double)gamepoint.y - (double)camerapoint.y, 2) + pow((double)gamepoint.z - (double)camerapoint.z, 2), 0.5);
		if(distance < 200)
		{
			
			float multiplier = distance * 0.025F/2;
			if(multiplier < 0.25F)
				multiplier = 0.25F;
			Vector3 position = pos + (c.lookVector()*((size.z)+1));
			Draw::sphere(Sphere(position, multiplier), rd, sphereColor, Color4::clear());
			position = pos - (c.lookVector()*((size.z)+1));
			Draw::sphere(Sphere(position, multiplier), rd, sphereColor, Color4::clear());

			position = pos + (c.rightVector()*((size.x)+1));
			Draw::sphere(Sphere(position, multiplier), rd, sphereColor, Color4::clear());
			position = pos - (c.rightVector()*((size.x)+1));
			Draw::sphere(Sphere(position, multiplier), rd, sphereColor, Color4::clear());

			position = pos + (c.upVector()*((size.y)+1));
			Draw::sphere(Sphere(position, multiplier), rd, sphereColor, Color4::clear());
			position = pos - (c.upVector()*((size.y)+1));
			Draw::sphere(Sphere(position, multiplier), rd, sphereColor, Color4::clear());
		}
	}
}