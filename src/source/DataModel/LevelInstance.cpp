#include "DataModel/LevelInstance.h"

LevelInstance::LevelInstance(void)
{
	Instance::Instance();
	name = "Level";
	winMessage = "You Won!";
	loseMessage = "You Lost. Try Again";
	timer = 60.0F;
	score = 0;
	canDelete = false;
}

LevelInstance::~LevelInstance(void)
{
}


char timerTxt[12];
char scoreTxt[12];
std::vector<PROPGRIDITEM> LevelInstance::getProperties()
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


	sprintf_s(timerTxt, "%g", timer);
	sprintf_s(scoreTxt, "%d", score);
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
void LevelInstance::PropUpdate(LPPROPGRIDITEM &pItem)
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