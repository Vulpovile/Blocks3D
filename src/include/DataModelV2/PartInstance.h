#pragma once
#include "PVInstance.h"
#include "Enum.h"
#define _USE_MATH_DEFINES
#include <cmath>

class PartInstance : public PVInstance
{
public:
	
	PartInstance(void);
	PartInstance(const PartInstance &oinst);
	~PartInstance(void);
	Instance* clone() const { return new PartInstance(*this); }
	
	//Rendering
	virtual void PartInstance::postRender(RenderDevice* rd);
	virtual void render(RenderDevice*);
	
	//Surfaces
	Enum::SurfaceType::Value top;
	Enum::SurfaceType::Value front;
	Enum::SurfaceType::Value right;
	Enum::SurfaceType::Value back;
	Enum::SurfaceType::Value left;
	Enum::SurfaceType::Value bottom;
	Enum::Shape::Value shape;

	//Variables
	Color3 color;
	bool canCollide;
	bool anchored;

	//Getters
	Vector3 getPosition();
	Vector3 getVelocity();
	Vector3 getRotVelocity();
	Vector3 getSize();
	Box getBox();
	Sphere getSphere();
	Box getScaledBox();
	CoordinateFrame getCFrame();

	//Setters
	void setParent(Instance* parent);
	void setPosition(Vector3);
	void setVelocity(Vector3);
	void setRotVelocity(Vector3);
	void setCFrame(CoordinateFrame);
	void setSize(Vector3);
	void setShape(Enum::Shape::Value shape);
	void setChanged();
	void setSurface(int face, Enum::SurfaceType::Value surface);

	//Collision
	bool collides(PartInstance * part);
	bool collides(Box);

	//Properties
	virtual std::vector<PROPGRIDITEM> getProperties();
	virtual void PropUpdate(LPPROPGRIDITEM &pItem);
private:
	Vector3 position;
	Vector3 size;
	Vector3 velocity;
	Vector3 rotVelocity;
	bool changed;
	Box itemBox;
	GLuint glList;
};
