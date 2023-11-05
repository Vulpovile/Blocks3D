#pragma once
#include "PVInstance.h"
#include "Enum.h"
#define _USE_MATH_DEFINES
#include <cmath>

namespace B3D
{
	class PartInstance : public PVInstance
	{
	public:
		
		PartInstance(void);
		~PartInstance(void);
	

		//Reflective Properties
		Reflection::ReflectionProperty<Color3> color;
		Reflection::ReflectionProperty<bool> canCollide;
		//Surfaces
		Reflection::ReflectionProperty<Enum::SurfaceType::Value> top, front, right, back, left, bottom;
		//Shapes
		Reflection::ReflectionProperty<Enum::Shape::Value> shape;
		//OnTouch
		Reflection::ReflectionProperty<Enum::ActionType::Value> onTouchAction;
		Reflection::ReflectionProperty<Enum::Sound::Value> OnTouchSound;	

		//Non-Reflective Variables
		dBodyID physBody;
		dGeomID physGeom[3];

		//Functions
		//Rendering
		virtual void PartInstance::postRender(RenderDevice* rd);
		virtual void render(RenderDevice*);
		virtual void renderName(RenderDevice*);
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
	private:
		//Reflective Properties
		Reflection::ReflectionProperty<bool> anchored;
		Reflection::ReflectionProperty<Vector3> position;
		Reflection::ReflectionProperty<Vector3> size;
		Reflection::ReflectionProperty<Vector3> velocity;
		Reflection::ReflectionProperty<Vector3> rotVelocity;

		// OnTouch
		Reflection::ReflectionProperty<bool> singleShot;
		Reflection::ReflectionProperty<int> touchesToTrigger;
		Reflection::ReflectionProperty<int> uniqueObjectsToTrigger;
		Reflection::ReflectionProperty<int> changeScore;
		Reflection::ReflectionProperty<float> changeTimer;

		//Non-reflective Variables
		bool changed;
		bool dragging;
		Box itemBox;
		GLuint glList;
		bool _touchedOnce;

		
	};
}