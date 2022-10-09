#include <sstream>
#include "ErrorFunctions.h"
#include "Globals.h"



void OnError(int err, std::string msg)
{
	std::string emsg = "An unexpected error has occured and "+g_appName+" has to quit. We're sorry!" + msg;
	std::string title = g_appName+" Crash";
	MessageBox(NULL, emsg.c_str(), title.c_str(), MB_OK);
	exit(err);
}


void MessageBoxStr(std::string msg)
{
	std::string title = g_appName;
	MessageBox(NULL, msg.c_str(), title.c_str(), MB_OK);
}

void MessageBoxStream(std::stringstream msg)
{
	std::string strMsg = msg.str();
	std::string title = g_appName;
	MessageBox(NULL, strMsg.c_str(), title.c_str(), MB_OK);
}