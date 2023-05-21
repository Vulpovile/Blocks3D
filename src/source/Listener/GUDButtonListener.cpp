#include <G3DAll.h>
#include "Application.h"
#include "Globals.h"
#include "DataModelV2/SelectionService.h"
#include "Listener/GUDButtonListener.h"
#include "DataModelV2/SoundService.h"

void GUDButtonListener::onButton1MouseClick(BaseButtonInstance* button)
{
	SelectionService* getSelectionService = g_dataModel->getSelectionService();
	SoundService* getSoundService = g_dataModel->getSoundService();

	bool cont = false;
	for(size_t i = 0; i < getSelectionService->getSelection().size(); i++)
		if(getSelectionService->getSelection()[i]->canDelete)
		{
			cont = true;	
			break;
		}

	if (cont)
	{
		if(button->disabled == false){
			getSoundService->playSound(getSoundService->findFirstChild("Ping"));
		}

		if(button->name == "Duplicate")
		{
			std::vector<Instance*> newinst;
			for(size_t i = 0; i < getSelectionService->getSelection().size(); i++)
			{
				if(getSelectionService->getSelection()[i]->canDelete)
				{
				Instance* tempinst = getSelectionService->getSelection()[i];
				
				Instance* clonedInstance = getSelectionService->getSelection()[i]->clone();

				if (clonedInstance->getClassName() == "PVInstance"){
					PartInstance* Part = dynamic_cast<PartInstance*>(clonedInstance);
					Part->setPosition(Part->getPosition() + G3D::Vector3(0, Part->getSize().y, 0));
				}

				newinst.push_back(clonedInstance);
				}
			}
			getSelectionService->clearSelection();
			getSelectionService->addSelected(newinst);
		}
		else if(button->name == "Group")
		{
			if (getSelectionService->getSelection().size() > 1){
				GroupInstance * inst = new GroupInstance();
				inst->setParent(g_dataModel->getWorkspace());
				for(size_t i = 0; i < getSelectionService->getSelection().size(); i++)
				{
					if(getSelectionService->getSelection()[i]->canDelete)
					{
						getSelectionService->getSelection()[i]->setParent(inst);
						if(PartInstance* part = dynamic_cast<PartInstance*>(getSelectionService->getSelection()[i]))
						{
							inst->primaryPart = part;
						}
					}
				}
				getSelectionService->clearSelection();
				getSelectionService->addSelected(inst);
			}			
		}
		else if(button->name == "UnGroup")
		{
			std::vector<Instance*> newinst;
			for(size_t i = 0; i < getSelectionService->getSelection().size(); i++)
			{
				Instance* selection = getSelectionService->getSelection()[i];

				if(GroupInstance* model = dynamic_cast<GroupInstance*>(selection))
				{
					newinst = model->unGroup();
					model->setParent(NULL);
					delete model;
					model = NULL;
				}
			}
			getSelectionService->clearSelection();
			getSelectionService->addSelected(newinst);
		}
	}
}