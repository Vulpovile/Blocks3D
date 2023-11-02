#pragma once
#include "Instance.h"

struct UDim
{
	float scale;
	float offset;
	UDim()
	{
		scale = offset = 0;
	}
	UDim(float scale_, float offset_)
	{
		scale = scale_;
		offset = offset_;
	}
};

struct UDim2
{
	UDim x;
	UDim y;
	UDim2(UDim x_, UDim y_)
	{
		x = x_;
		y = y_;
	}
	UDim2(float scale_x, float offset_x, float scale_y, float offset_y)
	{
		x = UDim(scale_x, offset_x);
		y = UDim(scale_y, offset_y);
	}
};

class Instance;

class BaseGuiInstance : public Instance
{
public:
	BaseGuiInstance(void);
	virtual ~BaseGuiInstance(void);
	virtual void render(RenderDevice* rd);
	virtual bool mouseHovered(float, float, RenderDevice* rd);
	UDim2 position;
	UDim2 size;	
	static G3D::Color4 translucentBackdrop()
	{
		return G3D::Color4(0.60000002F, 0.60000002F, 0.60000002F, 0.60000002F);
	}
	static G3D::Color4 disabledFill()
	{
		return G3D::Color4(0.69999999F, 0.69999999F, 0.69999999F, 0.5F);
	}
protected:
	bool mouseInArea(float, float, float, float, float, float);
	class ButtonListener* listener;
};
