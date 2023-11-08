#pragma once
#include "../Instance.h"

namespace B3D{
	//TODO deprecated
	class ImageButtonInstance;
	//TODO deprecated
	class TextButtonInstance;
	class GuiRootInstance : public Instance
	{
	public:
		GuiRootInstance();
		GuiRootInstance::~GuiRootInstance();
		
		//TODO deprecated
		TextButtonInstance*		makeTextButton();
		void					drawButtons(RenderDevice* rd);
		
		//TODO deprecated
		ImageButtonInstance*	makeImageButton(G3D::TextureRef newImage, G3D::TextureRef overImage, G3D::TextureRef downImage, G3D::TextureRef disableImage);
		void					renderGUI(G3D::RenderDevice* rd, double fps);
		void					setDebugMessage(std::string msg, G3D::RealTime msgTime);
		void					update();
		bool					mouseInGUI(G3D::RenderDevice* renderDevice,int x,int y);
		void					onMouseLeftUp(G3D::RenderDevice* renderDevice, int x,int y);
		void					hideGui(bool doHide);
	private:
		G3D::GFontRef		fntdominant;
		G3D::GFontRef		fntlighttrek;
		std::string			_message;
		G3D::RealTime		_messageTime;
		bool				_hideGui;
	};
}