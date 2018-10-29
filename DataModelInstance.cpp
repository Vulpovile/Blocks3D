#include <string>
#include "DataModelInstance.h"
#include <fstream>
#include <iostream>
#include <sstream>

using namespace std;
using namespace rapidxml;


DataModelInstance::DataModelInstance(void)
{
	Instance::Instance();
	workspace = new WorkspaceInstance();
	guiRoot = new Instance();
	level = new LevelInstance();
	//children.push_back(workspace);
	//children.push_back(level);
	className = "dataModel";
	mousex = 0;
	mousey = 0;
	mouseButton1Down = false;
	showMessage = false;
	canDelete = false;

	workspace->setParent(this);
	level->setParent(this);
	
}

DataModelInstance::~DataModelInstance(void)
{
}

PartInstance* DataModelInstance::makePart()
{
	PartInstance* part = new PartInstance();
	return part;
}

rapidxml::xml_node<>* DataModelInstance::getNode(xml_node<> * node,const char* name)
{
	xml_node<> * tempNode = node->first_node(name);
	if (!tempNode)
	{
		_errMsg = "Expected <";
		_errMsg += name;
		_errMsg+="> tag.";
		_successfulLoad=true;
		return 0;
	}
	return tempNode;
}
float DataModelInstance::getFloatValue(xml_node<> * node,const char* name)
{
	xml_node<> * tempNode = node->first_node(name);
	if (!tempNode)
	{
		_errMsg = "Expected <";
		_errMsg += name;
		_errMsg+="> tag.";
		_successfulLoad=true;
		return 0;
	}
	float newFloat;
	stringstream converter;
	converter << tempNode->value();
	converter >> newFloat;
	return newFloat;
}

bool DataModelInstance::scanXMLObject(xml_node<> * scanNode)
{
	xml_node<> * watchFirstNode = scanNode->first_node();
	
	for (xml_node<> *node = scanNode->first_node();node; node = node->next_sibling())
	{

		if (strncmp(node->name(),"Item",4)==0)
		{
			xml_attribute<> *classAttr = node->first_attribute("class");
			std::string className = classAttr->value();
			if (className=="Part") {
				xml_node<> *propNode = node->first_node();
				xml_node<> *cFrameNode=0;
				xml_node<> *sizeNode=0;
				xml_node<> *colorNode=0;

				for (xml_node<> *partPropNode = propNode->first_node();partPropNode; partPropNode = partPropNode->next_sibling())
				{
					for (xml_attribute<> *attr = partPropNode->first_attribute();attr; attr = attr->next_attribute())
					{
						std::string xmlName = attr->name();
						std::string xmlValue = attr->value();
						
						if (xmlValue=="CFrame" | xmlValue=="CoordinateFrame")
						{
							 cFrameNode = partPropNode;
						}
						if (xmlValue=="Color")
						{
							colorNode=partPropNode;
						}
						if (xmlValue=="size")
						{
							sizeNode = partPropNode;
						}
						if (xmlValue=="Part")
						{
							for (xml_node<> *featureNode = partPropNode->first_node();featureNode; featureNode = featureNode->next_sibling())
							{
								for (xml_attribute<> *attr = featureNode->first_attribute();attr; attr = attr->next_attribute())
								{
									std::string xmlName = attr->name();
									std::string xmlValue = attr->value();
									if (xmlValue=="size")
									{
										sizeNode=featureNode;
									}
								}
							}
						}
					}
				}

				if (!cFrameNode) {
					_errMsg="CFrame is missing in Part";
					return false;
				}
				if (!sizeNode) {
					_errMsg="Size is missing in Part";
					return false;
				}

				float R=1;
				float G=1;
				float B=1;

				if (colorNode)
				{
					R = getFloatValue(colorNode,"R");
					G = getFloatValue(colorNode,"G");
					B = getFloatValue(colorNode,"B");
				}

				float X = getFloatValue(cFrameNode,"X");
				float Y = getFloatValue(cFrameNode,"Y");
				float Z = getFloatValue(cFrameNode,"Z");
				float R00 = getFloatValue(cFrameNode,"R00");
				float R01 = getFloatValue(cFrameNode,"R01");
				float R02 = getFloatValue(cFrameNode,"R02");
				float R10 = getFloatValue(cFrameNode,"R10");
				float R11 = getFloatValue(cFrameNode,"R11");
				float R12 = getFloatValue(cFrameNode,"R12");
				float R20 = getFloatValue(cFrameNode,"R20");
				float R21 = getFloatValue(cFrameNode,"R21");
				float R22 = getFloatValue(cFrameNode,"R22");

				float sizeX = getFloatValue(sizeNode,"X");
				float sizeY = getFloatValue(sizeNode,"Y");
				float sizeZ = getFloatValue(sizeNode,"Z");

				if (_successfulLoad) {
					PartInstance* test = makePart();
					test->setParent(getWorkspace());
					test->color = Color3(R,G,B);
					test->setSize(Vector3(sizeX,sizeY,sizeZ));

					CoordinateFrame what;
					what.translation = Vector3(X,Y,Z);
					what.rotation = Matrix3(R00,R01,R02,R10,R11,R12,R20,R21,R22);
					test->setCFrame(what);
				}
				else
				{
					return false;
				}

			}
		}
		/*
		for (xml_attribute<> *attr = node->first_attribute();attr; attr = attr->next_attribute())
		{
			std::string xmlName = attr->name();
			std::string xmlValue = attr->value();
		}
		*/
		scanXMLObject(node);
	}

	return true;
}

