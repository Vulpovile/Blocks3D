#ifndef RENDERUTIL
#define RENDERUTIL
#include "Enum.h"
#include "DataModelV2/Instance.h"
void renderShape(const Enum::Shape::Value& shape, const Vector3& size, const Color3& ncolor);
void renderSurface(const char face, const Vector3& size, const Enum::SurfaceType::Value& surface, const Enum::Controller::Value& controller);
#endif
