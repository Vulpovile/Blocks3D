#include "DataModelV3/PartInstance.h"

#include "DataModelV3/DataModelInstance.h"
#include "DataModelV3/XplicitNgine/XplicitNgine.h"

#include "Renderer.h"
#include <sstream>
#include <iomanip>
#include "Faces.h"
#include "AudioPlayer.h"
#include "StringFunctions.h"

using namespace B3D;
using namespace Reflection;

PartInstance::PartInstance(void)
{
	PVInstance::PVInstance("Part");
	
	*(name.value) = "Unnamed PVItem";
	canCollide = ReflectionProperty<bool>("CanCollide", true, TYPE_BOOLEAN, this->dataTable);
	anchored = ReflectionProperty<bool>("Anchored", false, TYPE_BOOLEAN, this->dataTable);
	size = ReflectionProperty<Vector3>("Size", Vector3(2,1,4), TYPE_VECTOR3, this->dataTable);
	setCFrame(CoordinateFrame(Vector3(0,0,0)));
	color = ReflectionProperty<Color3>("Color", Color3::gray(), TYPE_COLOR3, this->dataTable);
	velocity = ReflectionProperty<Vector3>("Velocity", Vector3(0,0,0), TYPE_VECTOR3, this->dataTable);
	rotVelocity = ReflectionProperty<Vector3>("RotVelocity", Vector3(0,0,0), TYPE_VECTOR3, this->dataTable);
	top = ReflectionProperty<Enum::SurfaceType::Value>("TopSurface", Enum::SurfaceType::Bumps, TYPE_ENUM, this->dataTable, 
		(void*)new EnumMeta(Enum::SurfaceType::LENGTH, Enum::SurfaceType::STR_TABLE));
    front = ReflectionProperty<Enum::SurfaceType::Value>("FrontSurface", Enum::SurfaceType::Smooth, TYPE_ENUM, this->dataTable, 
		(void*)new EnumMeta(Enum::SurfaceType::LENGTH, Enum::SurfaceType::STR_TABLE));
    right = ReflectionProperty<Enum::SurfaceType::Value>("RightSurface", Enum::SurfaceType::Smooth, TYPE_ENUM, this->dataTable, 
		(void*)new EnumMeta(Enum::SurfaceType::LENGTH, Enum::SurfaceType::STR_TABLE));
	back = ReflectionProperty<Enum::SurfaceType::Value>("BackSurface", Enum::SurfaceType::Smooth, TYPE_ENUM, this->dataTable, 
		(void*)new EnumMeta(Enum::SurfaceType::LENGTH, Enum::SurfaceType::STR_TABLE));
	left = ReflectionProperty<Enum::SurfaceType::Value>("LeftSurface", Enum::SurfaceType::Smooth, TYPE_ENUM, this->dataTable, 
		(void*)new EnumMeta(Enum::SurfaceType::LENGTH, Enum::SurfaceType::STR_TABLE));
	bottom = ReflectionProperty<Enum::SurfaceType::Value>("BottomSurface", Enum::SurfaceType::Smooth, TYPE_ENUM, this->dataTable, 
		(void*)new EnumMeta(Enum::SurfaceType::LENGTH, Enum::SurfaceType::STR_TABLE));
	shape = ReflectionProperty<Enum::Shape::Value>("Shape", Enum::Shape::Block, TYPE_ENUM, this->dataTable, 
		(void*)new EnumMeta(Enum::Shape::LENGTH, Enum::Shape::STR_TABLE));
	
	// OnTouch
	singleShot = ReflectionProperty<bool>("SingleShot", true, TYPE_BOOLEAN, this->dataTable);
	touchesToTrigger = ReflectionProperty<int>("TouchesToTrigger", 1, TYPE_INT, this->dataTable);
	uniqueObjectsToTrigger = ReflectionProperty<int>("UniqueObjectsToTrigger", 1, TYPE_INT, this->dataTable);
	changeScore = ReflectionProperty<int>("ChangeScore", 0, TYPE_INT, this->dataTable);
	changeTimer = ReflectionProperty<float>("ChangeTimer", 0.0f, TYPE_FLOAT, this->dataTable);

	// Non-Reflective Properties
	physBody = NULL;
    glList = glGenLists(1);
	_touchedOnce = false;
	dragging = false;
}

