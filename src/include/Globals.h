#pragma once
#include "DataModelV2/DataModelInstance.h"
#include "XplicitNgine/XplicitNgine.h"

class Application;

class Globals
{
public:
    Globals(void);
    ~Globals(void);
    static DataModelInstance* dataModel;
	//static bool showMouse;
	static POINT mousepoint;
	static bool useMousePoint;
	static const int gen;
	static const int major;
	static const int minor;
	static const int patch;
	static G3D::TextureRef surface;
	static int surfaceId;
	static const std::string g_appName;
	static COLORREF g_acrCustClr[16]; //Will be dynamic later
	static HWND mainHwnd;
};

extern std::vector<Instance*> postRenderStack;
extern std::vector<Instance*> g_selectedInstances;
extern bool running;
extern DataModelInstance* g_dataModel;
extern XplicitNgine* g_xplicitNgine;
extern Application* g_usableApp;

extern GFontRef g_fntdominant;
extern GFontRef g_fntlighttrek;

extern COLORREF g_acrCustClr[16]; //Will be dynamic later
extern std::string cameraSound;
extern std::string clickSound;
extern std::string dingSound;
extern HWND mainHwnd;
const std::string g_appName = "Blocks3D";