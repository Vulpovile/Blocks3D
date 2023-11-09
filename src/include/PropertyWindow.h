#pragma once
#include "DataModelV3/Instance.h"

class PropertyWindow {
public:
	PropertyWindow(int x, int y, int sx, int sy, HMODULE hThisInstance);
	bool	onCreate(int x, int y, int sx, int sy, HMODULE hThisInstance);
	void	UpdateSelected(std::vector<B3D::Instance *> selection);
	void	ClearProperties();
	void	onResize();
	void	refreshExplorer(std::vector<B3D::Instance *> selection);
	HWND	_hwndProp;
private:
	HWND	_propGrid;
	HWND	_explorerComboBox;
	void	_resize();
	void	clearExplorer();
};