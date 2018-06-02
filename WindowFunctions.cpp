
#include "WindowFunctions.h"

bool createWindowClass(const char* name,WNDPROC proc,HMODULE hInstance)
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
	if (!RegisterClassEx (&wc))
		return false;
	return true;
}