bool PartInstance::isDragging()
{
	return dragging;
}

void PartInstance::setDragging(bool value)
{
	if (dragging != value && getParentDataModel() != NULL)
	{
		dragging = value;
		//TODO implement engine
		//getParentDataModel()->getEngine()->resetBody(this);
	}
}

float PartInstance::getMass()
{
	if(*(shape.value) == Enum::Shape::Block)
		return size.value->x*size.value->y*size.value->z*0.7F;
	else 
		return 1.3333333333333333333333333333333F*(size.value->x/2)*(size.value->y/2)*(size.value->z/2)*0.7F;
}

Vector3 PartInstance::getVelocity()
{
	return *(velocity.value);
}
Vector3 PartInstance::getRotVelocity()
{
	return *(rotVelocity.value);
}

// OnTouch
bool PartInstance::isSingleShot()
{
	return *(singleShot.value);
}

int PartInstance::getTouchesToTrigger()
{
	return *(touchesToTrigger.value);
}

int PartInstance::getUniqueObjectsToTrigger()
{
	return *(uniqueObjectsToTrigger.value);
}

int PartInstance::getChangeScore()
{
	return *(changeScore.value);
}

float PartInstance::getChangeTimer()
{
	return *(changeTimer.value);
}

void PartInstance::setVelocity(Vector3 v)
{
	*(velocity.value) = v;
}
void PartInstance::setRotVelocity(Vector3 v)
{
	*(rotVelocity.value) = v;
}

void PartInstance::postRender(RenderDevice *rd)
{
	// possibly discard this function...
}

void PartInstance::renderName(RenderDevice *rd)
{
	if(!*(nameShown.value))
		return;
	G3D::GFontRef fnt = NULL;
	Instance* dm = parent;
	while(dm != NULL)
	{
		if(DataModelInstance* mod = dynamic_cast<DataModelInstance*>(dm))
		{
			fnt = mod->font;
			break;
		}
		dm = dm->getParent();
	}
	if(!fnt.isNull())
	{
		Vector3 gamepoint = *(position.value) + Vector3(0,1.5,0);
		Vector3 camerapoint = rd->getCameraToWorldMatrix().translation;
		float distance = pow(pow((double)gamepoint.x - (double)camerapoint.x, 2) + pow((double)gamepoint.y - (double)camerapoint.y, 2) + pow((double)gamepoint.z - (double)camerapoint.z, 2), 0.5);
		if(distance < 100 && distance > -100)
		{
			if(distance < 0)
			distance = distance*-1;
			glDisable(GL_DEPTH_TEST);
			fnt->draw3D(rd, *(name.value), CoordinateFrame(rd->getCameraToWorldMatrix().rotation, gamepoint), 0.03*distance, Color3::yellow(), Color3::black(), G3D::GFont::XALIGN_CENTER, G3D::GFont::YALIGN_CENTER);
			glEnable(GL_DEPTH_TEST);
		}
	}
}

void PartInstance::setChanged()
{
	changed = true;
}

void PartInstance::setSurface(int face, Enum::SurfaceType::Value surface)
{
	switch(face)
	{
	case TOP:
		*(top.value) = surface;
		break;
	case BOTTOM:
		*(bottom.value) = surface;
		break;
	case LEFT:
		*(left.value) = surface;
		break;
	case RIGHT:
		*(right.value) = surface;
		break;
	case FRONT:
		*(front.value) = surface;
		break;
	default:
		*(back.value) = surface;
	}
	changed = true;
}

void PartInstance::setParent(Instance* prnt)
{
	if(this->physBody != NULL && getParentDataModel() != NULL)
	{
		//TODO implement engine
		//getParentDataModel()->getEngine()->deleteBody(this);
	}
	Instance * cparent = getParent();
	//TODO implement workspace
	/*while(cparent != NULL)
	{
		if(WorkspaceInstance* workspace = dynamic_cast<WorkspaceInstance*>(cparent))
		{
			workspace->partObjects.erase(std::remove(workspace->partObjects.begin(), workspace->partObjects.end(), this), workspace->partObjects.end());
		}
		cparent = cparent->getParent();
	}*/
	Instance::setParent(prnt);
	cparent = getParent();
	//TODO implement workspace
	/*
	while(cparent != NULL)
	{
		if(WorkspaceInstance* workspace = dynamic_cast<WorkspaceInstance*>(cparent))
		{
			workspace->partObjects.push_back(this);
			break;
		}
		cparent = cparent->getParent();
	}*/
		
}

