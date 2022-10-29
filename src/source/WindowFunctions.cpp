
#include "WindowFunctions.h"
#include <sstream>

using namespace std;

bool createWindowClass(const char* name, WNDPROC proc, HMODULE hInstance)
{
	WNDCLASSEX wc;
	wc.cbSize        = sizeof(WNDCLASSEX);
	wc.style         = 0;
	wc.lpfnWndProc   = proc;
	wc.cbClsExtra    = 0;
	wc.cbWndExtra    = 0;
	wc.hInstance     = hInstance;
	wc.hIcon         = LoadIcon(NULL, IDI_APPLICATION);
	wc.hCursor       = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW);
	wc.lpszMenuName  = NULL;
	wc.lpszClassName = name;
	wc.hIconSm       = LoadIcon(NULL, IDI_APPLICATION);

	if (!RegisterClassEx(&wc))
	{
		stringstream errMsg;
		errMsg << "Failed to register " << name;
		MessageBox(NULL, errMsg.str().c_str(), "Blocks3D Crash", MB_OK);
		return false;
	}

	return true;
}

