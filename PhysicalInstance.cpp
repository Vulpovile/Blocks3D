#include "PhysicalInstance.h"
bool canCollide = true;
bool anchored = false;
Vector3 size;
Vector3 position;
Vector3 velocity;
Vector3 rotVelocity;
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
	}
	return itemBox;
}

void PhysicalInstance::render(RenderDevice* rd)
{
	Draw::box(getBox(), rd, color, Color4::clear());
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




