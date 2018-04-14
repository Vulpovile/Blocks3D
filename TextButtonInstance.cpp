#include "TextButtonInstance.h"
Vector2 boxBegin;
Vector2 boxEnd;
Vector2 fontLocationRelativeTo;
Color4 textColor;
Color4 textOutlineColor;
Color4 boxColor;
Color4 boxOutlineColor;
Color4 textColorOvr;
Color4 textOutlineColorOvr;
Color4 boxColorOvr;
Color4 boxOutlineColorOvr;
Color4 textColorDn;
Color4 textOutlineColorDn;
Color4 boxColorDn;
Color4 boxOutlineColorDn;
bool centeredWithinBox;
std::string title;
G3D::GFontRef* font;
int textSize;
bool floatBottom;
bool floatRight;
bool visible;

TextButtonInstance::TextButtonInstance(void)
{
	boxBegin = Vector2(0,0);
	boxEnd = Vector2(0,0);
	fontLocationRelativeTo = Vector2(0,0);
	centeredWithinBox = false;
	title = "TextBox";
	textColor = Color4(1, 1, 1, 1);
	textOutlineColor = Color4(0, 0, 0, 0);
	boxColor = Color4(0.6F,0.6F,0.6F,0.4F);
	boxOutlineColor = Color4(0, 0, 0, 0);
	textSize = 12;
	floatBottom = false;
	floatRight = false;
	visible = true;
	
}

TextButtonInstance::~TextButtonInstance(void)
{
}
