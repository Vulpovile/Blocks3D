#pragma once
#include "DataModelV3/PartInstance.h"
#pragma once
#include "DataModelV3/WorkspaceInstance.h"

struct MousePoint{
	Vector3 position;
	B3D::PartInstance * target;
	MousePoint(Vector3 pos, B3D::PartInstance * targ)
	{
		position = pos;
		target = targ;
	}
};

#pragma once
class Mouse
{
public:
	Mouse();
	~Mouse(void);
	int x, y;
	int oldx, oldy;
	B3D::PartInstance * getTarget();
	MousePoint getPositionAndPart(std::vector<B3D::Instance *> ignore = std::vector<B3D::Instance *>());
	Vector3 getPosition(std::vector<B3D::Instance *> ignore = std::vector<B3D::Instance *>());
	bool isMouseOnScreen();
	bool isMouseDown();
	void setMouseDown(bool mouseDown);
	G3D::Ray getRay();
	G3D::Ray getLastRay();
	G3D::Plane getPlane();
	G3D::Plane getInversePlane();
private:
	bool mouseDown;
};
