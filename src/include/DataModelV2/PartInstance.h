#pragma once
#include "PVInstance.h"
#include "Enum.h"
#define _USE_MATH_DEFINES
#include <cmath>

#define NEW_BOX_RENDER

class PartInstance : public PVInstance
{
public:
	
	PartInstance(void);
	PartInstance(const PartInstance &oinst);
	Instance* clone() const { return new PartInstance(*this); }
	virtual void PartInstance::postRender(RenderDevice* rd);
	~PartInstance(void);
	virtual void render(RenderDevice*);
	Enum::SurfaceType::Value top;
	Enum::SurfaceType::Value front;
	Enum::SurfaceType::Value right;
	Enum::SurfaceType::Value back;
	Enum::SurfaceType::Value left;
	Enum::SurfaceType::Value bottom;
	Enum::Shape::Value shape;
	CoordinateFrame cFrame;
	Color3 color;
	Vector3 getPosition();
	Vector3 getVelocity();
	Vector3 getRotVelocity();
	void setParent(Instance* parent);
	void setPosition(Vector3);
	void setVelocity(Vector3);
	bool collides(PartInstance * part);
	void setRotVelocity(Vector3);
	CoordinateFrame getCFrame();
	void setCFrame(CoordinateFrame);
	Box getBox();
	Sphere getSphere();
	Box getScaledBox();
	CoordinateFrame getCFrameRenderBased();
	Vector3 getSize();
	void setSize(Vector3);
	void setShape(Enum::Shape::Value shape);
	bool canCollide;
	bool anchored;
	bool collides(Box);
	virtual std::vector<PROPGRIDITEM> getProperties();
	virtual void PropUpdate(LPPROPGRIDITEM &pItem);
	#ifdef NEW_BOX_RENDER
	void addPlus(Vector3 v1);
	void addPlus2(Vector3 v1);
	#endif
private:
	Vector3 position;
	Vector3 size;
	Vector3 velocity;
	Vector3 rotVelocity;
	float	_bevelSize;
	int		_parseVert;
	int		_debugTimer;
	bool changed;
	Box itemBox;
	GLuint glList;
};
