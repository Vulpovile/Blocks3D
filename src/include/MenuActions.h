#pragma once
#include "DataModelV3/DataModelInstance.h"
//TODO - Temporary location - Should be moved to different header once MFC gets involved
struct ActionParam {
	DataModelInstance *dataModel;
	Instance *caller;
	int actionCode;
};

#define MENUBTN_MENU 1
#define MENUBTN_GO   2

void menuCallback(const ActionParam & actionParam);