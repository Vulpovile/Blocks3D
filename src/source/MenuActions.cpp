#include "MenuActions.h"


void menuCallback(const ActionParam &actionParam) {
	switch(actionParam.actionCode) {
		case MENUBTN_GO:
			actionParam.dataModel->toggleRun();
			break;
	}
}

