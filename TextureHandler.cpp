#include "TextureHandler.h"

TextureHandler::TextureHandler(void)
{
}

TextureHandler::~TextureHandler(void)
{
}
std::map<std::string, G3D::TextureRef> TextureHandler::volTex = std::map<std::string, G3D::TextureRef>();
std::map<std::string, G3D::RealTime> TextureHandler::volExp = std::map<std::string, G3D::RealTime>();
std::map<std::string, G3D::TextureRef> TextureHandler::permTex = std::map<std::string, G3D::TextureRef>();