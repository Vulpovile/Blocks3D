#include "DataModelV3/SelectionService.h"
#include "DataModelV3/PartInstance.h"

//This is absolutely disgusting, and will not last long
//#include "Application.h"
//#include "Globals.h"
#define CURSOR 0
#define ARROWS 1
#define RESIZE 2

using namespace B3D;

SelectionService::SelectionService(void) : Instance(){
	mode = CURSOR;
	// TODO Port PropertyWindow
	//propertyWindow = NULL;
}

SelectionService::~SelectionService(void){
}

SelectionService::SelectionService(const SelectionService &oinst){
	Instance::Instance(oinst);
	// TODO Port PropertyWindow
	//propertyWindow = NULL;
}


std::vector<Instance *> SelectionService::getSelection(){
	return this->selection;
}
void SelectionService::clearSelection(){
	this->selection.clear();
	// TODO Port PropertyWindow
	/*if(propertyWindow != NULL)
		propertyWindow->ClearProperties();*/
}
bool SelectionService::isSelected(Instance * instance){
	return std::find(selection.begin(), selection.end(), instance) != selection.end();
}
void SelectionService::addSelected(Instance * instance){
	if(!isSelected(instance))
		this->selection.push_back(instance);
	// TODO Port PropertyWindow
	/*if(propertyWindow != NULL)
		propertyWindow->UpdateSelected(selection);*/
}
void SelectionService::removeSelected(Instance * instance){
	selection.erase(std::remove(selection.begin(), selection.end(), instance), selection.end());
	// TODO Port PropertyWindow
	/*if(propertyWindow != NULL)
		propertyWindow->UpdateSelected(selection);*/
}
void SelectionService::addSelected(const std::vector<Instance *> &instances){
	for(size_t i = 0; i < instances.size(); i++)
	{
		if(!isSelected(instances[i]))
			this->selection.push_back(instances[i]);
	}
	// TODO Port PropertyWindow
	/*if(propertyWindow != NULL)
		propertyWindow->UpdateSelected(selection);*/
}

// TODO Port PropertyWindow
/*void SelectionService::setPropertyWindow(PropertyWindow * propertyWindow)
{
	this->propertyWindow = propertyWindow;
	if(propertyWindow != NULL)
		propertyWindow->ClearProperties();
}*/


void SelectionService::render(RenderDevice * rd)
{
	for(size_t i = 0; i < selection.size(); i++)
	{
		if(PartInstance* part = dynamic_cast<PartInstance*>(selection[i]))
		{
			Vector3 size = part->getSize();
			Vector3 pos = part->getPosition();
			drawOutline(Vector3(0+size.x/2, 0+size.y/2, 0+size.z/2) ,Vector3(0-size.x/2,0-size.y/2,0-size.z/2), rd, Vector3(size.x/2, size.y/2, size.z/2), Vector3(pos.x, pos.y, pos.z), part->getCFrame());
		}		
	}
}



