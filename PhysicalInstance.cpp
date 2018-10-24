#include "PhysicalInstance.h"
#include "Globals.h"


PhysicalInstance::PhysicalInstance(void)
{
    name = "Default PhysicalInstance";
	className = "Part";
	canCollide = true;
	anchored = true;
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
}

PhysicalInstance::PhysicalInstance(const PhysicalInstance &oinst)
{
	name = oinst.name;
	className = "Part";
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
}

void PhysicalInstance::setSize(Vector3 newSize)
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

	size = Vector3(sizex, sizey, sizez);



}
Vector3 PhysicalInstance::getSize()
{
	return size;
}
Vector3 PhysicalInstance::getPosition()
{
	return position;
}
void PhysicalInstance::setPosition(Vector3 pos)
{
	position = pos;
	cFrame = CoordinateFrame(pos);
	changed = true;
}
CoordinateFrame PhysicalInstance::getCFrame()
{
	return cFrame;
}
void PhysicalInstance::setCFrame(CoordinateFrame coordinateFrame)
{
	cFrame = coordinateFrame;
	position = coordinateFrame.translation;
	changed = true;
}

CoordinateFrame PhysicalInstance::getCFrameRenderBased()
{
	return CoordinateFrame(getCFrame().rotation,Vector3(getCFrame().translation.x/2, getCFrame().translation.y/2, getCFrame().translation.z/2));
}

Box PhysicalInstance::getBox()
{
	if(changed)
	{
		Box box = Box(Vector3(0+size.x/4, 0+size.y/4, 0+size.z/4) ,Vector3(0-size.x/4,0-size.y/4,0-size.z/4));
		CoordinateFrame c = getCFrameRenderBased();
		itemBox = c.toWorldSpace(box);
		Vector3 v0,v1,v2,v3;
		for (int f = 0; f < 6; f++) {
			itemBox.getFaceCorners(f, v0,v1,v2,v3);
			vertecies[f*16] = v0.x;
			vertecies[(f*16)+1] = v0.y;
			vertecies[(f*16)+2] = v0.z;
			vertecies[(f*16)+3] = v1.x;
			vertecies[(f*16)+4] = v1.y;
			vertecies[(f*16)+5] = v1.z;
			vertecies[(f*16)+6] = v2.x;
			vertecies[(f*16)+7] = v2.y;
			vertecies[(f*16)+8] = v2.z;
			vertecies[(f*16)+9] = v3.x;
			vertecies[(f*16)+10] = v3.y;
			vertecies[(f*16)+11] = v3.z;
			vertecies[(f*16)+12] = color.r;
			vertecies[(f*16)+13] = color.g;
			vertecies[(f*16)+14] = color.b;
			vertecies[(f*16)+15] = 1;
		}
	}
	return itemBox;
}

bool PhysicalInstance::collides(Box box)
{
	return CollisionDetection::fixedSolidBoxIntersectsFixedSolidBox(getBox(), box);
}

void PhysicalInstance::render(RenderDevice* rd)
{
	if(changed)
		Box box = getBox();
	
	glColor(color);
	/*glEnable( GL_TEXTURE_2D );
	glEnable(GL_BLEND);// you enable blending function
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); 
	glBindTexture( GL_TEXTURE_2D, Globals::surfaceId);
	glBegin(GL_QUADS);*/
    for(int i = 0; i < 96; i+=16)
	{
		double add = 0.8;
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

		Vector3 v0 = Vector3(vertecies[i], vertecies[i+1], vertecies[i+2]), v1 = Vector3(vertecies[i+3], vertecies[i+4], vertecies[i+5]), v3 = Vector3(vertecies[i+9], vertecies[i+10], vertecies[i+11]);
		/*glNormal3fv((v1 - v0).cross(v3 - v0).direction());
		glTexCoord2f(0.0F,0.0F);
		glVertex3fv(v0);
		glTexCoord2f(1.0F,0.0F);
		glVertex3fv(v1);
		glTexCoord2f(1.0F,0.25F);
		glVertex3f(vertecies[i+6], vertecies[i+7], vertecies[i+8]);
		glTexCoord2f(0.0F,0.25F);
		glVertex3fv(v3);*/

		glEnable( GL_TEXTURE_2D );
		glEnable(GL_BLEND);// you enable blending function
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); 
		glBindTexture( GL_TEXTURE_2D, Globals::surfaceId);
		glBegin( GL_QUADS );
		glNormal3fv((v1 - v0).cross(v3 - v0).direction());
		glTexCoord2d(0.0,0.0+add);
		glVertex3fv(v0);
		glTexCoord2d( 1.0,0.0+add);
		glVertex3fv(v1);
		glTexCoord2d(1.0,0.2+add);
		glVertex3f(vertecies[i+6], vertecies[i+7], vertecies[i+8]);
		glTexCoord2d( 0.0,0.2+add);
		glVertex3fv(v3);
		glEnd();
		glDisable( GL_TEXTURE_2D );
	}
	/*glEnd();
	glDisable(GL_TEXTURE_2D);*/
	glColor(Color3::white());
	if(!children.empty())
	{
		for(size_t i = 0; i < children.size(); i++)
		{
			children.at(i)->render(rd);
		}
	}
	
}

PhysicalInstance::~PhysicalInstance(void)
{
}
char pto[512];
char pto2[512];
#include <sstream>

void PhysicalInstance::PropUpdate(LPPROPGRIDITEM &item)
{
	if(strcmp(item->lpszPropName, "Color3") == 0)
	{
		color = Color3(GetRValue(item->lpCurValue)/255.0F,GetGValue(item->lpCurValue)/255.0F,GetBValue(item->lpCurValue)/255.0F);
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

		if(vect.size() != 3)
		{
			sprintf(pto, "%g, %g, %g", cFrame.translation.x, cFrame.translation.y, cFrame.translation.z, "what");
			LPCSTR str = LPCSTR(pto);
			item->lpCurValue = (LPARAM)str;
			MessageBox(NULL, "NO","NO", MB_OK);
		}
		else
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

		if(vect.size() != 3)
		{
			sprintf(pto, "%g, %g, %g", cFrame.translation.x, cFrame.translation.y, cFrame.translation.z, "what");
			LPCSTR str = LPCSTR(pto);
			item->lpCurValue = (LPARAM)str;
			MessageBox(NULL, "NO","NO", MB_OK);
		}
		else
		{
			Vector3 size(vect.at(0),vect.at(1),vect.at(2));
			setSize(size);
		}
	}

	else Instance::PropUpdate(item);
}

std::vector<PROPGRIDITEM> PhysicalInstance::getProperties()
{
	std::vector<PROPGRIDITEM> properties = Instance::getProperties();
	

	properties.push_back(createPGI(
		"Properties",
		"Color3",
		"The color of the selected part",
		RGB((color.r*255),(color.g*255),(color.b*255)),
		PIT_COLOR
		));
	
	sprintf(pto, "%g, %g, %g", cFrame.translation.x, cFrame.translation.y, cFrame.translation.z);
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
	return properties;
}

