#include "DataModelV2/PartInstance.h"
#include "Globals.h"
#include "Renderer.h"
#include <sstream>
#include <iomanip>
#include "Faces.h"
#include "AudioPlayer.h"
#include "StringFunctions.h"

PartInstance::PartInstance(void)
{
	PVInstance::PVInstance();
	physBody = NULL;
    glList = glGenLists(1);
	name = "Unnamed PVItem";
	className = "Part";
	canCollide = true;
	anchored = false;
	dragging = false;
	size = Vector3(2,1,4);
	setCFrame(CoordinateFrame(Vector3(0,0,0)));
	color = Color3::gray();
	velocity = Vector3(0,0,0);
	rotVelocity = Vector3(0,0,0);
	top = Enum::SurfaceType::Smooth;
    front = Enum::SurfaceType::Smooth;
    right = Enum::SurfaceType::Smooth;
	back = Enum::SurfaceType::Smooth;
	left = Enum::SurfaceType::Smooth;
	bottom = Enum::SurfaceType::Smooth;
	shape = Enum::Shape::Block;
	_touchedOnce = false;

	// OnTouch
	singleShot = true;
	touchesToTrigger = 1;
	uniqueObjectsToTrigger = 1;
	changeScore = 0;
	changeTimer = 0;
	singleShot = true;
}

bool PartInstance::isDragging()
{
	return dragging;
}

void PartInstance::setDragging(bool value)
{
	if (dragging != value)
	{
		dragging = value;
		g_dataModel->getEngine()->resetBody(this);
	}
}

float PartInstance::getMass()
{
	if(shape == Enum::Shape::Block)
		return size.x*size.y*size.z*0.7F;
	else 
		return 1.3333333333333333333333333333333F*(size.x/2)*(size.y/2)*(size.z/2)*0.7F;
}

Vector3 PartInstance::getVelocity()
{
	return velocity;
}
Vector3 PartInstance::getRotVelocity()
{
	return rotVelocity;
}

// OnTouch
bool PartInstance::isSingleShot()
{
	return singleShot;
}

int PartInstance::getTouchesToTrigger()
{
	return touchesToTrigger;
}

int PartInstance::getUniqueObjectsToTrigger()
{
	return uniqueObjectsToTrigger;
}

int PartInstance::getChangeScore()
{
	return changeScore;
}

float PartInstance::getChangeTimer()
{
	return changeTimer;
}

void PartInstance::setVelocity(Vector3 v)
{
	velocity = v;
}
void PartInstance::setRotVelocity(Vector3 v)
{
	rotVelocity = v;
}

void PartInstance::postRender(RenderDevice *rd)
{
	// possibly descard this function...
}

void PartInstance::renderName(RenderDevice *rd)
{
	if(!nameShown)
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
		Vector3 gamepoint = position + Vector3(0,1.5,0);
		Vector3 camerapoint = rd->getCameraToWorldMatrix().translation;
		float distance = pow(pow((double)gamepoint.x - (double)camerapoint.x, 2) + pow((double)gamepoint.y - (double)camerapoint.y, 2) + pow((double)gamepoint.z - (double)camerapoint.z, 2), 0.5);
		if(distance < 100 && distance > -100)
		{
			if(distance < 0)
			distance = distance*-1;
			glDisable(GL_DEPTH_TEST);
			fnt->draw3D(rd, name, CoordinateFrame(rd->getCameraToWorldMatrix().rotation, gamepoint), 0.03*distance, Color3::yellow(), Color3::black(), G3D::GFont::XALIGN_CENTER, G3D::GFont::YALIGN_CENTER);
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
		top = surface;
		break;
	case BOTTOM:
		bottom = surface;
		break;
	case LEFT:
		left = surface;
		break;
	case RIGHT:
		right = surface;
		break;
	case FRONT:
		front = surface;
		break;
	default:
		back = surface;
	}
	changed = true;
}

void PartInstance::setParent(Instance* prnt)
{
	if(this->physBody != NULL)
	{
		g_dataModel->getEngine()->deleteBody(this);
	}
	Instance * cparent = getParent();
	while(cparent != NULL)
	{
		if(WorkspaceInstance* workspace = dynamic_cast<WorkspaceInstance*>(cparent))
		{
			workspace->partObjects.erase(std::remove(workspace->partObjects.begin(), workspace->partObjects.end(), this), workspace->partObjects.end());
		}
		cparent = cparent->getParent();
	}
	Instance::setParent(prnt);
	cparent = getParent();
	while(cparent != NULL)
	{
		if(WorkspaceInstance* workspace = dynamic_cast<WorkspaceInstance*>(cparent))
		{
			workspace->partObjects.push_back(this);
			break;
		}
		cparent = cparent->getParent();
	}
		
}