void SelectionService::drawOutline(Vector3 from, Vector3 to, RenderDevice* rd, Vector3 size, Vector3 pos, CoordinateFrame c)
{
	Color3 outline = Color3::cyan();//Color3(0.098F,0.6F,1.0F);
	float offsetSize = 0.1F;
	//X
	Draw::box(c.toWorldSpace(Box(Vector3(from.x - offsetSize, from.y + offsetSize, from.z + offsetSize), Vector3(to.x + offsetSize, from.y - offsetSize, from.z - offsetSize))), rd, outline, Color4::clear()); 
	Draw::box(c.toWorldSpace(Box(Vector3(from.x - offsetSize, to.y + offsetSize, from.z + offsetSize), Vector3(to.x + offsetSize, to.y - offsetSize, from.z - offsetSize))), rd, outline, Color4::clear()); 
	Draw::box(c.toWorldSpace(Box(Vector3(from.x - offsetSize, to.y + offsetSize, to.z + offsetSize), Vector3(to.x + offsetSize, to.y - offsetSize, to.z - offsetSize))), rd, outline, Color4::clear()); 
	Draw::box(c.toWorldSpace(Box(Vector3(from.x - offsetSize, from.y + offsetSize, to.z + offsetSize), Vector3(to.x + offsetSize, from.y - offsetSize, to.z - offsetSize))), rd, outline, Color4::clear()); 
	//Y
	Draw::box(c.toWorldSpace(Box(Vector3(from.x + offsetSize, from.y - offsetSize + 0.2, from.z + offsetSize), Vector3(from.x - offsetSize, to.y + offsetSize - 0.2, from.z - offsetSize))), rd, outline, Color4::clear()); 
	Draw::box(c.toWorldSpace(Box(Vector3(to.x + offsetSize, from.y - offsetSize + 0.2, from.z + offsetSize), Vector3(to.x - offsetSize, to.y + offsetSize - 0.2, from.z - offsetSize))), rd, outline, Color4::clear()); 
	Draw::box(c.toWorldSpace(Box(Vector3(to.x + offsetSize, from.y - offsetSize + 0.2, to.z + offsetSize), Vector3(to.x - offsetSize, to.y + offsetSize-0.2, to.z - offsetSize))), rd, outline, Color4::clear()); 
	Draw::box(c.toWorldSpace(Box(Vector3(from.x + offsetSize, from.y - offsetSize + 0.2, to.z + offsetSize), Vector3(from.x - offsetSize, to.y + offsetSize - 0.2, to.z - offsetSize))), rd, outline, Color4::clear()); 

	//Z
	Draw::box(c.toWorldSpace(Box(Vector3(from.x + offsetSize, from.y + offsetSize, from.z - offsetSize), Vector3(from.x - offsetSize, from.y - offsetSize, to.z + offsetSize))), rd, outline, Color4::clear()); 
	Draw::box(c.toWorldSpace(Box(Vector3(from.x + offsetSize, to.y + offsetSize, from.z - offsetSize), Vector3(from.x - offsetSize, to.y - offsetSize, to.z + offsetSize))), rd, outline, Color4::clear()); 
	Draw::box(c.toWorldSpace(Box(Vector3(to.x + offsetSize, from.y + offsetSize, from.z - offsetSize), Vector3(to.x - offsetSize, from.y - offsetSize, to.z + offsetSize))), rd, outline, Color4::clear()); 
	Draw::box(c.toWorldSpace(Box(Vector3(to.x + offsetSize, to.y + offsetSize, from.z - offsetSize), Vector3(to.x - offsetSize, to.y - offsetSize, to.z + offsetSize))), rd, outline, Color4::clear()); 
	
	if(mode == ARROWS)
	{
		
		AABox box;
		c.toWorldSpace(Box(from, to)).getBounds(box);
		float max = box.high().y - pos.y;

		Draw::arrow(pos, Vector3(0, 1.5+max, 0), rd);
		Draw::arrow(pos, Vector3(0, (-1.5)-max, 0), rd);
		
		max = box.high().x - pos.x;

		Draw::arrow(pos, Vector3(1.5+max, 0, 0), rd);
		Draw::arrow(pos, Vector3((-1.5)-max, 0, 0), rd);

		max = box.high().z - pos.z;

		Draw::arrow(pos, Vector3(0, 0, 1.5+max), rd);
		Draw::arrow(pos, Vector3(0, 0, (-1.5)-max), rd);



	}
	else if(mode == RESIZE)
	{
		Color3 sphereColor = outline;
		Vector3 gamepoint = pos;
		Vector3 camerapoint = rd->getCameraToWorldMatrix().translation;
		float distance = pow(pow((double)gamepoint.x - (double)camerapoint.x, 2) + pow((double)gamepoint.y - (double)camerapoint.y, 2) + pow((double)gamepoint.z - (double)camerapoint.z, 2), 0.5);
		if(distance < 200)
		{
			
			float multiplier = distance * 0.050F/2;
			if(multiplier < 0.50F)
				multiplier = 0.50F;
			Vector3 position = pos + (c.lookVector()*((size.z)+2));
			Draw::sphere(Sphere(position, multiplier), rd, sphereColor, Color4::clear());
			position = pos - (c.lookVector()*((size.z)+2));
			Draw::sphere(Sphere(position, multiplier), rd, sphereColor, Color4::clear());

			position = pos + (c.rightVector()*((size.x)+2));
			Draw::sphere(Sphere(position, multiplier), rd, sphereColor, Color4::clear());
			position = pos - (c.rightVector()*((size.x)+2));
			Draw::sphere(Sphere(position, multiplier), rd, sphereColor, Color4::clear());

			position = pos + (c.upVector()*((size.y)+2));
			Draw::sphere(Sphere(position, multiplier), rd, sphereColor, Color4::clear());
			position = pos - (c.upVector()*((size.y)+2));
			Draw::sphere(Sphere(position, multiplier), rd, sphereColor, Color4::clear());
		}
	}
}

