#include "DataModelV2/ThumbnailGeneratorInstance.h"
#include "Application.h"
#include "Globals.h"
#include "base64.h"
#include <fstream>

ThumbnailGeneratorInstance::ThumbnailGeneratorInstance(void)
{
	Instance::Instance();
	name = "ThumbnailGenerator";
	className = "ThumbnailGenerator";
	canDelete = false;
}

ThumbnailGeneratorInstance::~ThumbnailGeneratorInstance(void) {}

/*
 * TODO:
 * Move functions like toggleSky into their own "Lighting" instance
 * Make this headless, and allow for resolutions greater than the screen resolution
*/
std::string ThumbnailGeneratorInstance::click(std::string fileType, int cx, int cy, bool hideSky)
{
	if(!G3D::GImage::supportedFormat(fileType)) {
		printf("%s is not a valid fileType.", fileType);
		return "";
	}

	RenderDevice* rd = g_usableApp->getRenderDevice();
	GuiRootInstance* guiRoot = g_dataModel->getGuiRoot();
	const G3D::GImage::Format format = G3D::GImage::stringToFormat(fileType);

	int prevWidth = rd->width();
	int prevHeight = rd->height();
	G3D::GImage imgBuffer(cx, cy, 4);
	G3D::BinaryOutput binOut;

	guiRoot->hideGui(true);
	g_usableApp->resize3DView(cx, cy);

	if(hideSky) 
		g_dataModel->getLighting()->suppressSky(true);
	
	g_usableApp->onGraphics(rd);
	rd->screenshotPic(imgBuffer, true, hideSky);
	imgBuffer.encode(format, binOut);

	// Convert to Base64 string
	std::string base64ImgStr = base64_encode(reinterpret_cast<const unsigned char*>(binOut.getCArray()), binOut.length(), false);
	
	guiRoot->hideGui(false);
	g_usableApp->resize3DView(prevWidth, prevHeight);

	return base64ImgStr;
}

