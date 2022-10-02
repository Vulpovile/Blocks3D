#include <string>
#include "DataModelV2/GuiRootInstance.h"
#include "DataModelV2/DataModelInstance.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <commdlg.h>
#include "ErrorFunctions.h"
#include "Globals.h"
#include "Application.h"

using namespace std;
using namespace rapidxml;


DataModelInstance::DataModelInstance(void)
{
	Instance::Instance();
	workspace = new WorkspaceInstance();
	guiRoot = new GuiRootInstance();
	level = new LevelInstance();
	//children.push_back(workspace);
	//children.push_back(level);
	className = "dataModel";
	//mousex = 0;
	//mousey = 0;
	//mouseButton1Down = false;
	showMessage = false;
	canDelete = false;
	_modY=0;
	workspace->setParent(this);
	level->setParent(this);
	_loadedFileName="..//skooter.rbxm";
	listicon = 5;
	running = false;
	xplicitNgine = NULL;
	resetEngine();
}

void DataModelInstance::resetEngine()
{
	if(xplicitNgine != NULL)
		delete xplicitNgine;
	xplicitNgine = new XplicitNgine();
	g_xplicitNgine = xplicitNgine;
	for(size_t i = 0; i < getWorkspace()->partObjects.size(); i++)
	{
		PartInstance* partInstance = getWorkspace()->partObjects[i];
		partInstance->physBody = NULL;
	}
}

XplicitNgine * DataModelInstance::getEngine()
{
	return xplicitNgine;
}

void DataModelInstance::toggleRun()
{
	running = !running;
	//if(!running)
		//resetEngine();
}
bool DataModelInstance::isRunning()
{
	return running;
}

DataModelInstance::~DataModelInstance(void)
{
	delete xplicitNgine;
}

#ifdef _DEBUG
void DataModelInstance::modXMLLevel(float modY)
{
	_modY += modY;
	clearLevel();
	debugGetOpen();

}
#endif

void DataModelInstance::clearLevel()
{
	workspace->clearChildren();
	g_usableApp->_propWindow->UpdateSelected(this);
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
		_successfulLoad=false;
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
		_successfulLoad=false;
		return 0;
	}
	float newFloat;
	stringstream converter;
	converter << tempNode->value();
	converter >> newFloat;
	return newFloat;
}


