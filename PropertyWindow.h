#pragma once

class PropertyWindow {
public:
	PropertyWindow(int x, int y, int sx, int sy, HMODULE hThisInstance);
	bool	onCreate(int x, int y, int sx, int sy, HMODULE hThisInstance);
	void	onResize();
private:
	HWND	_propGrid;
	HWND	_hwndProp;
	void	_redraw();
};