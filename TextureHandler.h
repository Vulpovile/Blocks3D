#pragma once
#include <G3DAll.h>
#include <map>
class TextureHandler
{
public:
	TextureHandler(void);
	~TextureHandler(void);
	static int getTextureVolatile(std::string str)
	{
		if(!volTex[str].isNull())
		{
			volExp[str] = G3D::System::time();
			return volTex[str]->openGLID();
		}
		else
		{
			G3D::TextureRef tex = G3D::Texture::fromFile(str);
			volExp[str] = G3D::System::time();
			volTex[str] = tex;
			return tex->openGLID();
		}
	}
	static int getTexturePermanent(std::string str)
	{
		if(!permTex[str].isNull())
		{
			return permTex[str]->openGLID();
		}
		else
		{
			G3D::TextureRef tex = G3D::Texture::fromFile(str);
			permTex[str] = tex;
			return tex->openGLID();
		}
	}
	static void flushVolatile()
	{
		std::map<std::string, G3D::RealTime>::iterator it;
		for (it=volExp.begin(); it!=volExp.end(); ++it)
		{
			if(it->second < G3D::System::time() - 3)
			{
				volTex[it->first]->~Texture();
				volTex.erase(it->first);
				volExp.erase(it->first);
				//it->second->~ReferenceCountedPointer();
			}
		}
	}
	static void dispose()
	{
		std::map<std::string, G3D::TextureRef>::iterator it;
		for (it=volTex.begin(); it!=volTex.end(); ++it)
		{
			it->second->~Texture();
			//it->second->~ReferenceCountedPointer();
		}
		for (it=permTex.begin(); it!=permTex.end(); ++it)
		{
			it->second->~Texture();
			//it->second->~ReferenceCountedPointer();
		}
		permTex.clear();
		volTex.clear();
	}

	static void remove(std::string str)
	{
		if(!volTex[str].isNull())
		{
			volTex[str]->~Texture();
			//volTex[str]->~ReferenceCountedPointer();
			volTex.erase(str);
		}
		if(!permTex[str].isNull())
		{
			permTex[str]->~Texture();
			//permTex[str]->~ReferenceCountedPointer();
			permTex.erase(str);
		}
	}
private:
	static std::map<std::string, G3D::TextureRef> volTex;
	static std::map<std::string, G3D::RealTime> volExp;
	static std::map<std::string, G3D::TextureRef> permTex;
};