PartInstance::PartInstance(const PartInstance &oinst)
{
	PVInstance::PVInstance(oinst);
	physBody = NULL;
	glList = glGenLists(1);
	name = oinst.name;
	canCollide = oinst.canCollide;
	setParent(oinst.parent);
	anchored = oinst.anchored;
	size = oinst.size;
	setCFrameNoSync(oinst.cFrame);
	color = oinst.color;
	velocity = oinst.velocity;
	rotVelocity = oinst.rotVelocity;
	top = oinst.top;
	front = oinst.front;
	right = oinst.right;
	back = oinst.back;
	left = oinst.left;
	bottom = oinst.bottom;
	shape = oinst.shape;
	changed = true;

	// OnTouch
	singleShot = oinst.singleShot;
	touchesToTrigger = oinst.touchesToTrigger;
	uniqueObjectsToTrigger = oinst.uniqueObjectsToTrigger;
	changeScore = oinst.changeScore;
	changeTimer = oinst.changeTimer;
	OnTouchAction = oinst.OnTouchAction;
	OnTouchSound = oinst.OnTouchSound;
	singleShot = oinst.singleShot;
	_touchedOnce = false;
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

	if(shape != Enum::Shape::Block)
	{
		int max = sizex;
		if(sizey > max)
			max = sizey;
		if(sizez > max)
			max = sizez;
		sizex = sizey = sizez = max;
	}

	size = Vector3(sizex, sizey, sizez);

	if(this->physBody != NULL)
		g_dataModel->getEngine()->resetBody(this);
}
Vector3 PartInstance::getSize()
{
	return size;
}
Vector3 PartInstance::getPosition()
{
	return position;
}
void PartInstance::setShape(Enum::Shape::Value shape)
{
	switch(shape)
	{
	case Enum::Shape::Block:
		this->shape = shape;
		break;
	default:
		this->shape = shape;
		this->setSize(this->getSize());
	}
	if(this->physBody != NULL)
		g_dataModel->getEngine()->resetBody(this);

	changed = true;
}

void PartInstance::setPosition(Vector3 pos)
{
	position = pos;
	setCFrame(CoordinateFrame(cFrame.rotation, pos));

	if (anchored)
		g_dataModel->getEngine()->resetBody(this);
}

void PartInstance::setAnchored(bool anchored)
{
	this->anchored = anchored;
	if(this->physBody != NULL)
		g_dataModel->getEngine()->resetBody(this);
}

bool PartInstance::isAnchored()
{
	return this->anchored;
}


CoordinateFrame PartInstance::getCFrame()
{
	return cFrame;
}
void PartInstance::setCFrame(CoordinateFrame coordinateFrame)
{
	setCFrameNoSync(coordinateFrame);
		g_dataModel->getEngine()->updateBody(this);
}

void PartInstance::setCFrameNoSync(CoordinateFrame coordinateFrame)
{
	cFrame = coordinateFrame;
	position = coordinateFrame.translation;
}

bool PartInstance::collides(PartInstance * part)
{
	if(shape == Enum::Shape::Block)
	{
		if(part->shape == Enum::Shape::Block)
			return G3D::CollisionDetection::fixedSolidBoxIntersectsFixedSolidBox(getBox(), part->getBox());
		else
			return G3D::CollisionDetection::fixedSolidSphereIntersectsFixedSolidBox(part->getSphere(), getBox());
	}
	else
	{
		if(part->shape == Enum::Shape::Block)
			return G3D::CollisionDetection::fixedSolidSphereIntersectsFixedSolidBox(getSphere(), part->getBox());
		else
			return G3D::CollisionDetection::fixedSolidSphereIntersectsFixedSolidSphere(getSphere(), part->getSphere());
	}
}

Box PartInstance::getBox()
{
	Box box = Box(Vector3(size.x/2, size.y/2, size.z/2) ,Vector3(-size.x/2,-size.y/2,-size.z/2));
	CoordinateFrame c = getCFrame();
	itemBox = c.toWorldSpace(box);
	return itemBox;
}

Sphere PartInstance::getSphere()
{
	Sphere sphere = Sphere(Vector3(0,0,0), size.y/2);
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
		Vector3 renderSize = size/2;
		glNewList(glList, GL_COMPILE);
		renderShape(this->shape, renderSize, color);
		renderSurface(TOP, this->top, renderSize, this->controller, color);
		renderSurface(FRONT, this->front, renderSize, this->controller, color);
		renderSurface(RIGHT, this->right, renderSize, this->controller, color);
		renderSurface(BACK, this->back, renderSize, this->controller, color);
		renderSurface(LEFT, this->left, renderSize, this->controller, color);
		renderSurface(BOTTOM, this->bottom, renderSize, this->controller, color);
		glEndList();
	}
	rd->setObjectToWorldMatrix(cFrame);
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