void PartInstance::setSize(Vector3 newSize)
{
	int minsize = 1;
	int maxsize = 512;
	changed = true;
	int sizex = (int)newSize.x;
	if(sizex <= 0)
		sizex = 1;
	if(sizex > 512)
		sizex = 512;

	int sizey = (int)newSize.y;
	if(sizey <= 0)
		sizey = 1;
	if(sizey > 512)
		sizey = 512;

	int sizez = (int)newSize.z;
	if(sizez <= 0)
		sizez = 1;
	if(sizez > 512)
		sizez = 512;

	if(*(shape.value) != Enum::Shape::Block)
	{
		int max = sizex;
		if(sizey > max)
			max = sizey;
		if(sizez > max)
			max = sizez;
		sizex = sizey = sizez = max;
	}

	*(size.value) = Vector3(sizex, sizey, sizez);

	if(this->physBody != NULL && getParentDataModel() != NULL)
		getParentDataModel()->getEngine()->resetBody(this);
}
Vector3 PartInstance::getSize()
{
	return *(size.value);
}
Vector3 PartInstance::getPosition()
{
	return *(position.value);
}
void PartInstance::setShape(Enum::Shape::Value shape)
{
	switch(shape)
	{
	case Enum::Shape::Block:
		*(this->shape.value) = shape;
		break;
	default:
		*(this->shape.value) = shape;
		this->setSize(this->getSize());
	}
	if(this->physBody != NULL && getParentDataModel() != NULL)
		getParentDataModel()->getEngine()->resetBody(this);

	changed = true;
}

void PartInstance::setPosition(Vector3 pos)
{
	*(position.value) = pos;
	setCFrame(CoordinateFrame(cFrame.value->rotation, pos));

	if (*(anchored.value) && getParentDataModel() != NULL)
		getParentDataModel()->getEngine()->resetBody(this);
}

void PartInstance::setAnchored(bool anchored)
{
	*(this->anchored.value) = anchored;
	if(this->physBody != NULL && getParentDataModel() != NULL)
		getParentDataModel()->getEngine()->resetBody(this);
}

bool PartInstance::isAnchored()
{
	return *(this->anchored.value);
}


CoordinateFrame PartInstance::getCFrame()
{
	return cFrame.value->rotation;
}
void PartInstance::setCFrame(CoordinateFrame coordinateFrame)
{
	setCFrameNoSync(coordinateFrame);
	if(getParentDataModel() != NULL)
		getParentDataModel()->getEngine()->updateBody(this);
}

void PartInstance::setCFrameNoSync(CoordinateFrame coordinateFrame)
{
	*(cFrame.value) = coordinateFrame;
	*(position.value) = coordinateFrame.translation;
}

bool PartInstance::collides(PartInstance * part)
{
	if(*(shape.value) == Enum::Shape::Block)
	{
		if(*(part->shape.value) == Enum::Shape::Block)
			return G3D::CollisionDetection::fixedSolidBoxIntersectsFixedSolidBox(getBox(), part->getBox());
		else
			return G3D::CollisionDetection::fixedSolidSphereIntersectsFixedSolidBox(part->getSphere(), getBox());
	}
	else
	{
		if(*(part->shape.value) == Enum::Shape::Block)
			return G3D::CollisionDetection::fixedSolidSphereIntersectsFixedSolidBox(getSphere(), part->getBox());
		else
			return G3D::CollisionDetection::fixedSolidSphereIntersectsFixedSolidSphere(getSphere(), part->getSphere());
	}
}

Box PartInstance::getBox()
{
	Box box = Box(Vector3(size.value->x/2, size.value->y/2, size.value->z/2) ,Vector3(-size.value->x/2,-size.value->y/2,-size.value->z/2));
	CoordinateFrame c = getCFrame();
	itemBox = c.toWorldSpace(box);
	return itemBox;
}

