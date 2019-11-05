#pragma once
//#include "Application.h"
#include "BaseButtonInstance.h"
class BaseButtonInstance;

class ButtonListener
{
public:
	ButtonListener();
	~ButtonListener(void);
	virtual void onButton1MouseClick(BaseButtonInstance*);
	//virtual void onMouseOver(); //TODO
	//virtual void onMouseOut(); //TODO
	//virtual void onButton1MouseDown(); //TODO
	//virtual void onButton1MouseUp(); //TODO
	//virtual void onButton2MouseClick(); //TODO
	//virtual void onButton2MouseDown(); //TODO
	//virtual void onButton2MouseUp(); //TODO
	//What to do now...
};
