#pragma once
#include "TextButtonInstance.h"
class TextButtonInstance;
class ButtonListener
{
public:
	ButtonListener(void);
	~ButtonListener(void);
	virtual void onButton1MouseClick(TextButtonInstance*);
	//virtual void onMouseOver(); //TODO
	//virtual void onMouseOut(); //TODO
	//virtual void onButton1MouseDown(); //TODO
	//virtual void onButton1MouseUp(); //TODO
	//virtual void onButton2MouseClick(); //TODO
	//virtual void onButton2MouseDown(); //TODO
	//virtual void onButton2MouseUp(); //TODO
	//What to do now...
};
