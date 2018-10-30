#pragma once
#include "WorkspaceInstance.h"
#include "LevelInstance.h"
#include "PartInstance.h"
#include "rapidxml/rapidxml.hpp"

class DataModelInstance :
	public Instance
{
public:
	DataModelInstance(void);
	~DataModelInstance(void);
	void					setMessage(std::string);
	void					setMessageBrickCount();
	void					clearMessage();
	bool					load();	
	void					drawMessage(RenderDevice*);
	WorkspaceInstance*		getWorkspace();
	WorkspaceInstance*		workspace;
	LevelInstance *			level;
	LevelInstance *			getLevel();
	Instance*				guiRoot;
	std::string				message;
	bool					showMessage;
	G3D::GFontRef			font;
	Instance*				getGuiRoot();
	float					mousex;
	float					mousey;
	Vector2					getMousePos();
	void					setMousePos(int x,int y);
	void					setMousePos(Vector2 pos);
	bool					mouseButton1Down;
	PartInstance*			makePart();
	void					clearLevel();
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
};
