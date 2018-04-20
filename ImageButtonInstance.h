#pragma once
#include "instance.h"

class ImageButtonInstance :
	public Instance
{
public:
	ImageButtonInstance(G3D::TextureRef,G3D::TextureRef,G3D::TextureRef);
	~ImageButtonInstance(void);
};
