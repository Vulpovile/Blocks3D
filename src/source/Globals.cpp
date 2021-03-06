#include "Globals.h"
#include "Application.h"

int const Globals::gen = 0;
int const Globals::major = 0;
int const Globals::minor = 4;
int const Globals::patch = 2;
int Globals::surfaceId = 2;
bool Globals::showMouse = true;
bool Globals::useMousePoint = false;
std::vector<Instance*> postRenderStack = std::vector<Instance*>();

std::vector<Instance*> g_selectedInstances = std::vector<Instance*>();
DataModelInstance* g_dataModel = NULL;

bool running = false;
G3D::TextureRef Globals::surface;
POINT Globals::mousepoint;

GFontRef g_fntdominant = NULL;
GFontRef g_fntlighttrek = NULL;
HWND Globals::mainHwnd = NULL;

Globals::Globals(void){}

Globals::~Globals(void){}

std::string cameraSound="";
std::string clickSound="";
std::string dingSound="";

Application *g_usableApp = NULL;

COLORREF g_acrCustClr[16] = {RGB(255,255,255),RGB(255,255,255),RGB(255,255,255),RGB(255,255,255),RGB(255,255,255),RGB(255,255,255),RGB(255,255,255),RGB(255,255,255),RGB(255,255,255),RGB(255,255,255),RGB(255,255,255),RGB(255,255,255),RGB(255,255,255),RGB(255,255,255),RGB(255,255,255),RGB(255,255,255)};