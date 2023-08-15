#pragma once

// Instances
#include "WorkspaceInstance.h"
#include "LevelInstance.h"
#include "PartInstance.h"
#include "SelectionService.h"
#include "GuiRootInstance.h"
#include "ThumbnailGeneratorInstance.h"
#include "XplicitNgine/XplicitNgine.h"
#include "SoundService.h"
#include "LightingInstance.h"

// Libraries 
#include "rapidxml/rapidxml.hpp"

class GuiRootInstance;

class DataModelInstance :
	public Instance
{
public:
	DataModelInstance(void);
	~DataModelInstance(void);
	void					setMessage(std::string);
	void					setMessageBrickCount();
	void					clearMessage();
	bool					debugGetOpen();
	bool					getOpen();
	bool                    getOpenModel();
	bool					load(const char* filename,bool clearObjects);	
	bool					loadModel(const char* filename);
	bool					readXMLFileStream(std::ifstream* file);
	void					drawMessage(RenderDevice*);
	
	// Instance getters
	WorkspaceInstance*				getWorkspace();
	LevelInstance*					getLevel();
	XplicitNgine*					getEngine();
	ThumbnailGeneratorInstance*		getThumbnailGenerator();
	SoundService*					getSoundService();
	LightingInstance*				getLighting();

	std::string				message;
	std::string				_loadedFileName;
	bool					showMessage;
	G3D::GFontRef			font;
	GuiRootInstance*		getGuiRoot();
	SelectionService*		getSelectionService();
	PartInstance*			makePart();
	void					clearLevel();
	void					toggleRun();
	bool					isRunning();
	void					resetEngine();
#if _DEBUG
	void					modXMLLevel(float modY);
#endif
private:
	bool isBrickCount;
	bool					scanXMLObject(rapidxml::xml_node<>* node);
	rapidxml::xml_node<>*	getNode(rapidxml::xml_node<> * node,const char* name );
	float					getFloatValue(rapidxml::xml_node<> * node,const char* name);
	bool					_successfulLoad;
	std::string				_errMsg;
	bool					_legacyLoad;
	float					_modY;
	
	// Instances
	WorkspaceInstance*		workspace;
	LevelInstance*			level;
	GuiRootInstance*		guiRoot;
	SelectionService*		selectionService;
	ThumbnailGeneratorInstance* thumbnailGenerator;
	XplicitNgine*			xplicitNgine;
	SoundService*			soundService;
	LightingInstance*		lightingInstance;
	bool					running;
	
};
