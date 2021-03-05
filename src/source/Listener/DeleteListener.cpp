#include "Listener/DeleteListener.h"
#include "Globals.h"
#include "Application.h"

void DeleteListener::onButton1MouseClick(BaseButtonInstance* button)
{
	g_usableApp->deleteInstance();
}