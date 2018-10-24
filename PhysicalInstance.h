#pragma once
#include "instance.h"
#include "Enum.h"

class PhysicalInstance :
	public Instance
{
public:
	PhysicalInstance(void);
	PhysicalInstance(const PhysicalInstance &oinst);
	Instance* clone() const { return new PhysicalInstance(*this); }
	~PhysicalInstance(void);
	virtual void render(RenderDevice*);
	Vector3 velocity;
	Enum::SurfaceType::Value top;
	Enum::SurfaceType::Value front;
	Enum::SurfaceType::Value right;
	Enum::SurfaceType::Value back;
	Enum::SurfaceType::Value left;
	Enum::SurfaceType::Value bottom;
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
	bool canCollide;
	bool anchored;
	Vector3 rotVelocity;
	bool collides(Box);
	virtual std::vector<PROPGRIDITEM> getProperties();
	virtual void PropUpdate(LPPROPGRIDITEM &pItem);
private:
	Vector3 position;
	Vector3 size;
	GLfloat vertecies[96];
	bool changed;
	Box itemBox;
};
