#pragma once
#include "PVInstance.h"
#include "Enum.h"
#include "PropertiesV2/Color3Property.h"
#include "PropertiesV2/Vector3Property.h"
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
	virtual void renderName(RenderDevice*);

	//Surfaces
	Enum::SurfaceType::Value top;
	Enum::SurfaceType::Value front;
	Enum::SurfaceType::Value right;
	Enum::SurfaceType::Value back;
	Enum::SurfaceType::Value left;
	Enum::SurfaceType::Value bottom;

	//Shapes
	Enum::Shape::Value shape;

	//OnTocuh
	Enum::ActionType::Value OnTouchAction;
	Enum::Sound::Value OnTouchSound;	

	//Variables
	Color3 color;
	bool canCollide;
	dBodyID physBody;
	dGeomID physGeom[3];

	//Getters
	Vector3 getPosition();
	Vector3 getVelocity();
	Vector3 getRotVelocity();
	Vector3 getSize();
	Box getBox();
	Sphere getSphere();
	Box getScaledBox();
	CoordinateFrame getCFrame();

	//OnTouch Getters
	bool isSingleShot();
	int getTouchesToTrigger();
	int getUniqueObjectsToTrigger();
	int getChangeScore();
	float getChangeTimer();

	//Setters
	void setParent(Instance* parent);
	void setPosition(Vector3);
	void setColor(Color3 color);
	void setVelocity(Vector3);
	void setRotVelocity(Vector3);
	void setCFrame(CoordinateFrame);
	void setCFrameNoSync(CoordinateFrame);
	void setSize(Vector3);
	void setShape(Enum::Shape::Value shape);
	void setChanged();
	void setSurface(int face, Enum::SurfaceType::Value surface);
	void setAnchored(bool anchored);
	bool isAnchored();
	float getMass();
	bool isDragging();
	void setDragging(bool value);

	//Collision
	bool collides(PartInstance * part);
	bool collides(Box);
	
	// onTouch
	void onTouch();

	//Properties
	virtual std::vector<PROPGRIDITEM> getProperties();
	virtual void PropUpdate(LPPROPGRIDITEM &pItem);
	virtual std::vector<Property *> collectProperties();
private:
	bool anchored;
	Vector3 position;
	Vector3 size;
	Vector3 velocity;
	Vector3 rotVelocity;
	bool changed;
	bool dragging;
	Box itemBox;
	GLuint glList;

	// OnTouch
	bool singleShot;
	int touchesToTrigger;
	int uniqueObjectsToTrigger;
	int changeScore;
	float changeTimer;
	bool _touchedOnce;
};