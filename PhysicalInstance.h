#pragma once
#include "instance.h"

class PhysicalInstance :
	public Instance
{
public:
	PhysicalInstance(void);
	~PhysicalInstance(void);
	virtual void render(RenderDevice*);
	Vector3 velocity;
	Vector3 rotvelocity;
	CoordinateFrame cFrame;
	Color3 color;
	Vector3 getPosition();
	void setPosition(Vector3);
	CoordinateFrame getCFrame();
	void setCFrame(CoordinateFrame);
	Box getBox();
	CoordinateFrame getCFrameRenderBased();
	Vector3 getSize();
	void setSize(Vector3);
private:
	Vector3 position;
	Vector3 size;
};
