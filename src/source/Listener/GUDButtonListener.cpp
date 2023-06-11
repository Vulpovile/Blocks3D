#include <G3DAll.h>
#include "Application.h"
#include "Globals.h"
#include "DataModelV2/SelectionService.h"
#include "Listener/GUDButtonListener.h"
#include "DataModelV2/SoundService.h"

void GUDButtonListener::onButton1MouseClick(BaseButtonInstance* button)
{
	SelectionService* selectionService = g_dataModel->getSelectionService();
	SoundService* soundService = g_dataModel->getSoundService();

	bool cont = false;
	for(size_t i = 0; i < selectionService->getSelection().size(); i++)
		if(selectionService->getSelection()[i]->canDelete)
		{
			cont = true;	
			break;
		}

	if (cont)
	{
		if(button->disabled == false){
			soundService->playSound(soundService->findFirstChild("Ping"));
		}

		if(button->name == "Duplicate")
		{
			std::vector<Instance*> newinst;
			for(size_t i = 0; i < selectionService->getSelection().size(); i++)
			{
				if(selectionService->getSelection()[i]->canDelete)
				{
				Instance* tempinst = selectionService->getSelection()[i];
				
				Instance* clonedInstance = selectionService->getSelection()[i]->clone();

				if (clonedInstance->getClassName() == "PVInstance"){
					PartInstance* Part = dynamic_cast<PartInstance*>(clonedInstance);
					Part->setPosition(Part->getPosition() + G3D::Vector3(0, Part->getSize().y, 0));
				}

				newinst.push_back(clonedInstance);
				}
			}
			selectionService->clearSelection();
			selectionService->addSelected(newinst);
		}
		else if(button->name == "Group")
		{
			if (selectionService->getSelection().size() > 1){
				GroupInstance * inst = new GroupInstance();
				inst->setParent(g_dataModel->getWorkspace());
				for(size_t i = 0; i < selectionService->getSelection().size(); i++)
				{
					if(selectionService->getSelection()[i]->canDelete)
					{
						selectionService->getSelection()[i]->setParent(inst);
						if(PartInstance* part = dynamic_cast<PartInstance*>(selectionService->getSelection()[i]))
						{
							inst->primaryPart = part;
						}
					}
				}
				selectionService->clearSelection();
				selectionService->addSelected(inst);
			}			
		}
		else if(button->name == "UnGroup")
		{
			std::vector<Instance*> newinst;
			for(size_t i = 0; i < selectionService->getSelection().size(); i++)
			{
				Instance* selection = selectionService->getSelection()[i];

				if(GroupInstance* model = dynamic_cast<GroupInstance*>(selection))
				{
					newinst = model->unGroup();
					model->setParent(NULL);
					delete model;
					model = NULL;
				}
			}
			selectionService->clearSelection();
			selectionService->addSelected(newinst);
		}
	}
}