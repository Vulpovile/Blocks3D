#pragma once
#include "Instance.h"
class PropertyWindow {
public:
	PropertyWindow(int x, int y, int sx, int sy, HMODULE hThisInstance);
	bool	onCreate(int x, int y, int sx, int sy, HMODULE hThisInstance);
	void	SetProperties(Instance *);
	void	onResize();
	
	HWND	_hwndProp;
private:
	HWND	_propGrid;
	void	_redraw();
};