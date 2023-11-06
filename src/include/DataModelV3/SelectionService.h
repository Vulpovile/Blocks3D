#pragma once
#include "Instance.h"
// TODO Port PropertyWindow
//#include "PropertyWindow.h"

namespace B3D{
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
		// TODO Port PropertyWindow
		//void setPropertyWindow(PropertyWindow * propertyWindow);
		void render(RenderDevice * rd);
	private:
		void drawOutline(Vector3 from, Vector3 to, RenderDevice* rd, Vector3 size, Vector3 pos, CoordinateFrame c);

		std::vector<Instance *> selection;
		int mode;
		// TODO Port PropertyWindow
		//PropertyWindow * propertyWindow;
	};
}