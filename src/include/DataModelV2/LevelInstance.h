#pragma once
#include "instance.h"

class LevelInstance :
	public Instance
{
public:
	std::string SplashHTML;
	LevelInstance(void);
	~LevelInstance(void);
	float timer;
	int score;
	virtual std::vector<PROPGRIDITEM> getProperties();
	std::string winMessage;
	std::string loseMessage;
	virtual void PropUpdate(LPPROPGRIDITEM &pItem);
};
