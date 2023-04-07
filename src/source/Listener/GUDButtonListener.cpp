#include <G3DAll.h>
#include "Application.h"
#include "Globals.h"
#include "AudioPlayer.h"
#include "DataModelV2/SelectionService.h"
#include "Listener/GUDButtonListener.h"

void GUDButtonListener::onButton1MouseClick(BaseButtonInstance* button)
{
	bool cont = false;
	for(size_t i = 0; i < g_dataModel->getSelectionService()->getSelection().size(); i++)
		if(g_dataModel->getSelectionService()->getSelection()[i]->canDelete)
		{
			cont = true;	
			break;
		}
	if(cont)
	{
		
		if(button->disabled == false){
			AudioPlayer::playSound(dingSound);
		}

		if(button->name == "Duplicate")
		{
			std::vector<Instance*> newinst;
			for(size_t i = 0; i < g_dataModel->getSelectionService()->getSelection().size(); i++)
			{
				if(g_dataModel->getSelectionService()->getSelection()[i]->canDelete)
				{
				Instance* tempinst = g_dataModel->getSelectionService()->getSelection()[i];
				
				Instance* clonedInstance = g_dataModel->getSelectionService()->getSelection()[i]->clone();

				newinst.push_back(tempinst);
				}
			}
			g_dataModel->getSelectionService()->clearSelection();
			g_dataModel->getSelectionService()->addSelected(newinst);
		}
		else if(button->name == "Group")
		{
			if (g_dataModel->getSelectionService()->getSelection().size() > 1){
				GroupInstance * inst = new GroupInstance();
				inst->setParent(g_dataModel->getWorkspace());
				for(size_t i = 0; i < g_dataModel->getSelectionService()->getSelection().size(); i++)
				{
					if(g_dataModel->getSelectionService()->getSelection()[i]->canDelete)
					{
						g_dataModel->getSelectionService()->getSelection()[i]->setParent(inst);
						if(PartInstance* part = dynamic_cast<PartInstance*>(g_dataModel->getSelectionService()->getSelection()[i]))
						{
							inst->primaryPart = part;
						}
					}
				}
				g_dataModel->getSelectionService()->clearSelection();
				g_dataModel->getSelectionService()->addSelected(inst);
			}			
		}
		else if(button->name == "UnGroup")
		{
			std::vector<Instance*> newinst;
			for(size_t i = 0; i < g_dataModel->getSelectionService()->getSelection().size(); i++)
			{
				Instance* selection = g_dataModel->getSelectionService()->getSelection()[i];
				if(selection->canDelete && selection->getClassName() == "GroupInstance")
				{
					if(GroupInstance* model = dynamic_cast<GroupInstance*>(g_dataModel->getSelectionService()->getSelection()[i]))
					{
						newinst = model->unGroup();
						model->setParent(NULL);
						delete model;
						model = NULL;
					}
				}
			}
			g_dataModel->getSelectionService()->clearSelection();
			g_dataModel->getSelectionService()->addSelected(newinst);
		}
	}
}