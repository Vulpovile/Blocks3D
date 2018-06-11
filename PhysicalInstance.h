#pragma once
#include "instance.h"
#include "Surface.h"

class PhysicalInstance :
	public Instance
{
public:
	PhysicalInstance(void);
	~PhysicalInstance(void);
	virtual void render(RenderDevice*);
	Vector3 velocity;
	Vector3 rotvelocity;
	Surface top;
	Surface front;
	Surface right;
	Surface back;
	Surface left;
	Surface bottom;
	CoordinateFrame cFrame;
	Color3 color;
	Vector3 getPosition();
	void setPosition(Vector3);
	CoordinateFrame getCFrame();
	void setCFrame(CoordinateFrame);
	Box getBox();
	Box getScaledBox();
	CoordinateFrame getCFrameRenderBased();
	Vector3 getSize();
	void setSize(Vector3);
private:
	Vector3 position;
	Vector3 size;
};
