#include "Tool/Tool.h"

Tool::Tool(void)
{
	cursorString = GetFileInPath("/content/images/ArrowFarCursor.png");
	//cursorId = cursorRef->openGLID();
}

Tool::~Tool(void)
{
}

void Tool::onButton1MouseDown(Mouse mouse){}
void Tool::onButton2MouseDown(Mouse mouse){}	
void Tool::onButton3MouseDown(Mouse mouse){}	
void Tool::onButton1MouseUp(Mouse mouse){}
void Tool::onButton2MouseUp(Mouse mouse){}
void Tool::onButton3MouseUp(Mouse mouse){}
void Tool::onMouseMoved(Mouse mouse){}
void Tool::onSelect(Mouse mouse){}
void Tool::onDeselect(Mouse mouse){}
void Tool::onMouseScroll(Mouse mouse){}
void Tool::onKeyDown(int key){}
void Tool::onKeyUp(int key){}
void Tool::setCursor(std::string str)
{
	cursorString = str;
}
int Tool::getCursorId()
{
	return TextureHandler::getTexturePermanent(cursorString);
}