bool DataModelInstance::load()
{
	ifstream levelFile("..//skooterFix.rbxm",ios::binary);
	if (levelFile) {
		levelFile.seekg(0,levelFile.end);
		int length = levelFile.tellg();
		levelFile.seekg(0,levelFile.beg);
		char * buffer = new char[length+1];
		buffer[length]=0;
		levelFile.read(buffer,length);
		xml_document<> doc;
		doc.parse<0>(buffer);
		xml_node<> *mainNode = doc.first_node();
		std::string xmlName = mainNode->name();
		//node = node->first_node();
		//xmlName = node->name();
		scanXMLObject(mainNode);

		delete[] buffer;
	}
	return true;
}

void DataModelInstance::setMessage(std::string msg)
{
	message = msg;
	isBrickCount = false;
	showMessage = true;
}

void DataModelInstance::clearMessage()
{
	showMessage = false;
	isBrickCount = false;
	message = "";
}

void DataModelInstance::setMessageBrickCount()
{
	isBrickCount = true;
	showMessage = true;
}

void DataModelInstance::drawMessage(RenderDevice* rd)
{
	if(isBrickCount)
	{
		int brickCount = 0;
		int instCount = 0;
		std::vector<Instance*> inst = getAllChildren();
		for(size_t i = 0; i < inst.size(); i++)
		{
			if(PartInstance* moveTo = dynamic_cast<PartInstance*>(inst.at(i)))
			{
				brickCount++;
			}
			else
			{
				instCount++;
			}
		}
		char brkc[12];
		sprintf(brkc, "%d", brickCount);
		char instc[12];
		sprintf(instc, "%d", instCount);
		message = "Bricks: ";
		message += brkc;
		message += "	Snaps: ";
		message += instc;
	}
	if(showMessage && !font.isNull())
	{
		int x = rd->getWidth()/2;
		int y = rd->getHeight()/2;
		int width = rd->getWidth()/2 + 100;
		int height = width / 3;
		Draw::box(Box(Vector3(x-(width/2), y-(height/2), 0), Vector3(x+(width/2), y+(height/2), 0)), rd, Color4::fromARGB(0x55B2B2B2), Color3::fromARGB(0xB2B2B2));
		font->draw2D(rd, message, Vector2(x,y), height/8, Color3::white(), Color4::clear(), GFont::XALIGN_CENTER, GFont::YALIGN_CENTER);
	}
}

WorkspaceInstance* DataModelInstance::getWorkspace()
{
	return workspace;
}
Vector2 DataModelInstance::getMousePos()
{
	return Vector2(mousex,mousey);
}
void DataModelInstance::setMousePos(int x,int y)
{
	mousex=x;
	mousey=y;
}
void DataModelInstance::setMousePos(Vector2 pos)
{
	mousex=pos.x;
	mousey=pos.y;
}
Instance* DataModelInstance::getGuiRoot()
{
	return guiRoot;
}


LevelInstance* DataModelInstance::getLevel()
{
	return level;
}