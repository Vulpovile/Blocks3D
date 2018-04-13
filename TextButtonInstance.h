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
	bool centeredWithinBox;
	std::string title;
};
