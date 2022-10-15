#pragma once
#include "TextureHandler.h"
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
	virtual void onButton1MouseDown(Mouse); //yes
	virtual void onButton2MouseDown(Mouse);	//yes
	virtual void onButton3MouseDown(Mouse);	//no
	virtual void onButton1MouseUp(Mouse);//yes
	virtual void onButton2MouseUp(Mouse);//yes
	virtual void onButton3MouseUp(Mouse); //no
	virtual void onMouseMoved(Mouse);//yes
	virtual void onSelect(Mouse);//yes
	virtual void onDeselect(Mouse);//yes
	virtual void onMouseScroll(Mouse);//Kinda
	virtual void onKeyDown(int);//yes
	virtual void onKeyUp(int);//yes
	virtual void render(RenderDevice * rd, Mouse mouse);//yes
	//virtual int getCursorId();//yes
protected:
	//virtual void setCursor(std::string);
private:
	//std::string cursorString;
};
