#pragma once
#include <G3DAll.h>
#pragma once
#include "Mouse.h"
#pragma once
#include "Globals.h"
#pragma once
#include "StringFunctions.h"
#pragma once
class Tool
{
public:
	Tool(void);
	~Tool(void);
	void onButton1MouseDown(Mouse); //yes
	void onButton2MouseDown(Mouse);	//yes
	void onButton3MouseDown(Mouse);	
	void onButton1MouseUp(Mouse);//yes
	void onButton2MouseUp(Mouse);//yes
	void onButton3MouseUp(Mouse);
	void onMouseMoved(Mouse);//yes
	void onSelect(Mouse);//For later
	void onDeselect(Mouse);//For later
	void onMouseScroll(Mouse);//Kinda
	void onKeyDown(char);//yes
	void onKeyUp(char);//yes
	void setCursor(std::string);
	void setCursorId(int);//yes
	int getCursorId();//yes
private:
	int cursorId;
	G3D::TextureRef cursorRef;
	std::string cursorString;
};
