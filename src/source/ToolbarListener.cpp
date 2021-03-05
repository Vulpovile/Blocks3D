#include "ToolbarListener.h"
#include "Globals.h"
#include "StringFunctions.h"
#include "Application.h"

void ToolbarListener::onButton1MouseClick(BaseButtonInstance* btn)
{
	if(TextButtonInstance* button = dynamic_cast<TextButtonInstance*>(btn))
	{
	for(size_t i = 0; i < btns.size(); i++)
		btns[i]->selected = false;
		button->selected = true;
		if(button->title == "Model") g_usableApp->navigateToolbox("http://androdome.com/res/ClientToolbox.php");
		else if(button->title == "Surface") g_usableApp->navigateToolbox(GetFileInPath("/content/page/surface.html"));
		else if(button->title == "Color") g_usableApp->navigateToolbox(GetFileInPath("/content/page/color.html"));
		else if(button->title == "Controller") g_usableApp->navigateToolbox(GetFileInPath("/content/page/controller.html"));
		else if(button->title == "Hopper") g_usableApp->navigateToolbox(GetFileInPath("/content/page/hopper.html"));
	}
}
void ToolbarListener::addButtonRef(BaseButtonInstance* button)
{
	btns.push_back(button);
}