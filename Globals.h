#pragma once
#include "DataModelInstance.h"
#include <G3DAll.h>

class Globals
{
public:
    Globals(void);
    ~Globals(void);
    static DataModelInstance* dataModel;
	static bool showMouse;
	static POINT mousepoint;
	static bool useMousePoint;
	static const int gen;
	static const int major;
	static const int minor;
	static const int patch;
	static G3D::TextureRef surface;
	static int surfaceId;
};