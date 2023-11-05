#pragma once
#include "Instance.h"
#include "Enum.h"
namespace B3D{
class LevelInstance : public Instance
{
	public:
		//Constructors
		LevelInstance(void);
		~LevelInstance(void);

		//Functions
		void winCondition();
		void loseCondition();
		void pauseCondition();
		void drawCondition();
		void Step(SimTime sdt);

		//Values
		Reflection::ReflectionProperty<bool> highScoreIsGood;
		Reflection::ReflectionProperty<Enum::ActionType::Value> timerUpAction;
		Reflection::ReflectionProperty<Enum::AffectType::Value> timerAffectsScore;
		Reflection::ReflectionProperty<bool> runOnOpen;
		Reflection::ReflectionProperty<float> timer;
		Reflection::ReflectionProperty<int> score;
		Reflection::ReflectionProperty<std::string> winMessage;
		Reflection::ReflectionProperty<std::string> loseMessage;
	};
}