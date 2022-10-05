#pragma once
#include "instance.h"

class LevelInstance :
	public Instance
{
public:
	LevelInstance(void);
	~LevelInstance(void);
	bool HighScoreIsGood;
	Enum::ActionType::Value TimerUpAction;
	Enum::AffectType::Value TimerAffectsScore;
	bool RunOnOpen;
	float timer;
	int score;
	virtual std::vector<PROPGRIDITEM> getProperties();
	std::string winMessage;
	std::string loseMessage;
	virtual void PropUpdate(LPPROPGRIDITEM &pItem);
	void Step(SimTime sdt);
};
