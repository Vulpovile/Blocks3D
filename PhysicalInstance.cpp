#include "PhysicalInstance.h"
bool canCollide = true;
bool anchored = false;
Vector3 size;
Vector3 position;
Vector3 velocity;
Vector3 rotVelocity;
GLfloat vertecies[96];
CoordinateFrame cFrame;
Color3 color;
bool changed = true;
Box itemBox = Box();


PhysicalInstance::PhysicalInstance(void)
{
	name = "Default PhysicalInstance";
	className = "Part";
	canCollide = true;
	anchored = true;
	size = Vector3(2,1,4);
	position = Vector3(0,0,0);
	cFrame = CoordinateFrame(position);
	color = Color3::gray();
	velocity = Vector3(0,0,0);
	rotVelocity = Vector3(0,0,0);
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

void PhysicalInstance::render(RenderDevice* rd)
{
	if(changed)
	Box box = getBox();
	glColor(color);
	glBegin(GL_QUADS);
    for(int i = 0; i < 96; i+=16)
	{
		Vector3 v0 = Vector3(vertecies[i], vertecies[i+1], vertecies[i+2]), v1 = Vector3(vertecies[i+3], vertecies[i+4], vertecies[i+5]), v3 = Vector3(vertecies[i+9], vertecies[i+10], vertecies[i+11]);
		glNormal3fv((v1 - v0).cross(v3 - v0).direction());
		glVertex3fv(v0);
		glVertex3fv(v1);
		glVertex3f(vertecies[i+6], vertecies[i+7], vertecies[i+8]);
		glVertex3fv(v3);
	}
	glEnd();
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




