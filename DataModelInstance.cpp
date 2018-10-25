#include "DataModelInstance.h"





DataModelInstance::DataModelInstance(void)
{
	Instance::Instance();
	workspace = new WorkspaceInstance();
	guiRoot = new Instance();
	level = new LevelInstance();
	//children.push_back(workspace);
	//children.push_back(level);
	className = "dataModel";
	mousex = 0;
	mousey = 0;
	mouseButton1Down = false;
	showMessage = false;
	canDelete = false;

	workspace->setParent(this);
	level->setParent(this);
	
}

DataModelInstance::~DataModelInstance(void)
{
}

void DataModelInstance::setMessage(std::string msg)
{
	message = msg;
	isBrickCount = false;
	showMessage = true;
}

void DataModelInstance::clearMessage()
{
	showMessage = false;
	isBrickCount = false;
	message = "";
}

void DataModelInstance::setMessageBrickCount()
{
	isBrickCount = true;
	showMessage = true;
}

void DataModelInstance::drawMessage(RenderDevice* rd)
{
	if(isBrickCount)
	{
		int brickCount = 0;
		int instCount = 0;
		std::vector<Instance*> inst = getAllChildren();
		for(size_t i = 0; i < inst.size(); i++)
		{
			if(PartInstance* moveTo = dynamic_cast<PartInstance*>(inst.at(i)))
			{
				brickCount++;
			}
			else
			{
				instCount++;
			}
		}
		char brkc[12];
		sprintf(brkc, "%d", brickCount);
		char instc[12];
		sprintf(instc, "%d", instCount);
		message = "Bricks: ";
		message += brkc;
		message += "	Snaps: ";
		message += instc;
	}
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


LevelInstance* DataModelInstance::getLevel()
{
	return level;
}