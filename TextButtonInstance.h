#pragma once
#include "instance.h"

class TextButtonInstance :
	public Instance
{
public:
	TextButtonInstance(void);
	~TextButtonInstance(void);
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
	G3D::GFontRef font;
};
