#include "Tool/SurfaceTool.h"
#include "Application.h"
using namespace B3D;

SurfaceTool::SurfaceTool(int theSurface, int extraParam)
{
	surface = theSurface;
	param = extraParam;
}

SurfaceTool::~SurfaceTool(void)
{
}

std::vector<G3D::Box> getSurfaces(PartInstance * part)
{
	std::vector<G3D::Box> planes;
	G3D::Box box = part->getBox();
	G3D::Vector3 v0;
	G3D::Vector3 v1;
	G3D::Vector3 v2;
	G3D::Vector3 v3;
	box.getFaceCorners(0,v0,v1,v2,v3);
	planes.push_back(G3D::Box(v0, v2));
	box.getFaceCorners(1,v0,v1,v2,v3);
	planes.push_back(G3D::Box(v0, v2));
	box.getFaceCorners(2,v0,v1,v2,v3);
	planes.push_back(G3D::Box(v0, v2));
	box.getFaceCorners(3,v0,v1,v2,v3);
	planes.push_back(G3D::Box(v0, v2));
	box.getFaceCorners(4,v0,v1,v2,v3);
	planes.push_back(G3D::Box(v0, v2));
	box.getFaceCorners(5,v0,v1,v2,v3);
	planes.push_back(G3D::Box(v0, v2));
	return planes;
}

void SurfaceTool::onButton1MouseDown(Mouse mouse)
{
	AudioPlayer::playSound(dingSound);
	PartInstance * target = mouse.getTarget();
	if(target != NULL)
	{
		G3D::Ray ray = mouse.getLastRay();
		std::vector<G3D::Box> surfacesHit = getSurfaces(target);
		int closest;
		float nearValue = G3D::inf();
		for(size_t i = 0; i < surfacesHit.size(); i++)
		{
			float newTime = ray.intersectionTime(surfacesHit[i]);
			if(nearValue > newTime)
			{
				nearValue = newTime;
				closest = (int)i;
			}
		}
		if(G3D::isFinite(nearValue))
		{
			target->setSurface(closest, Enum::SurfaceType::Value(surface));
		}
	}
	if(surface == Enum::SurfaceType::Motor)
	{
		g_usableApp->changeTool(NULL);
	}
}
void SurfaceTool::onButton1MouseUp(Mouse mouse)
{
	
}

void SurfaceTool::onMouseMoved(Mouse mouse)
{
}
void SurfaceTool::onSelect(Mouse mouse)
{
	AudioPlayer::playSound(dingSound);
}

void SurfaceTool::onKeyDown(int key)
{
	
}

void SurfaceTool::onKeyUp(int key)
{
	
}