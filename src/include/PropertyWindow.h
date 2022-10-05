#pragma once
#include "DataModelV2/Instance.h"

class PropertyWindow {
public:
	PropertyWindow(int x, int y, int sx, int sy, HMODULE hThisInstance);
	bool	onCreate(int x, int y, int sx, int sy, HMODULE hThisInstance);
	void	UpdateSelected(std::vector<Instance *> selection);
	void	ClearProperties();
	void	onResize();
	void	refreshExplorer(std::vector<Instance *> selection);
	HWND	_hwndProp;
private:
	HWND	_propGrid;
	HWND	_explorerComboBox;
	void	_resize();
	void	clearExplorer();
};