char pto[512];
char pto2[512];
#include <sstream>

// Shape
static Enum::Shape::Value strEnum(TCHAR* shape)
{
	if(strcmp("Block", shape) == 0)
		return Enum::Shape::Block;
	if(strcmp("Cylinder", shape) == 0)
		return Enum::Shape::Cylinder;
	return Enum::Shape::Ball;
}

static TCHAR* enumStr(int shape)
{
	switch(shape)
	{
		case Enum::Shape::Block:
			return "Block";
		case Enum::Shape::Ball:
			return "Ball";
		case Enum::Shape::Cylinder:
			return "Cylinder";
	}
	return "Block";
}

// ActionType
static TCHAR* strActionType(int option)
{
	switch(option)
	{
		case Enum::ActionType::Nothing:
			return "Nothing";
		case Enum::ActionType::Pause:
			return "Pause";
		case Enum::ActionType::Lose:
			return "Lose";
		case Enum::ActionType::Draw:
			return "Draw";
		case Enum::ActionType::Win:
			return "Win";
	}
	return "Nothing";
}

static Enum::ActionType::Value EnumOnTouchActionType(TCHAR* option)
{
	if(strcmp("Nothing", option) == 0)
		return Enum::ActionType::Nothing;
	if(strcmp("Pause", option) == 0)
		return Enum::ActionType::Pause;
	if(strcmp("Lose", option) == 0)
		return Enum::ActionType::Lose;
	if(strcmp("Draw", option) == 0)
		return Enum::ActionType::Draw;
	return Enum::ActionType::Win;
}

// SoundType
static TCHAR* strSoundType(int option)
{
	switch(option)
	{
		case Enum::Sound::NoSound:
			return "NoSound";
		case Enum::Sound::Victory:
			return "Victory";
		case Enum::Sound::Boing:
			return "Boing";
		case Enum::Sound::Splat:
			return "Splat";
		case Enum::Sound::Snap:
			return "Snap";
		case Enum::Sound::Bomb:
			return "Bomb";
		case Enum::Sound::Break:
			return "Break";
		case Enum::Sound::Ping:
			return "Ping";
		case Enum::Sound::Swoosh:
			return "Swoosh";
		case Enum::Sound::Page:
			return "Page";
	}
	return "NoSound";
}

static Enum::Sound::Value EnumOnTouchSoundType(TCHAR* option)
{
	if(strcmp("Nothing", option) == 0)
		return Enum::Sound::NoSound;
	if(strcmp("Victory", option) == 0)
		return Enum::Sound::Victory;
	if(strcmp("Boing", option) == 0)
		return Enum::Sound::Boing;
	if(strcmp("Splat", option) == 0)
		return Enum::Sound::Splat;
	if(strcmp("Bomb", option) == 0)
		return Enum::Sound::Bomb;
	if(strcmp("Break", option) == 0)
		return Enum::Sound::Break;
	if(strcmp("Swoosh", option) == 0)
		return Enum::Sound::Swoosh;
	if(strcmp("Page", option) == 0)
		return Enum::Sound::Page;
	if(strcmp("Ping", option) == 0)
		return Enum::Sound::Ping;
	if(strcmp("Snap", option) == 0)
		return Enum::Sound::Snap;

	return Enum::Sound::NoSound;
}

void PartInstance::onTouch()
{
	if(singleShot && _touchedOnce)
		return;

	if(singleShot && !_touchedOnce)
		_touchedOnce = true;

	g_dataModel->getLevel()->score += changeScore;
	g_dataModel->getLevel()->timer += changeTimer;

	switch(OnTouchAction)
	{
		case Enum::ActionType::Nothing:
			break;
		case Enum::ActionType::Pause:
			break;
		case Enum::ActionType::Lose:
			g_dataModel->getLevel()->loseCondition();
			break;
		case Enum::ActionType::Draw:
			break;
		case Enum::ActionType::Win:
			g_dataModel->getLevel()->winCondition();
			break;
	}

	SoundService* sndService = g_dataModel->getSoundService();

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
	}
}

