#pragma once
#include "BaseButtonInstance.h"

class ImageButtonInstance : public BaseButtonInstance
{
public:
	ImageButtonInstance(G3D::TextureRef,G3D::TextureRef,G3D::TextureRef);
	~ImageButtonInstance(void);
	void drawObj(RenderDevice*, Vector2, bool);
	Vector2 size;
	Vector2 position;
};
