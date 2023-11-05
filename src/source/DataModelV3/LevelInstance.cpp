//#include "DataModelV3/DataModelInstance.h"
#include "DataModelV3/LevelInstance.h"
using namespace B3D;

LevelInstance::LevelInstance(void)
{
	Instance::Instance("LevelService");
	*name.value = "Level";
	
	//Reflection values
	winMessage = Reflection::ReflectionProperty<std::string>("WinMessage", "You Won!", TYPE_STRING, this->dataTable);
	loseMessage = Reflection::ReflectionProperty<std::string>("LoseMessage", "You Lost. Try Again", TYPE_STRING, this->dataTable);
	timer = Reflection::ReflectionProperty<float>("InitialTimerValue", 60.0F, TYPE_FLOAT, this->dataTable);
	score = Reflection::ReflectionProperty<int>("InitialScoreValue", 0, TYPE_INT, this->dataTable);
	highScoreIsGood = Reflection::ReflectionProperty<bool>("HighScoreIsGood", false, TYPE_BOOLEAN, this->dataTable);
	runOnOpen = Reflection::ReflectionProperty<bool>("RunOnOpen", false, TYPE_BOOLEAN, this->dataTable);
	timerUpAction = Reflection::ReflectionProperty<Enum::ActionType::Value>("TimerUpAction", Enum::ActionType::Nothing, TYPE_ENUM, this->dataTable, 
		new EnumMeta(Enum::ActionType::LENGTH, Enum::ActionType::STR_TABLE));
	timerAffectsScore = Reflection::ReflectionProperty<Enum::AffectType::Value>("TimerAffectsScore", Enum::AffectType::NoChange, TYPE_ENUM, this->dataTable, 
		new EnumMeta(Enum::AffectType::LENGTH, Enum::AffectType::STR_TABLE));

	canDelete = false;
}

LevelInstance::~LevelInstance(void)
{
}

void LevelInstance::winCondition()
{
	//DataModelInstance* DataModel = (DataModelInstance*)getParent(); //If level parent gets changed to something other than Datamodel it could cause nasty data corruption bugs
	//DataModel->setMessage(winMessage);
	//DataModel->toggleRun();
}

void LevelInstance::loseCondition()
{
	//DataModelInstance* DataModel = (DataModelInstance*)getParent();
	//DataModel->setMessage(loseMessage);
	//DataModel->toggleRun();
}

void LevelInstance::pauseCondition()
{
	//DataModelInstance* DataModel = (DataModelInstance*)getParent();
	//DataModel->toggleRun();
}

void LevelInstance::drawCondition()
{
	//DataModelInstance* DataModel = (DataModelInstance*)getParent();
	//DataModel->toggleRun();
}

void LevelInstance::Step(SimTime sdt)
{
	switch(*timerAffectsScore.value)
	{
		case Enum::AffectType::NoChange:
			break;
		case Enum::AffectType::Increase:
			*score.value += 1;
			break;
		case Enum::AffectType::Decrease:
			if (*score.value > 0)
				*score.value -= 1;
			break;
	}
	if (*timer.value >= sdt){
		*score.value -= sdt;
	}
	else{
		*timer.value = 0.0f;
		switch(*timerUpAction.value)
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