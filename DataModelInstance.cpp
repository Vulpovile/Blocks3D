#include "DataModelInstance.h"





DataModelInstance::DataModelInstance(void)
{
	Instance::Instance();
	workspace = new WorkspaceInstance();
	guiRoot = new Instance();
	children.push_back(workspace);
	className = "dataModel";
	mousex = 0;
	mousey = 0;
	mouseButton1Down = false;
	showMessage = false;
	canDelete = false;
	winMessage = "You Won!";
	loseMessage = "You Lost. Try Again";
	timer = 60.0F;
	score = 0;
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

char timerTxt[12];
char scoreTxt[12];
std::vector<PROPGRIDITEM> DataModelInstance::getProperties()
{
	std::vector<PROPGRIDITEM> properties = Instance::getProperties();



	properties.push_back(createPGI("Messages",
		"WinMessage",
		"The message that shows when the player wins.",
		(LPARAM)winMessage.c_str(),
		PIT_EDIT));
	properties.push_back(createPGI("Messages",
		"LoseMessage",
		"The message that shows when the player loses.",
		(LPARAM)loseMessage.c_str(),
		PIT_EDIT));


	sprintf(timerTxt, "%g", timer);
	sprintf(scoreTxt, "%d", score);
	properties.push_back(createPGI("Gameplay",
		"InitialTimerValue",
		"The ammount of time in seconds the player has to complete this level.\r\n\r\nPut 0 if time is limitless.",
		(LPARAM)timerTxt,
		PIT_EDIT));
	properties.push_back(createPGI("Gameplay",
		"InitialScoreValue",
		"The ammount of points the player starts with.",
		(LPARAM)scoreTxt,
		PIT_EDIT));
	return properties;
}
void DataModelInstance::PropUpdate(LPPROPGRIDITEM &pItem)
{
	if(strcmp(pItem->lpszPropName, "InitialTimerValue") == 0)
	{
		timer = atoi((LPSTR)pItem->lpCurValue);
	}
	if(strcmp(pItem->lpszPropName, "InitialScoreValue") == 0)
	{
		score = atof((LPSTR)pItem->lpCurValue);
	}
	if(strcmp(pItem->lpszPropName, "LoseMessage") == 0)
	{
		loseMessage = (LPSTR)pItem->lpCurValue;
	}
	if(strcmp(pItem->lpszPropName, "WinMessage") == 0)
	{
		winMessage = (LPSTR)pItem->lpCurValue;
	}
	else
		Instance::PropUpdate(pItem);
}