#pragma once
#include "rapidxml/rapidxml.hpp"
#include "instance.h"
#include "WorkspaceInstance.h"
#include "PhysicalInstance.h"

class DataModelInstance :
	public Instance
{
public:
	DataModelInstance(void);
	~DataModelInstance(void);
	void				setMessage(std::string);
	void				clearMessage();
	bool				load();	
	bool				printIfLoadError(const char* errorMsg);
	void				drawMessage(RenderDevice*);
	WorkspaceInstance*	getWorkspace();
	WorkspaceInstance*	workspace;
	Instance*			guiRoot;
	std::string			message;
	bool				showMessage;
	G3D::GFontRef		font;
	Instance*			getGuiRoot();
	float				mousex;
	float				mousey;
	Vector2				getMousePos();
	void				setMousePos(int x,int y);
	void				setMousePos(Vector2 pos);
	bool				mouseButton1Down;
	PhysicalInstance*	makePart();
private:
	bool					scanXMLObject(rapidxml::xml_node<>* node);
	rapidxml::xml_node<>*	getNode(rapidxml::xml_node<> * node,const char* name );
	float					getFloatValue(rapidxml::xml_node<> * node,const char* name);
	bool					_successfulLoad;
	std::string				_errMsg;
};
