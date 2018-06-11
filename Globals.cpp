#include "Globals.h"

DataModelInstance* Globals::dataModel = NULL;
int const Globals::gen = 0;
int const Globals::major = 0;
int const Globals::minor = 4;
int const Globals::patch = 2;
int Globals::surfaceId = 2;
bool Globals::showMouse = true;
bool Globals::useMousePoint = false;
G3D::TextureRef Globals::surface;
POINT Globals::mousepoint;
Globals::Globals(void){}

Globals::~Globals(void){}
