#include <G3DAll.h>
#include "Application.h"
#include "Globals.h"
#include "DataModelV2/SelectionService.h"
#include "Listener/GUDButtonListener.h"
#include "DataModelV2/SoundService.h"

void GUDButtonListener::onButton1MouseClick(BaseButtonInstance* button)
{
	SelectionService* SelectionSvc = g_dataModel->getSelectionService();
	SoundService* SoundSvc = g_dataModel->getSoundService();

	bool cont = false;
	for(size_t i = 0; i < SelectionSvc->getSelection().size(); i++)
		if(SelectionSvc->getSelection()[i]->canDelete)
		{
			cont = true;	
			break;
		}

	if (cont)
	{
		if(button->disabled == false){
			SoundSvc->playSound(SoundSvc->findFirstChild("Ping"));
		}

		if(button->name == "Duplicate")
		{
			std::vector<Instance*> newinst;
			for(size_t i = 0; i < SelectionSvc->getSelection().size(); i++)
			{
				if(SelectionSvc->getSelection()[i]->canDelete)
				{
				Instance* tempinst = SelectionSvc->getSelection()[i];
				
				Instance* clonedInstance = SelectionSvc->getSelection()[i]->clone();

				if (clonedInstance->getClassName() == "PVInstance"){
					PartInstance* Part = dynamic_cast<PartInstance*>(clonedInstance);
					Part->setPosition(Part->getPosition() + G3D::Vector3(0, Part->getSize().y, 0));
				}

				newinst.push_back(clonedInstance);
				}
			}
			SelectionSvc->clearSelection();
			SelectionSvc->addSelected(newinst);
		}
		else if(button->name == "Group")
		{
			if (SelectionSvc->getSelection().size() > 1){
				GroupInstance * inst = new GroupInstance();
				inst->setParent(g_dataModel->getWorkspace());
				for(size_t i = 0; i < SelectionSvc->getSelection().size(); i++)
				{
					if(SelectionSvc->getSelection()[i]->canDelete)
					{
						SelectionSvc->getSelection()[i]->setParent(inst);
						if(PartInstance* part = dynamic_cast<PartInstance*>(SelectionSvc->getSelection()[i]))
						{
							inst->primaryPart = part;
						}
					}
				}
				SelectionSvc->clearSelection();
				SelectionSvc->addSelected(inst);
			}			
		}
		else if(button->name == "UnGroup")
		{
			std::vector<Instance*> newinst;
			for(size_t i = 0; i < SelectionSvc->getSelection().size(); i++)
			{
				Instance* selection = SelectionSvc->getSelection()[i];
				if(selection->canDelete && selection->getClassName() == "GroupInstance")
				{
					if(GroupInstance* model = dynamic_cast<GroupInstance*>(SelectionSvc->getSelection()[i]))
					{
						newinst = model->unGroup();
						model->setParent(NULL);
						delete model;
						model = NULL;
					}
				}
			}
			SelectionSvc->clearSelection();
			SelectionSvc->addSelected(newinst);
		}
	}
}