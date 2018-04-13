#include "TextButtonInstance.h"
Vector2 boxBegin;
Vector2 boxEnd;
Vector2 fontLocationRelativeTo;
Color4 textColor;
Color4 textOutlineColor;
Color4 boxColor;
Color4 boxOutlineColor;
bool centeredWithinBox;
std::string title;
G3D::GFontRef font;


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
}

TextButtonInstance::~TextButtonInstance(void)
{
}
