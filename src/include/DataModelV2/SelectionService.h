#pragma once
#include "Instance.h"
#include "PropertyWindow.h"

class SelectionService : public Instance
{
public:
	SelectionService(void);
	~SelectionService(void);
	SelectionService(const SelectionService &oinst);
	std::vector<Instance *> getSelection();
	void clearSelection();
	bool isSelected(Instance * instance);
	void addSelected(Instance * instance);
	void removeSelected(Instance * instance);
	void addSelected(const std::vector<Instance *> &instances);
	void setPropertyWindow(PropertyWindow * propertyWindow);
	void render(RenderDevice * rd);
private:
	std::vector<Instance *> selection;
	PropertyWindow * propertyWindow;
};
