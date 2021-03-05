#include <G3DAll.h>
#include "Application.h"
#include "Globals.h"
#include "AudioPlayer.h"
#include "GUDButtonListener.h"

void GUDButtonListener::onButton1MouseClick(BaseButtonInstance* button)
{
	bool cont = false;
	for(size_t i = 0; i < g_selectedInstances.size(); i++)
		if(g_selectedInstances.at(i)->canDelete)
		{
			cont = true;	
			break;
		}
	if(cont)
	{
		AudioPlayer::playSound(dingSound);
		if(button->name == "Duplicate")
		{
			std::vector<Instance*> newinst;
			for(size_t i = 0; i < g_selectedInstances.size(); i++)
			{
				if(g_selectedInstances.at(i)->canDelete)
				{
				Instance* tempinst = g_selectedInstances.at(i);
				
				Instance* clonedInstance = g_selectedInstances.at(i)->clone();

				newinst.push_back(tempinst);
				}
				/*tempinst->setPosition(Vector3(tempPos.x, tempPos.y + tempSize.y, tempPos.z));
				g_usableApp->cameraController.centerCamera(g_selectedInstances.at(0));*/
			}
			g_selectedInstances = newinst;
			if(g_selectedInstances.size() > 0)
				g_usableApp->_propWindow->UpdateSelected(newinst.at(0));
		}
		else if(button->name == "Group")
		{
			GroupInstance * inst = new GroupInstance();
			for(size_t i = 0; i < g_selectedInstances.size(); i++)
			{
				if(g_selectedInstances.at(i)->canDelete)
				{
					g_selectedInstances.at(i)->setParent(inst);
					if(PartInstance* part = dynamic_cast<PartInstance*>(g_selectedInstances.at(i)))
					{
						inst->primaryPart = part;
					}
				}
				/*tempinst->setPosition(Vector3(tempPos.x, tempPos.y + tempSize.y, tempPos.z));
				g_usableApp->cameraController.centerCamera(g_selectedInstances.at(0));*/
			}
			inst->setParent(g_dataModel->getWorkspace());
			g_selectedInstances.clear();
			g_selectedInstances.push_back(inst);
			if(g_selectedInstances.size() > 0)
				g_usableApp->_propWindow->UpdateSelected(g_selectedInstances.at(0));
		}
		else if(button->name == "UnGroup")
		{
			std::vector<Instance*> newinst;
			for(size_t i = 0; i < g_selectedInstances.size(); i++)
			{
				if(g_selectedInstances.at(i)->canDelete)
				{
					if(GroupInstance* model = dynamic_cast<GroupInstance*>(g_selectedInstances.at(i)))
					{
						newinst = model->unGroup();
						model->setParent(NULL);
						delete model;
						model = NULL;
					}
				}
				/*tempinst->setPosition(Vector3(tempPos.x, tempPos.y + tempSize.y, tempPos.z));
				g_usableApp->cameraController.centerCamera(g_selectedInstances.at(0));*/
			}
			g_selectedInstances.clear();
			g_selectedInstances = newinst;
			if(g_selectedInstances.size() > 0)
				g_usableApp->_propWindow->UpdateSelected(newinst.at(0));
		}
	}
}