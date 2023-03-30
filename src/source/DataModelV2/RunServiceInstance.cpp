#include "DataModelV2/RunServiceInstance.h"
#include "DataModelV2/ToggleImageButtonInstance.h"
#include "Globals.h"

RunService::RunService()
{
	// Run Service, not RunService, because Roblox themselves did it. Why? IDK!
	name = "Run Service";
	className = "RunService";
	canDelete = false;
}

RunService::~RunService(void)
{
}

void RunService::run()
{
	// Tell GUI that we are running
	Instance* go = g_dataModel->getGuiRoot()->findFirstChild("go");
	g_dataModel->toggleRun(true);
	((ToggleImageButtonInstance*)go)->checked = true;
}

void RunService::pause()
{
	// Tell GUI that we paused
	Instance* go = g_dataModel->getGuiRoot()->findFirstChild("go");
	g_dataModel->toggleRun(false);
	((ToggleImageButtonInstance*)go)->checked = false;
}

void RunService::reset()
{
	// Can't really implement right now
}
