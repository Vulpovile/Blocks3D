#pragma once
#include "WorkspaceInstance.h"
#include "LevelInstance.h"
#include "PartInstance.h"
#include "rapidxml/rapidxml.hpp"
#include "GuiRootInstance.h"
#include "XplicitNgine/XplicitNgine.h"

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
	bool					load(const char* filename,bool clearObjects);	
	bool					readXMLFileStream(std::ifstream* file);
	void					drawMessage(RenderDevice*);
	WorkspaceInstance*		getWorkspace();
	LevelInstance *			getLevel();
	XplicitNgine *			getEngine();
	std::string				message;
	std::string				_loadedFileName;
	bool					showMessage;
	G3D::GFontRef			font;
	GuiRootInstance*		getGuiRoot();
	//float					mousex;
	//float					mousey;
	//Vector2					getMousePos();
	//void					setMousePos(int x,int y);
	//void					setMousePos(Vector2 pos);
	//bool					mouseButton1Down;
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
	WorkspaceInstance*		workspace;
	LevelInstance *			level;
	GuiRootInstance*		guiRoot;
	bool					running;
	XplicitNgine *			xplicitNgine;
};
