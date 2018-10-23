#include "DataModelInstance.h"





DataModelInstance::DataModelInstance(void)
{
	workspace = new WorkspaceInstance();
	guiRoot = new Instance();
	children.push_back(workspace);
	className = "dataModel";
	mousex = 0;
	mousey = 0;
	mouseButton1Down = false;
	showMessage = false;
	initProperties();
}

DataModelInstance::~DataModelInstance(void)
{
}

void DataModelInstance::setMessage(std::string msg)
{
	message = msg;
	showMessage = true;
}

void DataModelInstance::clearMessage()
{
	showMessage = false;
	message = "";
}

void DataModelInstance::drawMessage(RenderDevice* rd)
{
	if(showMessage && !font.isNull())
	{
		int x = rd->getWidth()/2;
		int y = rd->getHeight()/2;
		int width = rd->getWidth()/2 + 100;
		int height = width / 3;
		Draw::box(Box(Vector3(x-(width/2), y-(height/2), 0), Vector3(x+(width/2), y+(height/2), 0)), rd, Color4::fromARGB(0x55B2B2B2), Color3::fromARGB(0xB2B2B2));
		font->draw2D(rd, message, Vector2(x,y), height/8, Color3::white(), Color4::clear(), GFont::XALIGN_CENTER, GFont::YALIGN_CENTER);
	}
}

WorkspaceInstance* DataModelInstance::getWorkspace()
{
	return workspace;
}
Vector2 DataModelInstance::getMousePos()
{
	return Vector2(mousex,mousey);
}
void DataModelInstance::setMousePos(int x,int y)
{
	mousex=x;
	mousey=y;
}
void DataModelInstance::setMousePos(Vector2 pos)
{
	mousex=pos.x;
	mousey=pos.y;
}
Instance* DataModelInstance::getGuiRoot()
{
	return guiRoot;
}
