#pragma once
#include "BaseButtonInstance.h"
class TextButtonInstance : public BaseButtonInstance
{
public:
	TextButtonInstance(void);
	~TextButtonInstance(void);
	void setAllColorsSame();
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
	Color4 textColorDis;
	Color4 textOutlineColorDis;
	Color4 boxColorDis;
	Color4 boxOutlineColorDis;
	bool centeredWithinBox;
	std::string title;
	G3D::GFontRef font;
	bool visible;
	int textSize;
	void drawObj(RenderDevice*, Vector2, bool);
	bool mouseInButton(float, float, RenderDevice*);
};