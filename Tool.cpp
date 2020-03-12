#include "Tool.h"

Tool::Tool(void)
{
	cursorRef = Texture::fromFile(GetFileInPath("/content/images/ArrowCursor.png"));
	cursorId = cursorRef->openGLID();
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
void Tool::onKeyDown(char key){}
void Tool::onKeyUp(char key){}
void Tool::setCursor(std::string)
{
}
int Tool::getCursorId()
{
	return cursorId;
}
void Tool::setCursorId(int id)
{
	cursorId = id;
}