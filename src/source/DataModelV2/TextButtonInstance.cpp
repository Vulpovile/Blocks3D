#include "DataModelV2/TextButtonInstance.h"


TextButtonInstance::TextButtonInstance(void)
{
	BaseButtonInstance::BaseButtonInstance();
	boxBegin = Vector2(0,0);
	boxEnd = Vector2(0,0);
	fontLocationRelativeTo = Vector2(0,0);
	centeredWithinBox = false;
	title = "TextBox";
	textColor = Color4(1, 1, 1, 1);
	textOutlineColor = Color4(0, 0, 0, 0);
	boxColor = Color4(0.6F,0.6F,0.6F,0.4F);
	boxOutlineColor = Color4(0, 0, 0, 0);
	setAllColorsSame();
	textSize = 12;
	floatBottom = false;
	floatRight = false;
	floatCenter = false;
	visible = true;
	className = "TextButton";
	disabled = false;
	selected = false;
}

bool TextButtonInstance::mouseInButton(float mousex, float mousey, RenderDevice* rd)
{
	Vector3 point1;
	Vector3 point2;
	if(floatBottom)
	{
		point1 = Vector3(boxBegin.x, rd->getHeight() + boxBegin.y,0);
		point2 = Vector3(boxEnd.x, rd->getHeight() + boxEnd.y,0);
		
	}
	else
	{
		point1 = Vector3(boxBegin.x, boxBegin.y,0);
		point2 = Vector3(boxEnd.x, boxEnd.y,0);
	}
	if(mousex >= point1.x && mousey >= point1.y)
	{
		if(mousex < point2.x && mousey < point2.y)
		{
			return true;
		}
	}
	return false;
}

void TextButtonInstance::setAllColorsSame()
{
	textColorOvr = textColor;
	textOutlineColorOvr = textOutlineColor;
	boxColorOvr = boxColor;
	boxOutlineColorOvr = boxOutlineColor;
	textColorDn = textColor;
	textOutlineColorDn = textOutlineColor;
	boxColorDn = boxColor;
	boxOutlineColorDn = boxOutlineColor;
	textColorDis = textColor;
	textOutlineColorDis = textOutlineColor;
	boxColorDis = boxColor;
	boxOutlineColorDis = boxOutlineColor;
}

TextButtonInstance::~TextButtonInstance(void)
{
}

void TextButtonInstance::drawObj(RenderDevice* rd, Vector2 mousePos, bool mouseDown)
{
	Vector3 point1;
	Vector3 point2;
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glDisableClientState(GL_COLOR_ARRAY);
	
	if(floatBottom)
	{
		point1 = Vector3(boxBegin.x, rd->getHeight() + boxBegin.y,0);
		point2 = Vector3(boxEnd.x, rd->getHeight() + boxEnd.y,0);
		
	}
	else
	{
		point1 = Vector3(boxBegin.x, boxBegin.y,0);
		point2 = Vector3(boxEnd.x, boxEnd.y,0);
	}
	Vector2 RelativeTo = Vector2(point1.x + fontLocationRelativeTo.x, point1.y + fontLocationRelativeTo.y);
	if(disabled)
	{
		Draw::box(Box(point1, point2), rd, boxColorDis, boxOutlineColorDis);
		font->draw2D(rd, title, RelativeTo, textSize, textColorDis, textOutlineColorDis);
	}
	else if(mouseInArea(point1.x, point1.y, point2.x, point2.y, mousePos.x, mousePos.y) && mouseDown)
	{
		Draw::box(Box(point1, point2), rd, boxColorDn, boxOutlineColorDn);
		font->draw2D(rd, title, RelativeTo, textSize, textColorDn, textOutlineColorDn);
	}
	else if(selected || mouseInArea(point1.x, point1.y, point2.x, point2.y, mousePos.x, mousePos.y))
	{
		Draw::box(Box(point1, point2), rd, boxColorOvr, boxOutlineColorOvr);
		font->draw2D(rd, title, RelativeTo, textSize, textColorOvr, textOutlineColorOvr);
	}
	else
	{
		Draw::box(Box(point1, point2), rd, boxColor, boxOutlineColor);
		font->draw2D(rd, title, RelativeTo, textSize, textColor, textOutlineColor);
	}
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	glEnableClientState(GL_COLOR_ARRAY);
}

void doNullCheck()
{
}