Sphere PartInstance::getSphere()
{
	Sphere sphere = Sphere(Vector3(0,0,0), size.value->y/2);
	CoordinateFrame c = getCFrame();
	return sphere;
}

bool PartInstance::collides(Box box)
{
	return CollisionDetection::fixedSolidBoxIntersectsFixedSolidBox(getBox(), box);
}

void PartInstance::render(RenderDevice* rd) {
 	if (changed)
	{
		changed=false;
		Vector3 renderSize = *(size.value)/2;
		glNewList(glList, GL_COMPILE);
		renderShape(*(this->shape.value), renderSize, *(color.value));
		renderSurface(TOP, *(this->top.value), renderSize, *(this->controller.value), *(color.value));
		renderSurface(FRONT, *(this->front.value), renderSize, *(this->controller.value), *(color.value));
		renderSurface(RIGHT, *(this->right.value), renderSize, *(this->controller.value), *(color.value));
		renderSurface(BACK, *(this->back.value), renderSize, *(this->controller.value), *(color.value));
		renderSurface(LEFT, *(this->left.value), renderSize, *(this->controller.value), *(color.value));
		renderSurface(BOTTOM, *(this->bottom.value), renderSize, *(this->controller.value), *(color.value));
		glEndList();
	}
	rd->setObjectToWorldMatrix(*(cFrame.value));
	glCallList(glList);
	postRender(rd);
}

PartInstance::~PartInstance(void)
{
	glDeleteLists(glList, 1);
	/*
	// Causes some weird ODE error
	// Someone, please look into this

	dBodyDestroy(physBody);
	for (int i = 0; i < 3; i++) {
		if (physGeom[i] != NULL) 
			dGeomDestroy(physGeom[i]);
	}
	*/
}

void PartInstance::onTouch()
{
	if(getParentDataModel() == NULL)
		return;
	if(*(singleShot.value) && _touchedOnce)
		return;

	if(*(singleShot.value) && !_touchedOnce)
		_touchedOnce = true;

	*(getParentDataModel()->getLevel()->score.value) += *(changeScore.value);
	*(getParentDataModel()->getLevel()->timer.value) += *(changeTimer.value);

	switch(*(onTouchAction.value))
	{
		case Enum::ActionType::Nothing:
			break;
		case Enum::ActionType::Pause:
			break;
		case Enum::ActionType::Lose:
			getParentDataModel()->getLevel()->loseCondition();
			break;
		case Enum::ActionType::Draw:
			break;
		case Enum::ActionType::Win:
			getParentDataModel()->getLevel()->winCondition();
			break;
	}

	//TODO implement SoundService
	/*
	SoundService* sndService = getParentDataModel()->getSoundService();

	switch(OnTouchSound)
	{
		case Enum::Sound::NoSound:
			break;
		case Enum::Sound::Victory:
			sndService->playSound(sndService->findFirstChild("Victory"));
			break;
		case Enum::Sound::Boing:
			sndService->playSound(sndService->findFirstChild("Boing"));
			break;
		case Enum::Sound::Break:
			sndService->playSound(sndService->findFirstChild("Break"));
			break;
		case Enum::Sound::Snap:
			sndService->playSound(sndService->findFirstChild("Snap"));
			break;
		case Enum::Sound::Bomb:
			sndService->playSound(sndService->findFirstChild("Bomb"));
			break;
		case Enum::Sound::Splat:
			sndService->playSound(sndService->findFirstChild("Splat"));
			break;
		case Enum::Sound::Page:
			sndService->playSound(sndService->findFirstChild("Page"));
			break;
		case Enum::Sound::Ping:
			sndService->playSound(sndService->findFirstChild("Ping"));
			break;
		case Enum::Sound::Swoosh:
			sndService->playSound(sndService->findFirstChild("Swoosh"));
			break;
		case Enum::Sound::Click:
			sndService->playSound(sndService->findFirstChild("Click"));
			break;
		case Enum::Sound::Clock:
			sndService->playSound(sndService->findFirstChild("Clock"));
			break;
		case Enum::Sound::Step:
			sndService->playSound(sndService->findFirstChild("Step"));
			break;
		case Enum::Sound::StepOn:
			sndService->playSound(sndService->findFirstChild("StepOn"));
			break;
	}*/
}
