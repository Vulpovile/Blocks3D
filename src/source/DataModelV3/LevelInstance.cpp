#include "DataModelV3/DataModelInstance.h"
#include "DataModelV3/LevelInstance.h"
using namespace B3D;

LevelInstance::LevelInstance(void) : Instance("LevelService")
{
	name = "Level";
	
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
	DataModelInstance* DataModel = parentDataModel; //If level parent gets changed to something other than Datamodel it could cause nasty data corruption bugs
	DataModel->setMessage(winMessage.getValue());
	DataModel->toggleRun();
}

void LevelInstance::loseCondition()
{
	DataModelInstance* DataModel = parentDataModel;
	DataModel->setMessage(loseMessage.getValue());
	DataModel->toggleRun();
}

void LevelInstance::pauseCondition()
{
	DataModelInstance* DataModel = parentDataModel;
	DataModel->toggleRun();
}

void LevelInstance::drawCondition()
{
	DataModelInstance* DataModel = parentDataModel;
	DataModel->toggleRun();
}

void LevelInstance::Step(SimTime sdt)
{
	switch(timerAffectsScore.getValue())
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
	if (timer >= sdt){
		score -= sdt;
	}
	else{
		timer = 0.0f;
		switch(timerUpAction.getValue())
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