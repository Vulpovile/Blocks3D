#pragma once
#include "DataModelInstance.h"

class Globals
{
public:
    Globals(void);
    ~Globals(void);
    static DataModelInstance* dataModel;
	static bool showMouse;
	static const int gen;
	static const int major;
	static const int minor;
	static const int patch;
};