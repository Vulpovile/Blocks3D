#include "DataModelV2/ThumbnailGeneratorInstance.h"
#include "Application.h"
#include "Globals.h"
#include <fstream>

ThumbnailGeneratorInstance::ThumbnailGeneratorInstance(void)
{
	Instance::Instance();
	name = "ThumbnailGenerator";
	className = "ThumbnailGenerator";
	canDelete = false;
}

ThumbnailGeneratorInstance::~ThumbnailGeneratorInstance(void) {}

std::string ThumbnailGeneratorInstance::click(std::string fileType, int cx, int cy, bool hideSky)
{
	// Important things we need
	RenderDevice* rd = g_usableApp->getRenderDevice();
	GuiRootInstance* guiRoot = g_dataModel->getGuiRoot();

	const G3D::GImage::Format format = G3D::GImage::stringToFormat(fileType);
	
	// Hide the GUI
	guiRoot->hideGui(true);

	// Disable the sky
	if(hideSky) 
		g_usableApp->toggleSky();
	
	// Update graphics
	g_usableApp->onGraphics(rd);

	// Sky SHOULD be gone now, and alpha channel should be present
	G3D::GImage imgBuffer(cx, cy, 4);
	rd->screenshotPic(imgBuffer, true, hideSky);
	
	G3D::BinaryOutput binOut;
	imgBuffer.encode(format, binOut);

	// Temporary file saving
	std::string fileSave = "./click_output." + fileType;
	std::ofstream out(fileSave.c_str(), std::ios::out | std::ios::binary);
	out.write(reinterpret_cast<const char*>(binOut.getCArray()), binOut.length());

	// Unhide GUI
	guiRoot->hideGui(false);

	return "boop!";
}

