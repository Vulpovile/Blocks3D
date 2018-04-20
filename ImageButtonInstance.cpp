#include "ImageButtonInstance.h"
G3D::TextureRef image = NULL;
int openGLID = 0;
G3D::TextureRef image_ovr = NULL;
int openGLID_ovr = 0;
G3D::TextureRef image_dn = NULL;
int openGLID_dn = 0;
ImageButtonInstance::ImageButtonInstance(G3D::TextureRef newImage = NULL, G3D::TextureRef overImage = NULL, G3D::TextureRef downImage = NULL)
{
	
	image = newImage;
	openGLID = image->getOpenGLID();
	image_ovr = overImage;
	openGLID_ovr = image_ovr->getOpenGLID();
	image_dn = downImage;
	openGLID_dn = image_dn->getOpenGLID();
}

ImageButtonInstance::~ImageButtonInstance(void)
{
}
