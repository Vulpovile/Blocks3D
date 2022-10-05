#include "DataModelV2/DataModelInstance.h"
#include "DataModelV2/LevelInstance.h"

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

static Enum::ActionType::Value EnumActionType(TCHAR* option)
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

static TCHAR* strAffectType(int option)
{
	switch(option)
	{
		case Enum::AffectType::NoChange:
			return "NoChange";
		case Enum::AffectType::Increase:
			return "Increase";
		case Enum::AffectType::Decrease:
			return "Decrease";
	}
	return "NoChange";
}

static Enum::AffectType::Value EnumAffectType(TCHAR* option)
{
	if(strcmp("NoChange", option) == 0)
		return Enum::AffectType::NoChange;
	if(strcmp("Increase", option) == 0)
		return Enum::AffectType::Increase;
	return Enum::AffectType::Decrease;
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

	properties.push_back(createPGI(
		"Gameplay",
		"HighScoreIsGood",
		"Some temporary string here",
		(LPARAM)HighScoreIsGood,
		PIT_CHECK
		));

	properties.push_back(createPGI(
		"Gameplay",
		"RunOnOpen",
		"Some temporary string here",
		(LPARAM)RunOnOpen,
		PIT_CHECK
		));

	sprintf_s(timerTxt, "%g", timer);
	sprintf_s(scoreTxt, "%d", score);
	properties.push_back(createPGI("Gameplay",
		"InitialTimerValue",
		"The amount of time in seconds the player has to complete this level.\r\n\r\nPut 0 if time is limitless.",
		(LPARAM)timerTxt,
		PIT_EDIT));

	properties.push_back(createPGI("Gameplay",
		"InitialScoreValue",
		"The amount of points the player starts with.",
		(LPARAM)scoreTxt,
		PIT_EDIT));

		properties.push_back(createPGI("Gameplay",
		"TimerUpAction",
		"Some temporary string here",
		(LPARAM)strActionType(TimerUpAction),
		PIT_COMBO,
		TEXT("Nothing\0Pause\0Lose\0Draw\0Win\0")
		));

		properties.push_back(createPGI("Gameplay",
		"TimerAffectsScore",
		"Some temporary string here",
		(LPARAM)strAffectType(TimerAffectsScore),
		PIT_COMBO,
		TEXT("NoChange\0Increase\0Decrease\0")
		));
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
	else if(strcmp(pItem->lpszPropName, "TimerUpAction") == 0)
	{
		TimerUpAction = EnumActionType((TCHAR*)pItem->lpCurValue);
	}
	else if(strcmp(pItem->lpszPropName, "TimerAffectsScore") == 0)
	{
		TimerAffectsScore = EnumAffectType((TCHAR*)pItem->lpCurValue);
	}
	else if(strcmp(pItem->lpszPropName, "HighScoreIsGood") == 0)
	{
		HighScoreIsGood = pItem->lpCurValue == TRUE;
	}
	else if(strcmp(pItem->lpszPropName, "RunOnOpen") == 0)
	{
		RunOnOpen = pItem->lpCurValue == TRUE;
	}
	else
		Instance::PropUpdate(pItem);
}

void LevelInstance::winCondition()
{
	DataModelInstance* DataModel = (DataModelInstance*)getParent(); //If level parent gets changed to something other than Datamodel it could cause nasty data corruption bugs
	DataModel->setMessage(winMessage);
	DataModel->toggleRun();
}

void LevelInstance::loseCondition()
{
	DataModelInstance* DataModel = (DataModelInstance*)getParent();
	DataModel->setMessage(loseMessage);
	DataModel->toggleRun();
}

void LevelInstance::pauseCondition()
{
	DataModelInstance* DataModel = (DataModelInstance*)getParent();
	DataModel->toggleRun();
}

void LevelInstance::drawCondition()
{
	DataModelInstance* DataModel = (DataModelInstance*)getParent();
	DataModel->toggleRun();
}

void LevelInstance::Step(SimTime sdt)
{
	switch(TimerAffectsScore)
	{
		case Enum::AffectType::NoChange:
			break;
		case Enum::AffectType::Increase:
			score += 1;
			break;
		case Enum::AffectType::Decrease:
			if (score > 0)
				score -= 1;
			break;
	}
	if (timer >= 0.1f){ //Due to timing used this could cause the number go into negatives for one step
		timer -= sdt;
	}
	else{
		timer = 0.0f;
		switch(TimerUpAction)
		{
			case Enum::ActionType::Nothing:
				break;
			case Enum::ActionType::Pause:
				pauseCondition();
				break;
			case Enum::ActionType::Lose:
				loseCondition();
				break;
			case Enum::ActionType::Draw:
				drawCondition();
				break;
			case Enum::ActionType::Win:
				winCondition();
				break;
		}
	}
}