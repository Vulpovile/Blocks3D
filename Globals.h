#pragma once
#include "DataModelInstance.h"
#include <G3DAll.h>

class Application;

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
	static const std::string g_PlaceholderName;
};

extern std::vector<Instance*> postRenderStack;
extern std::vector<Instance*> g_selectedInstances;
extern bool running;
extern DataModelInstance* g_dataModel;
extern Application* g_usableApp;

extern GFontRef g_fntdominant;
extern GFontRef g_fntlighttrek;

extern std::string cameraSound;
extern std::string clickSound;
extern std::string dingSound;
const std::string g_PlaceholderName = "HyperCube";