void PartInstance::PropUpdate(LPPROPGRIDITEM &item)
{
	setChanged();
	if(strcmp(item->lpszPropName, "Color3") == 0)
	{
		color = Color3(
			GetRValue(item->lpCurValue)/255.0F,
			GetGValue(item->lpCurValue)/255.0F,
			GetBValue(item->lpCurValue)/255.0F
		);
	}
	else if(strcmp(item->lpszPropName, "Anchored") == 0)
	{
		setAnchored(item->lpCurValue == TRUE);
	}
	else if(strcmp(item->lpszPropName, "Offset") == 0)
	{
		std::string str = (LPTSTR)item->lpCurValue;
		std::vector<float> vect;
		std::stringstream ss(str);
		float i;

		while (ss >> i)
		{
			vect.push_back(i);

			if (ss.peek() == ',')
				ss.ignore();
		}

		if(vect.size() == 3)
		{
			Vector3 pos(vect.at(0),vect.at(1),vect.at(2));
			setPosition(pos);
		}
	}

	else if(strcmp(item->lpszPropName, "Size") == 0)
	{
		std::string str = (LPTSTR)item->lpCurValue;
		std::vector<float> vect;
		std::stringstream ss(str);
		float i;

		while (ss >> i)
		{
			vect.push_back(i);

			if (ss.peek() == ',')
				ss.ignore();
		}

		if(vect.size() == 3)
		{
			Vector3 size(vect.at(0),vect.at(1),vect.at(2));
			setSize(size);
		}
	}
	else if(strcmp(item->lpszPropName, "Shape") == 0)
	{
		printf("%s", enumStr(strEnum((TCHAR*)item->lpCurValue)));
		setShape(strEnum((TCHAR*)item->lpCurValue));
	}
	else if(strcmp(item->lpszPropName, "Action") == 0)
	{
		OnTouchAction = EnumOnTouchActionType((TCHAR*)item->lpCurValue);
	}
	else if (strcmp(item->lpszPropName, "Sound") == 0)
	{
		OnTouchSound = EnumOnTouchSoundType((TCHAR*)item->lpCurValue);
	}
	else if (strcmp(item->lpszPropName, "ChangeScore") == 0)
	{
		changeScore = atoi((LPSTR)item->lpCurValue);
	}
	else if (strcmp(item->lpszPropName, "ChangeTimer") == 0)
	{
		changeTimer = atof((LPSTR)item->lpCurValue);
	}
	else if (strcmp(item->lpszPropName, "SingleShot") == 0)
	{
		singleShot = item->lpCurValue == TRUE;
	}
	else PVInstance::PropUpdate(item);
}

// This needs to be changed, buffer size of 12 is way too small
// Crash occurs if you put a huge number in
char changeTimerTxt[12];
char changeScoreTxt[12];
std::vector<PROPGRIDITEM> PartInstance::getProperties()
{
	std::vector<PROPGRIDITEM> properties = PVInstance::getProperties();


	properties.push_back(createPGI("Properties",
		"Color3",
		"The color of the selected part",
		RGB((color.r*255),(color.g*255),(color.b*255)),
		PIT_COLOR
		));
	properties.push_back(createPGI("Item",
		"Anchored",
		"Whether the block can move or not",
		(LPARAM)anchored,
		PIT_CHECK
		));
	sprintf_s(pto, "%g, %g, %g", position.x, position.y, position.z);
	properties.push_back(createPGI("Item",
		"Offset",
		"The position of the object in the workspace",
		(LPARAM)pto,
		PIT_EDIT
		));
	sprintf_s(pto2, "%g, %g, %g", size.x, size.y, size.z);
	properties.push_back(createPGI("Item",
		"Size",
		"The size of the object in the workspace",
		(LPARAM)pto2,
		PIT_EDIT
		));
	properties.push_back(createPGI("Item",
		"Shape",
		"The shape of the object in the workspace",
		(LPARAM)enumStr(shape),
		PIT_COMBO,
		TEXT("Ball\0Block\0Cylinder\0")
		));
	properties.push_back(createPGI("OnTouch",
		"Action",
		"What action is taken when touched",
		(LPARAM)strActionType(OnTouchAction),
		PIT_COMBO,
		TEXT("Nothing\0Pause\0Lose\0Draw\0Win\0")
		));
	properties.push_back(createPGI("OnTouch",
		"Sound",
		"What sound plays when touched",
		(LPARAM)strSoundType(OnTouchSound),
		PIT_COMBO,
		TEXT("NoSound\0Victory\0Boing\0Break\0Snap\0Bomb\0Splat\0Page\0Ping\0Swoosh\0")
		));

		sprintf_s(changeScoreTxt, "%d", changeScore);
		sprintf_s(changeTimerTxt, "%g", changeTimer);
	properties.push_back(createPGI("OnTouch",
		"ChangeScore",
		"How the score is affected when touched",
		(LPARAM)changeScoreTxt,
		PIT_EDIT));
	properties.push_back(createPGI("OnTouch",
		"ChangeTimer",
		"How the timer is affected when touched",
		(LPARAM)changeTimerTxt,
		PIT_EDIT));
	properties.push_back(createPGI("OnTouch",
		"SingleShot",
		"Whether or not Action happens only once",
		(LPARAM)singleShot,
		PIT_CHECK
		));
	return properties;
}


