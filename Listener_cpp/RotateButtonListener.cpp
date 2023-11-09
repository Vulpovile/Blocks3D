#include "DataModelV2/BaseButtonInstance.h"
#include "Listener/RotateButtonListener.h"
#include "Globals.h"
#include "AudioPlayer.h"

void RotateButtonListener::onButton1MouseClick(BaseButtonInstance* button)
{
	if(g_dataModel->getSelectionService()->getSelection().size() > 0)
	{
		Instance* selectedInstance = g_dataModel->getSelectionService()->getSelection()[0];
		AudioPlayer::playSound(clickSound);
		if(PartInstance* part = dynamic_cast<PartInstance*>(selectedInstance))
		{
			if(button->name == "Tilt")
				part->setCFrame(part->getCFrame()*Matrix3::fromEulerAnglesXYZ(0,0,toRadians(90)));
			else if(button->name == "Rotate")
				part->setCFrame(part->getCFrame()*Matrix3::fromEulerAnglesXYZ(0,toRadians(90),0));
		}
	}
		
}
