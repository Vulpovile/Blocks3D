#include "BaseButtonInstance.h"
#include "Listener/ButtonListener.h"


ButtonListener::ButtonListener()
{
	doDelete = true;
}

ButtonListener::~ButtonListener(void)
{
}

void ButtonListener::onButton1MouseClick(BaseButtonInstance* button)
{
}

