#pragma once
#include "buttonlistener.h"
#pragma once
#include <G3DAll.h>

class ToolbarListener : public ButtonListener
{
public:
	void onButton1MouseClick(BaseButtonInstance* button);
	void addButtonRef(BaseButtonInstance* button);
private:
	std::vector<BaseButtonInstance*> btns;
};
