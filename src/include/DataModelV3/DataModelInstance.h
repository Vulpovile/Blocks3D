#include "Instance.h"
using namespace B3D;

#pragma once

// Instances
#include "WorkspaceInstance.h"
#include "LevelInstance.h"
#include "PartInstance.h"
#include "SelectionService.h"
#include "Gui/GuiRootInstance.h"
//#include "ThumbnailGeneratorInstance.h"
#include "XplicitNgine/XplicitNgine.h"
#include "SoundService.h"
#include "LightingInstance.h"

// Libraries 
//#include "rapidxml/rapidxml.hpp"
namespace B3D {
	class DataModelInstance : public Instance
	{
	public:
		DataModelInstance(void);
		~DataModelInstance(void);
		void					setMessage(std::string);
		void					setMessageBrickCount();
		void					clearMessage();
		void					drawMessage(RenderDevice*);
		
		// Instance getters
		WorkspaceInstance*				getWorkspace();
		LevelInstance*					getLevel();
		XplicitNgine*					getEngine();
	//	ThumbnailGeneratorInstance*		getThumbnailGenerator();
		SoundService*					getSoundService();
		LightingInstance*				getLighting();

		std::string				message;
		bool					showMessage;
	//Should probably not be here???
		G3D::GFontRef			font;
		GuiRootInstance*		getGuiRoot();
		SelectionService*		getSelectionService();
		void					clearLevel();
		void					toggleRun();
		bool					isRunning();
		void					resetEngine();
	private:
		bool isBrickCount;
		Color3 DataModelInstance::bcToRGB(short bc);
		// Instances
		WorkspaceInstance*		workspace;
		LevelInstance*			level;
		GuiRootInstance*		guiRoot;
		SelectionService*		selectionService;
	//	ThumbnailGeneratorInstance* thumbnailGenerator;
		XplicitNgine*			xplicitNgine;
		SoundService*			soundService;
		LightingInstance*		lightingInstance;
		bool					running;
		
	};
}