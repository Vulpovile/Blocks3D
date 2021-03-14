#include "DataModelV2/PartInstance.h"
#include "Globals.h"
#include "../../Renderer.h"
#include <sstream>
#include <iomanip>


PartInstance::PartInstance(void) : _bevelSize(0.07f), _parseVert(0), _debugTimer(0)
{
	PVInstance::PVInstance();
    glList = glGenLists(1);
	name = "Unnamed PVItem";
	className = "Part";
	canCollide = true;
	anchored = false;
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
}


Vector3 PartInstance::getVelocity()
{
	return velocity;
}
Vector3 PartInstance::getRotVelocity()
{
	return rotVelocity;
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

void PartInstance::setParent(Instance* prnt)
{
	Instance * cparent = getParent();
	while(cparent != NULL)
	{
		if(WorkspaceInstance* workspace = dynamic_cast<WorkspaceInstance*>(cparent))
		{
			std::cout << "Removed from partarray " << std::endl;
			workspace->partObjects.erase(std::remove(workspace->partObjects.begin(), workspace->partObjects.end(), this), workspace->partObjects.end());
			break;
		}
		cparent = cparent->getParent();
	}
	Instance::setParent(prnt);
	while(parent != NULL)
	{
		if(WorkspaceInstance* workspace = dynamic_cast<WorkspaceInstance*>(parent))
		{
			workspace->partObjects.push_back(this);
			break;
		}
		parent = parent->getParent();
	}
}

PartInstance::PartInstance(const PartInstance &oinst)  : _bevelSize(0.07f), _parseVert(0), _debugTimer(0)
{
	PVInstance::PVInstance(oinst);
	glList = glGenLists(1);
	//name = oinst.name;
	//className = "Part";
	name = oinst.name;
	canCollide = oinst.canCollide;
	setParent(oinst.parent);
	anchored = oinst.anchored;
	size = oinst.size;
	setCFrame(oinst.cFrame);
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
	changed = true;
}

void PartInstance::setPosition(Vector3 pos)
{
	position = pos;
	cFrame = CoordinateFrame(cFrame.rotation, pos);
	changed = true;
}

CoordinateFrame PartInstance::getCFrame()
{
	return cFrame;
}
void PartInstance::setCFrame(CoordinateFrame coordinateFrame)
{
	cFrame = coordinateFrame;
	position = coordinateFrame.translation;
	changed = true;
}
// Can probably be deleted
CoordinateFrame PartInstance::getCFrameRenderBased()
{
	return cFrame;//CoordinateFrame(getCFrame().rotation,Vector3(getCFrame().translation.x, getCFrame().translation.y, getCFrame().translation.z));
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

#ifdef NEW_BOX_RENDER
Box PartInstance::getBox()
{
	Box box = Box(Vector3(size.x/2, size.y/2, size.z/2) ,Vector3(-size.x/2,-size.y/2,-size.z/2));
	CoordinateFrame c = getCFrameRenderBased();
	itemBox = c.toWorldSpace(box);
	return itemBox;
}
Sphere PartInstance::getSphere()
{
	Sphere sphere = Sphere(Vector3(0,0,0), size.y/2);
	CoordinateFrame c = getCFrameRenderBased();
	//itemBox = c.toWorldSpace(Sphere);
	return sphere;//itemBox;
}
#else
Box PartInstance::getBox()
{
	if(changed)
	{
		Box box = Box(Vector3(0+size.x/4, 0+size.y/4, 0+size.z/4) ,Vector3(0-size.x/4,0-size.y/4,0-size.z/4));
		CoordinateFrame c = getCFrameRenderBased();
		itemBox = c.toWorldSpace(box);
		Vector3 v0,v1,v2,v3;
		for (int f = 0; f < 6; f++) {
			itemBox.getFaceCorners(f, v0,v1,v2,v3);
			_vertices[f*16] = v0.x;
			_vertices[(f*16)+1] = v0.y;
			_vertices[(f*16)+2] = v0.z;
			_vertices[(f*16)+3] = v1.x;
			_vertices[(f*16)+4] = v1.y;
			_vertices[(f*16)+5] = v1.z;
			_vertices[(f*16)+6] = v2.x;
			_vertices[(f*16)+7] = v2.y;
			_vertices[(f*16)+8] = v2.z;
			_vertices[(f*16)+9] = v3.x;
			_vertices[(f*16)+10] = v3.y;
			_vertices[(f*16)+11] = v3.z;
			_vertices[(f*16)+12] = color.r;
			_vertices[(f*16)+13] = color.g;
			_vertices[(f*16)+14] = color.b;
			_vertices[(f*16)+15] = 1;
		}
	}
	return itemBox;
}
#endif

bool PartInstance::collides(Box box)
{
	return CollisionDetection::fixedSolidBoxIntersectsFixedSolidBox(getBox(), box);
}
#ifdef NEW_BOX_RENDER



/*void PartInstance::addPlus(Vector3 v1)
{
	float renderY = max(size.z, max(size.x, size.y))/2 * 0.775;
	Vector3 vx1 = v1 + Vector3(0, -renderY, -0.1f);
	Vector3 vx2 = v1 + Vector3(0, -renderY, 0.1f);
	Vector3 vx3 = v1 + Vector3(0, renderY, 0.1f);

	addVertex(vx1,Color3::WHITE);
	addVertex(vx2,Color3::WHITE);
	addVertex(vx3,Color3::WHITE);
	//addNormals(cross(v2-v1,v3-v1).direction());
	addSingularNormal(cross(vx2-vx1,vx3-vx1).direction());
	addSingularNormal(cross(vx3-vx2,vx1-vx2).direction());
	addSingularNormal(cross(vx1-vx3,vx2-vx3).direction());

	vx1 = v1 + Vector3(0, renderY, 0.1f);
	vx2 = v1 + Vector3(0, renderY, -0.1f);
	vx3 = v1 + Vector3(0, -renderY, -0.1f);

	addVertex(vx1,Color3::WHITE);
	addVertex(vx2,Color3::WHITE);
	addVertex(vx3,Color3::WHITE);
	//addNormals(cross(v2-v1,v3-v1).direction());
	addSingularNormal(cross(vx2-vx1,vx3-vx1).direction());
	addSingularNormal(cross(vx3-vx2,vx1-vx2).direction());
	addSingularNormal(cross(vx1-vx3,vx2-vx3).direction());

	vx3 = v1 + Vector3(0, -0.1f, -renderY);
	vx2 = v1 + Vector3(0, 0.1f, -renderY);
	vx1 = v1 + Vector3(0, 0.1f, renderY);

	addVertex(vx1,Color3::WHITE);
	addVertex(vx2,Color3::WHITE);
	addVertex(vx3,Color3::WHITE);
	//addNormals(cross(v2-v1,v3-v1).direction());
	addSingularNormal(cross(vx2-vx1,vx3-vx1).direction());
	addSingularNormal(cross(vx3-vx2,vx1-vx2).direction());
	addSingularNormal(cross(vx1-vx3,vx2-vx3).direction());

	vx3 = v1 + Vector3(0, 0.1f, renderY);
	vx2 = v1 + Vector3(0, -0.1f, renderY);
	vx1 = v1 + Vector3(0, -0.1f, -renderY);

	addVertex(vx1,Color3::WHITE);
	addVertex(vx2,Color3::WHITE);
	addVertex(vx3,Color3::WHITE);
	//addNormals(cross(v2-v1,v3-v1).direction());
	addSingularNormal(cross(vx2-vx1,vx3-vx1).direction());
	addSingularNormal(cross(vx3-vx2,vx1-vx2).direction());
	addSingularNormal(cross(vx1-vx3,vx2-vx3).direction());

}


void PartInstance::addPlus2(Vector3 v1)
{
	float renderY = max(size.z, max(size.x, size.y))/2 * 0.775;
	Vector3 vx3 = v1 + Vector3(0, -renderY, -0.1f);
	Vector3 vx2 = v1 + Vector3(0, -renderY, 0.1f);
	Vector3 vx1 = v1 + Vector3(0, renderY, 0.1f);

	addVertex(vx1,Color3::WHITE);
	addVertex(vx2,Color3::WHITE);
	addVertex(vx3,Color3::WHITE);
	//addNormals(cross(v2-v1,v3-v1).direction());
	addSingularNormal(cross(vx2-vx1,vx3-vx1).direction());
	addSingularNormal(cross(vx3-vx2,vx1-vx2).direction());
	addSingularNormal(cross(vx1-vx3,vx2-vx3).direction());

	vx3 = v1 + Vector3(0, renderY, 0.1f);
	vx2 = v1 + Vector3(0, renderY, -0.1f);
	vx1 = v1 + Vector3(0, -renderY, -0.1f);

	addVertex(vx1,Color3::WHITE);
	addVertex(vx2,Color3::WHITE);
	addVertex(vx3,Color3::WHITE);
	//addNormals(cross(v2-v1,v3-v1).direction());
	addSingularNormal(cross(vx2-vx1,vx3-vx1).direction());
	addSingularNormal(cross(vx3-vx2,vx1-vx2).direction());
	addSingularNormal(cross(vx1-vx3,vx2-vx3).direction());

	vx1 = v1 + Vector3(0, -0.1f, -renderY);
	vx2 = v1 + Vector3(0, 0.1f, -renderY);
	vx3 = v1 + Vector3(0, 0.1f, renderY);

	addVertex(vx1,Color3::WHITE);
	addVertex(vx2,Color3::WHITE);
	addVertex(vx3,Color3::WHITE);
	//addNormals(cross(v2-v1,v3-v1).direction());
	addSingularNormal(cross(vx2-vx1,vx3-vx1).direction());
	addSingularNormal(cross(vx3-vx2,vx1-vx2).direction());
	addSingularNormal(cross(vx1-vx3,vx2-vx3).direction());

	vx1 = v1 + Vector3(0, 0.1f, renderY);
	vx2 = v1 + Vector3(0, -0.1f, renderY);
	vx3 = v1 + Vector3(0, -0.1f, -renderY);

	addVertex(vx1,Color3::WHITE);
	addVertex(vx2,Color3::WHITE);
	addVertex(vx3,Color3::WHITE);
	//addNormals(cross(v2-v1,v3-v1).direction());
	addSingularNormal(cross(vx2-vx1,vx3-vx1).direction());
	addSingularNormal(cross(vx3-vx2,vx1-vx2).direction());
	addSingularNormal(cross(vx1-vx3,vx2-vx3).direction());

}
*/


//int rings = 15;
//int sectors = 15;
void PartInstance::render(RenderDevice* rd) {
	int sectorCount = 12;
	int stackCount = 12;
	float radius = 0.5F;
	//if(nameShown)
		//postRenderStack.push_back(this);
 	if (changed)
	{

		getBox();
		//std::vector<GLfloat>(_vertices).swap(_vertices); //Clear the memory
		Vector3 renderSize = size/2;
		
		glNewList(glList, GL_COMPILE_AND_EXECUTE);
		glColor(this->color);
		renderShape(this->shape, renderSize, color);
		glEndList();
		changed = false;
		return;

 		changed=false;
		
	}
	rd->setObjectToWorldMatrix(cFrame);
	glCallList(glList);
	postRender(rd);
	//rd->setObjectToWorldMatrix(cFrame);

}
#else
void PartInstance::render(RenderDevice* rd)
{

	if(changed)
	{
		Box box = getBox();
	changed = false;
	glNewList(glList, GL_COMPILE);
	glColor(color);
	/*glEnable( GL_TEXTURE_2D );
	glEnable(GL_BLEND);// you enable blending function
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glBindTexture( GL_TEXTURE_2D, Globals::surfaceId);
	glBegin(GL_QUADS);*/
    for(int i = 0; i < 96; i+=16)
	{
		/*double add = 0.8;
		Enum::SurfaceType::Value face;
		if(i == 0)//Back
			face = back;
		else if(i == 16)//Right
			face = right;
		else if(i == 32)//Front
			face = front;
		else if(i == 48)//Top
			face = top;
		else if(i == 64)//Left
			face = left;
		else if(i == 80)//Bottom
			face = bottom;

		/*if(face == Snaps)
			add = 0.0;
		else if(face == Inlets)
			add = 0.2;*/

		Vector3 v0 = Vector3(_vertices[i], _vertices[i+1], _vertices[i+2]), v1 = Vector3(_vertices[i+3], _vertices[i+4], _vertices[i+5]), v3 = Vector3(_vertices[i+9], _vertices[i+10], _vertices[i+11]);
		/*glNormal3fv((v1 - v0).cross(v3 - v0).direction());
		glTexCoord2f(0.0F,0.0F);
		glVertex3fv(v0);
		glTexCoord2f(1.0F,0.0F);
		glVertex3fv(v1);
		glTexCoord2f(1.0F,0.25F);
		glVertex3f(_vertices[i+6], _vertices[i+7], _vertices[i+8]);
		glTexCoord2f(0.0F,0.25F);
		glVertex3fv(v3);*/

		glEnable(GL_BLEND);// you enable blending function
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glBegin( GL_QUADS );
		glNormal3fv((v1 - v0).cross(v3 - v0).direction());
		//glTexCoord2d(0.0,0.0+add);
		glVertex3fv(v0);
		//glTexCoord2d( 1.0,0.0+add);
		glVertex3fv(v1);
		//glTexCoord2d(1.0,0.2+add);
		glVertex3f(_vertices[i+6], _vertices[i+7], _vertices[i+8]);
		//glTexCoord2d( 0.0,0.2+add);
		glVertex3fv(v3);
		glEnd();
		//glDisable( GL_TEXTURE_2D );
	}
	glEndList();
	/*glEnd();
	glDisable(GL_TEXTURE_2D);*/
	}
	glCallList(glList);
	glColor(Color3::white());
	if(!children.empty())
	{
		for(size_t i = 0; i < children.size(); i++)
		{
			children.at(i)->render(rd);
		}
	}

}
#endif

PartInstance::~PartInstance(void)
{
	glDeleteLists(glList, 1);
}
char pto[512];
char pto2[512];
#include <sstream>

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

void PartInstance::PropUpdate(LPPROPGRIDITEM &item)
{
	if(strcmp(item->lpszPropName, "Color3") == 0)
	{
		color = Color3(GetRValue(item->lpCurValue)/255.0F,GetGValue(item->lpCurValue)/255.0F,GetBValue(item->lpCurValue)/255.0F);
		changed=true;
	}
	if(strcmp(item->lpszPropName, "Anchored") == 0)
	{
		anchored= item->lpCurValue == TRUE;
		changed=true;
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

		//if(vect.size() != 3)
		//{
			//sprintf(pto, "%g, %g, %g", cFrame.translation.x, cFrame.translation.y, cFrame.translation.z, "what");
			//LPCSTR str = LPCSTR(pto);
			//item->lpCurValue = (LPARAM)str;
		//}
		//else
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

		/*if(vect.size() != 3)
		{
			sprintf(pto, "%g, %g, %g", cFrame.translation.x, cFrame.translation.y, cFrame.translation.z, "what");
			LPCSTR str = LPCSTR(pto);
			item->lpCurValue = (LPARAM)str;
		}
		else*/
		if(vect.size() == 3)
		{
			Vector3 size(vect.at(0),vect.at(1),vect.at(2));
			setSize(size);
		}
	}
	if(strcmp(item->lpszPropName, "Shape") == 0)
	{
		printf("%s", enumStr(strEnum((TCHAR*)item->lpCurValue)));
		setShape(strEnum((TCHAR*)item->lpCurValue));
	}
	else PVInstance::PropUpdate(item);
}



std::vector<PROPGRIDITEM> PartInstance::getProperties()
{
	std::vector<PROPGRIDITEM> properties = PVInstance::getProperties();


	properties.push_back(createPGI(
		"Properties",
		"Color3",
		"The color of the selected part",
		RGB((color.r*255),(color.g*255),(color.b*255)),
		PIT_COLOR
		));
	properties.push_back(createPGI(
		"Item",
		"Anchored",
		"Whether the block can move or not",
		(LPARAM)anchored,
		PIT_CHECK
		));
	sprintf(pto, "%g, %g, %g", position.x, position.y, position.z);
	properties.push_back(createPGI(
		"Item",
		"Offset",
		"The position of the object in the workspace",
		(LPARAM)pto,
		PIT_EDIT
		));
	sprintf(pto2, "%g, %g, %g", size.x, size.y, size.z);
	properties.push_back(createPGI(
		"Item",
		"Size",
		"The position of the object in the workspace",
		(LPARAM)pto2,
		PIT_EDIT
		));
	properties.push_back(createPGI(
		"Item",
		"Shape",
		"The shape of the object in the workspace",
		(LPARAM)enumStr(shape),
		PIT_COMBO,
		TEXT("Ball\0Block\0Cylinder\0")
		));
	return properties;
}