Color3 bcToRGB(short bc)
{
	switch(bc)
	{
		case 1: return Color3(0.94901967048645F,0.95294123888016F,0.95294123888016F);
		case 2: return Color3(0.63137257099152F,0.64705884456635F,0.63529413938522F);
		case 3: return Color3(0.9764706492424F,0.91372555494308F,0.60000002384186F);
		case 5: return Color3(0.84313732385635F,0.77254909276962F,0.60392159223557F);
		case 6: return Color3(0.7607843875885F,0.85490202903748F,0.72156864404678F);
		case 9: return Color3(0.90980398654938F,0.7294117808342F,0.78431379795074F);
		case 11: return Color3(0.50196081399918F,0.73333334922791F,0.85882359743118F);
		case 12: return Color3(0.79607850313187F,0.51764708757401F,0.258823543787F);
		case 18: return Color3(0.80000007152557F,0.55686277151108F,0.41176474094391F);
		case 21: return Color3(0.76862752437592F,0.15686275064945F,0.10980392992496F);
		case 22: return Color3(0.76862752437592F,0.43921571969986F,0.62745100259781F);
		case 23: return Color3(0.050980396568775F,0.41176474094391F,0.6745098233223F);
		case 24: return Color3(0.96078437566757F,0.80392163991928F,0.18823531270027F);
		case 25: return Color3(0.38431376218796F,0.27843138575554F,0.19607844948769F);
		case 26: return Color3(0.10588236153126F,0.16470588743687F,0.20784315466881F);
		case 27: return Color3(0.42745101451874F,0.43137258291245F,0.42352944612503F);
		case 28: return Color3(0.15686275064945F,0.49803924560547F,0.27843138575554F);
		case 29: return Color3(0.63137257099152F,0.76862752437592F,0.54901963472366F);
		case 36: return Color3(0.95294123888016F,0.8117647767067F,0.60784316062927F);
		case 37: return Color3(0.29411765933037F,0.59215688705444F,0.29411765933037F);
		case 38: return Color3(0.62745100259781F,0.37254902720451F,0.20784315466881F);
		case 39: return Color3(0.75686281919479F,0.79215693473816F,0.8705883026123F);
		case 40: return Color3(0.92549026012421F,0.92549026012421F,0.92549026012421F);
		case 41: return Color3(0.80392163991928F,0.32941177487373F,0.29411765933037F);
		case 42: return Color3(0.75686281919479F,0.87450987100601F,0.94117653369904F);
		case 43: return Color3(0.48235297203064F,0.71372550725937F,0.90980398654938F);
		case 44: return Color3(0.96862751245499F,0.94509810209274F,0.55294120311737F);
		case 45: return Color3(0.70588237047195F,0.82352948188782F,0.89411771297455F);
		case 47: return Color3(0.85098046064377F,0.52156865596771F,0.42352944612503F);
		case 48: return Color3(0.51764708757401F,0.71372550725937F,0.55294120311737F);
		case 49: return Color3(0.97254908084869F,0.94509810209274F,0.51764708757401F);
		case 50: return Color3(0.92549026012421F,0.90980398654938F,0.8705883026123F);
		case 100: return Color3(0.93333339691162F,0.76862752437592F,0.71372550725937F);
		case 101: return Color3(0.85490202903748F,0.52549022436142F,0.47843140363693F);
		case 102: return Color3(0.43137258291245F,0.60000002384186F,0.79215693473816F);
		case 103: return Color3(0.78039222955704F,0.75686281919479F,0.71764707565308F);
		case 104: return Color3(0.41960787773132F,0.19607844948769F,0.48627454042435F);
		case 105: return Color3(0.88627457618713F,0.60784316062927F,0.25098040699959F);
		case 106: return Color3(0.85490202903748F,0.52156865596771F,0.2549019753933F);
		case 107: return Color3(0,0.56078433990479F,0.61176472902298F);
		case 108: return Color3(0.4078431725502F,0.36078432202339F,0.26274511218071F);
		case 110: return Color3(0.26274511218071F,0.32941177487373F,0.57647061347961F);
		case 111: return Color3(0.74901962280273F,0.71764707565308F,0.69411766529083F);
		case 112: return Color3(0.4078431725502F,0.45490199327469F,0.6745098233223F);
		case 113: return Color3(0.89411771297455F,0.678431391716F,0.78431379795074F);
		case 115: return Color3(0.78039222955704F,0.82352948188782F,0.23529413342476F);
		case 116: return Color3(0.33333334326744F,0.64705884456635F,0.68627452850342F);
		case 118: return Color3(0.71764707565308F,0.84313732385635F,0.83529418706894F);
		case 119: return Color3(0.64313727617264F,0.74117648601532F,0.27843138575554F);
		case 120: return Color3(0.85098046064377F,0.89411771297455F,0.65490198135376F);
		case 121: return Color3(0.90588241815567F,0.6745098233223F,0.34509804844856F);
		case 123: return Color3(0.82745105028152F,0.43529415130615F,0.29803922772408F);
		case 124: return Color3(0.57254904508591F,0.22352942824364F,0.47058826684952F);
		case 125: return Color3(0.91764712333679F,0.72156864404678F,0.57254904508591F);
		case 126: return Color3(0.64705884456635F,0.64705884456635F,0.79607850313187F);
		case 127: return Color3(0.86274516582489F,0.73725491762161F,0.50588238239288F);
		case 128: return Color3(0.68235296010971F,0.47843140363693F,0.34901961684227F);
		case 131: return Color3(0.61176472902298F,0.63921570777893F,0.65882354974747F);
		case 133: return Color3(0.83529418706894F,0.45098042488098F,0.23921570181847F);
		case 134: return Color3(0.84705889225006F,0.8666667342186F,0.33725491166115F);
		case 135: return Color3(0.45490199327469F,0.52549022436142F,0.61568629741669F);
		case 136: return Color3(0.52941179275513F,0.48627454042435F,0.56470590829849F);
		case 137: return Color3(0.87843143939972F,0.59607845544815F,0.39215689897537F);
		case 138: return Color3(0.58431375026703F,0.54117649793625F,0.45098042488098F);
		case 140: return Color3(0.12549020349979F,0.22745099663734F,0.33725491166115F);
		case 141: return Color3(0.15294118225574F,0.27450981736183F,0.17647059261799F);
		case 143: return Color3(0.8117647767067F,0.88627457618713F,0.96862751245499F);
		case 145: return Color3(0.47450983524323F,0.53333336114883F,0.63137257099152F);
		case 146: return Color3(0.58431375026703F,0.55686277151108F,0.63921570777893F);
		case 147: return Color3(0.57647061347961F,0.52941179275513F,0.40392160415649F);
		case 148: return Color3(0.34117648005486F,0.34509804844856F,0.34117648005486F);
		case 149: return Color3(0.086274512112141F,0.11372549831867F,0.19607844948769F);
		case 150: return Color3(0.67058825492859F,0.678431391716F,0.6745098233223F);
		case 151: return Color3(0.47058826684952F,0.56470590829849F,0.50980395078659F);
		case 153: return Color3(0.58431375026703F,0.47450983524323F,0.46666669845581F);
		case 154: return Color3(0.48235297203064F,0.1803921610117F,0.1843137294054F);
		case 157: return Color3(1,0.96470594406128F,0.48235297203064F);
		case 158: return Color3(0.88235300779343F,0.64313727617264F,0.7607843875885F);
		case 168: return Color3(0.4588235616684F,0.42352944612503F,0.38431376218796F);
		case 176: return Color3(0.59215688705444F,0.41176474094391F,0.35686275362968F);
		case 178: return Color3(0.70588237047195F,0.51764708757401F,0.33333334326744F);
		case 179: return Color3(0.53725492954254F,0.52941179275513F,0.53333336114883F);
		case 180: return Color3(0.84313732385635F,0.66274511814117F,0.29411765933037F);
		case 190: return Color3(0.9764706492424F,0.83921575546265F,0.1803921610117F);
		case 191: return Color3(0.90980398654938F,0.67058825492859F,0.17647059261799F);
		case 192: return Color3(0.41176474094391F,0.25098040699959F,0.15686275064945F);
		case 193: return Color3(0.8117647767067F,0.37647062540054F,0.14117647707462F);
		case 195: return Color3(0.27450981736183F,0.40392160415649F,0.64313727617264F);
		case 196: return Color3(0.13725490868092F,0.27843138575554F,0.54509806632996F);
		case 198: return Color3(0.55686277151108F,0.258823543787F,0.52156865596771F);
		case 199: return Color3(0.38823533058167F,0.37254902720451F,0.38431376218796F);
		case 200: return Color3(0.50980395078659F,0.54117649793625F,0.3647058904171F);
		case 208: return Color3(0.89803928136826F,0.89411771297455F,0.87450987100601F);
		case 209: return Color3(0.69019609689713F,0.55686277151108F,0.26666668057442F);
		case 210: return Color3(0.43921571969986F,0.58431375026703F,0.47058826684952F);
		case 211: return Color3(0.47450983524323F,0.70980393886566F,0.70980393886566F);
		case 212: return Color3(0.6235294342041F,0.76470595598221F,0.91372555494308F);
		case 213: return Color3(0.42352944612503F,0.50588238239288F,0.71764707565308F);
		case 216: return Color3(0.56078433990479F,0.29803922772408F,0.16470588743687F);
		case 217: return Color3(0.48627454042435F,0.36078432202339F,0.27450981736183F);
		case 218: return Color3(0.58823531866074F,0.43921571969986F,0.6235294342041F);
		case 219: return Color3(0.41960787773132F,0.38431376218796F,0.60784316062927F);
		case 220: return Color3(0.65490198135376F,0.66274511814117F,0.80784320831299F);
		case 221: return Color3(0.80392163991928F,0.38431376218796F,0.59607845544815F);
		case 222: return Color3(0.89411771297455F,0.678431391716F,0.78431379795074F);
		case 223: return Color3(0.86274516582489F,0.56470590829849F,0.58431375026703F);
		case 224: return Color3(0.94117653369904F,0.83529418706894F,0.62745100259781F);
		case 225: return Color3(0.9215686917305F,0.72156864404678F,0.49803924560547F);
		case 226: return Color3(0.99215692281723F,0.91764712333679F,0.55294120311737F);
		case 232: return Color3(0.49019610881805F,0.73333334922791F,0.8666667342186F);
		case 268: return Color3(0.2039215862751F,0.16862745583057F,0.4588235616684F);
		case 1001: return Color3(0.97254908084869F,0.97254908084869F,0.97254908084869F);
		case 1002: return Color3(0.80392163991928F,0.80392163991928F,0.80392163991928F);
		case 1003: return Color3(0.066666670143604F,0.066666670143604F,0.066666670143604F);
		case 1004: return Color3(1,0,0);
		case 1005: return Color3(1,0.68627452850342F,0);
		case 1006: return Color3(0.70588237047195F,0.50196081399918F,1);
		case 1007: return Color3(0.63921570777893F,0.29411765933037F,0.29411765933037F);
		case 1008: return Color3(0.75686281919479F,0.74509805440903F,0.258823543787F);
		case 1009: return Color3(1,1,0);
		case 1010: return Color3(0,0,1);
		case 1011: return Color3(0,0.12549020349979F,0.37647062540054F);
		case 1012: return Color3(0.1294117718935F,0.32941177487373F,0.72549021244049F);
		case 1013: return Color3(0.015686275437474F,0.68627452850342F,0.92549026012421F);
		case 1014: return Color3(0.66666668653488F,0.33333334326744F,0);
		case 1015: return Color3(0.66666668653488F,0,0.66666668653488F);
		case 1016: return Color3(1,0.40000003576279F,0.80000007152557F);
		case 1017: return Color3(1,0.68627452850342F,0);
		case 1018: return Color3(0.070588238537312F,0.93333339691162F,0.83137261867523F);
		case 1019: return Color3(0,1,1);
		case 1020: return Color3(0,1,0);
		case 1021: return Color3(0.22745099663734F,0.49019610881805F,0.082352943718433F);
		case 1022: return Color3(0.49803924560547F,0.55686277151108F,0.39215689897537F);
		case 1023: return Color3(0.54901963472366F,0.35686275362968F,0.6235294342041F);
		case 1024: return Color3(0.68627452850342F,0.8666667342186F,1);
		case 1025: return Color3(1,0.78823536634445F,0.78823536634445F);
		case 1026: return Color3(0.69411766529083F,0.65490198135376F,1);
		case 1027: return Color3(0.6235294342041F,0.95294123888016F,0.91372555494308F);
		case 1028: return Color3(0.80000007152557F,1,0.80000007152557F);
		case 1029: return Color3(1,1,0.80000007152557F);
		case 1030: return Color3(1,0.80000007152557F,0.60000002384186F);
		case 1031: return Color3(0.38431376218796F,0.14509804546833F,0.81960791349411F);
		case 1032: return Color3(1,0,0.74901962280273F);
		default: return Color3::gray();
	}
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
				xml_node<> *anchoredNode=0;
				xml_node<> *shapeNode=0;
				xml_node<> *colorNode=0;
				xml_node<> *brickColorNode=0;
				xml_node<> *nameNode=0;

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
						if (xmlValue=="Anchored")
						{
							 anchoredNode = partPropNode;
						}
						if (xmlValue=="Name")
						{
							 nameNode = partPropNode;
						}
						if (xmlValue=="shape")
						{
							 shapeNode = partPropNode;
							 _legacyLoad=false;
						}
						if (xmlValue=="Color")
						{
							colorNode=partPropNode;
						}
						if (xmlValue=="BrickColor")
						{
							brickColorNode=partPropNode;
						}
						if (xmlValue=="size")
						{
							sizeNode = partPropNode;
							_legacyLoad=false;
						}
						if (xmlValue=="Part")
						{
							for (xml_node<> *featureNode = partPropNode->first_node();featureNode; featureNode = featureNode->next_sibling())
							{
								for (xml_attribute<> *attr = featureNode->first_attribute();attr; attr = attr->next_attribute())
								{
									std::string xmlName = attr->name();
									std::string xmlValue = attr->value();
									if (xmlValue=="shape")
									{
										 shapeNode = featureNode;
										 _legacyLoad=true;
									}
									if (xmlValue=="size")
									{
										sizeNode=featureNode;
										_legacyLoad=true;
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

				Enum::Shape::Value partshape = Enum::Shape::Block;
				std::string pshape = shapeNode->value();
				if (shapeNode)
				{
					if(pshape == "0" || pshape == "Ball"){
						partshape = Enum::Shape::Ball;
					}
					if(pshape == "1" || pshape == "Block"){
						partshape = Enum::Shape::Block;
					}
					if(pshape == "2" || pshape == "Cylinder"){
						partshape = Enum::Shape::Cylinder;
					}
				}

				std::string newName = nameNode->value();
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
				//sizeX=1;
				//sizeY=1;
				//sizeZ=1;
				if (_successfulLoad) {
					PartInstance* test = makePart();
					test->setParent(getWorkspace());
					test->color = Color3(R,G,B);
					test->shape = partshape;
					if(brickColorNode)
					{
						test->color = bcToRGB(atoi(brickColorNode->value()));
					}
					if(anchoredNode)
					{
						printf("AAAAAAAAAAAAAAAAAAAA %s\n", anchoredNode->value());
						test->anchored = stricmp(anchoredNode->value(), "true") == 0;
					}
					test->setSize(Vector3(sizeX,sizeY+_modY,sizeZ));
					test->setName(newName);
					CoordinateFrame cf;

					if (_legacyLoad)
					{

						cf = CoordinateFrame(Vector3(-X,Y,Z))*CoordinateFrame(Vector3(-sizeX/2,(sizeY+_modY)/2,sizeZ/2)*Matrix3(R00,R01,R02,R10,R11,R12,R20,R21,R22));
						cf.rotation = Matrix3(R00,R01,R02,R10,R11,R12,R20,R21,R22);
					}
					else
					{
						cf.translation = Vector3(X,Y,Z);
						cf.rotation = Matrix3(R00,R01,R02,R10,R11,R12,R20,R21,R22);
					}

					test->setCFrame(cf);
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

bool DataModelInstance::load(const char* filename, bool clearObjects)
{
	ifstream levelFile(filename,ios::binary);
	if (levelFile)
	{
		if (clearObjects)
			clearLevel();
		readXMLFileStream(&levelFile);
		std::string sfilename = std::string(filename);
		std::size_t begin = sfilename.rfind('\\') + 1;
		std::size_t end = sfilename.find(".rbx");
		std::string hname = sfilename.substr(begin);
		std::string tname = hname.substr(0, hname.length() - 5);
		name = tname;
		resetEngine();
		return true;
	}
	else
	{
		std::stringstream msg;
		msg << "Failed to load file:" << std::endl << filename << std::endl << strerror(errno);
		MessageBoxStr(msg.str());
		return false;
	}
}

bool DataModelInstance::readXMLFileStream(std::ifstream* file)
{
	file->seekg(0,file->end);
	int length = file->tellg();
	if (length<0)
	{
		MessageBoxStr("File is empty");
		file->close();
		return false;
	}
	file->seekg(0,file->beg);
	char * buffer = new char[length+1];
	buffer[length]=0;

	file->read(buffer,length);
	file->close();

	if (!file)
	{
		stringstream msg;
		msg << "Something went wrong." << endl << strerror(errno);
		MessageBoxStr(msg.str());
		return false;
	}
	_successfulLoad = true;
	xml_document<> doc;
	doc.parse<0>(buffer);
	xml_node<> *mainNode = doc.first_node();
	_legacyLoad=false;
	//std::string xmlName = mainNode->name();
	//node = node->first_node();
	//xmlName = node->name();
	scanXMLObject(mainNode);
	delete[] buffer;
	return true;
}

bool DataModelInstance::debugGetOpen()
{
	ifstream levelFile(_loadedFileName.c_str(),ios::binary);
	if (levelFile)
		readXMLFileStream(&levelFile);
	else
		getOpen();
	return true;
}

bool DataModelInstance::getOpen()
{
	_modY=0;
	OPENFILENAME of;
	ZeroMemory( &of , sizeof( of));
	of.lStructSize = sizeof(OPENFILENAME);
	of.lpstrFilter = "Roblox Files\0*.rbxm;*.rbxl\0\0";
	char szFile[512];
	of.lpstrFile = szFile ;
	of.lpstrFile[0]='\0';
	of.nMaxFile=500;
	of.lpstrTitle="Hello";
	of.Flags = OFN_FILEMUSTEXIST;
	ShowCursor(TRUE);
	BOOL file = GetOpenFileName(&of);
	if (file)
	{
		_loadedFileName = of.lpstrFile;
		load(of.lpstrFile,true);
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
		sprintf_s(brkc, "%d", brickCount);
		char instc[12];
		sprintf_s(instc, "%d", instCount);
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
/*Vector2 DataModelInstance::getMousePos()
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
}*/
GuiRootInstance* DataModelInstance::getGuiRoot()
{
	return guiRoot;
}


LevelInstance* DataModelInstance::getLevel()
{
	return level;
}
