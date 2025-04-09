#include "MenuActions.h"
#include "DataModelV3/Gui/ToggleImageButtonInstance.h"

void menuCallback(const ActionParam &actionParam) {
	switch(actionParam.actionCode) {
		case MENUBTN_GO:
			actionParam.dataModel->toggleRun(); //SHOULD USE C++ STYLE CASTING BUT IDC RN
			((ToggleImageButtonInstance*)actionParam.caller)->checked = actionParam.dataModel->isRunning();
			break;
	}
}

