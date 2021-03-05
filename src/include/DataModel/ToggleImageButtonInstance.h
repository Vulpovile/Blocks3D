#pragma once
#include "imagebuttoninstance.h"


class ToggleImageButtonInstance : public ImageButtonInstance
{
public:
	//ImageButtonInstance(G3D::TextureRef);
	//ImageButtonInstance(G3D::TextureRef,G3D::TextureRef);
	//ImageButtonInstance(G3D::TextureRef,G3D::TextureRef,G3D::TextureRef);
	ToggleImageButtonInstance(G3D::TextureRef newImage,G3D::TextureRef overImage = NULL,
										 G3D::TextureRef downImage = NULL,
										 G3D::TextureRef disableImage = NULL,
										 G3D::TextureRef newImage2 = NULL,
										 G3D::TextureRef overImage2 = NULL,
										 G3D::TextureRef downImage2 = NULL,
										 G3D::TextureRef disableImage2 = NULL);
	~ToggleImageButtonInstance(void);
	void drawObj(RenderDevice*, Vector2, bool);
	bool checked;
	G3D::TextureRef image2;
	int openGLID2;
	G3D::TextureRef image_ovr2;
	int openGLID2_ovr;
	G3D::TextureRef image_dn2;
	int openGLID2_dn;
	G3D::TextureRef image_ds2;
	int openGLID2_ds;
};
