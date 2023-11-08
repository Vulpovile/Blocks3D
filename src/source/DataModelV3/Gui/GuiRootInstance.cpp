#include <iomanip>
#include <sstream>
#include "G3DAll.h"
#include "DataModelV3/Gui/BaseButtonInstance.h"
#include "DataModelV3/Gui/TextButtonInstance.h"
#include "DataModelV3/Gui/ImageButtonInstance.h"
#include "DataModelV3/Gui/ToggleImageButtonInstance.h"
#include "DataModelV3/Gui/GuiRootInstance.h"
#include "DataModelV3/Gui/ImageButtonInstance.h"
#include "DataModelV3/DataModelInstance.h"
#include "StringFunctions.h"

using namespace B3D;

#ifndef _DEBUG
	#if _MSC_VER== 1310
		#define VS03_WORKAROUND &
	#else
		#define VS03_WORKAROUND
	#endif
#else
	#define VS03_WORKAROUND
#endif

ImageButtonInstance* GuiRootInstance::makeImageButton(G3D::TextureRef newImage = NULL, G3D::TextureRef overImage = NULL, G3D::TextureRef downImage = NULL, G3D::TextureRef disableImage = NULL)
{
	//Oh come on
	ImageButtonInstance* part = new ImageButtonInstance(newImage,overImage, downImage, disableImage);
//	instances.push_back(part);
//	instances_2D.push_back(part);
	return part;
}

// Modnark here, I'm not a fan of having these functions, but until we make a proper "factory" it'll have to do.
TextButtonInstance* makeBaseTextButton(std::string title, Vector2 boxBegin, Vector2 boxEnd) {
	TextButtonInstance* button = new TextButtonInstance();
	button->boxBegin = boxBegin;
	button->boxEnd = boxEnd;
	button->title = title;
	button->font = GFont::fromFile(GetFileInPath("/content/font/lighttrek.fnt"));
	return button;
}

TextButtonInstance* makeMenuTextButton(std::string title, Vector2 boxBegin, Vector2 boxEnd) {
	TextButtonInstance* button = makeBaseTextButton(title, boxBegin, boxEnd);
	button->floatBottom = true;
	button->textColor = Color3(0,255,255);
	button->textOutlineColor = Color4::clear();
	button->fontLocationRelativeTo = Vector2(10, 3);
	button->boxOutlineColorOvr = Color3(0,255,255);
	button->boxColorDn = Color4(button->boxColor.r,button->boxColor.g,button->boxColor.b, 0.2F);
	button->setAllColorsSame();
	//button->setButtonListener(toolbar);
	//toolbar.addButtonRef(button);	
	return button;
}

TextButtonInstance* makeToolbarTextButton(std::string title, std::string name, Vector2 boxBegin, Vector2 boxEnd) {
	TextButtonInstance* button = makeBaseTextButton(title, boxBegin, boxEnd);
	button->textColor = Color3::white();
	button->boxColor = Color4::clear();
	button->textOutlineColor = Color4(0.5F,0.5F,0.5F,0.5F);
	button->name = name;
	button->textSize = 16;
	button->fontLocationRelativeTo = Vector2(10, 0);
	button->boxColorOvr = Color4(0.6F,0.6F,0.6F,0.4F);
	button->setAllColorsSame();
	//button->setButtonListener(menuListener);
	return button;
}

TextButtonInstance* makeLeftMenuTextButton(std::string title, Vector2 boxBegin, Vector2 boxEnd) {
	TextButtonInstance* button = makeBaseTextButton(title, boxBegin, boxEnd);
	button->textOutlineColor = Color4(0.5F,0.5F,0.5F,0.5F);
	button->textColor = Color3(0,1,1);
	button->boxColor = Color4::clear();
	button->textSize = 12;
	button->name = title;	
	button->textColorDis = Color3(0.8F,0.8F,0.8F);
	button->boxColorOvr = Color4(0.6F,0.6F,0.6F,0.4F);
	button->fontLocationRelativeTo = Vector2(10, 0);
	button->setAllColorsSame();
	//button->setButtonListener(gud);
	return button;
}

TextButtonInstance* GuiRootInstance::makeTextButton()
{
	TextButtonInstance* part = new TextButtonInstance();
	return part;
}
GuiRootInstance::GuiRootInstance() : _message(""), _messageTime(0)
{
	//AAAAAAA
	fntdominant = GFont::fromFile(GetFileInPath("/content/font/dominant.fnt"));
	fntlighttrek = GFont::fromFile(GetFileInPath("/content/font/lighttrek.fnt"));
	_hideGui = false;

	//Bottom Left
	TextButtonInstance* button = makeMenuTextButton("Hopper", Vector2(0, -24), Vector2(80, 0));
	button->setParent(this);

	button = makeMenuTextButton("Controller", Vector2(0, -48), Vector2(80, -24));
	button->setParent(this);

	button = makeMenuTextButton("Color", Vector2(0, -72), Vector2(80, -48));
	button->setParent(this);

	button = makeMenuTextButton("Surface", Vector2(0, -96), Vector2(80, -72));
	button->setParent(this);

	button = makeMenuTextButton("Model", Vector2(0, -120), Vector2(80, -96));
	button->setParent(this);

	//Top bar
	button = makeToolbarTextButton("File", "file", Vector2(0, 0), Vector2(125, 25));
	button->setParent(this);

	button = makeToolbarTextButton("Edit", "edit", Vector2(125, 0), Vector2(250, 25));
	button->setParent(this);

	button = makeToolbarTextButton("View", "view", Vector2(250, 0), Vector2(375, 25));
	button->setParent(this);

	button = makeToolbarTextButton("Insert", "insert", Vector2(375, 0), Vector2(500, 25));
	button->setParent(this);

	button = makeToolbarTextButton("Format", "format", Vector2(500, 0), Vector2(625, 25));
	button->setParent(this);

	//Menu
	button = makeLeftMenuTextButton("Group", Vector2(0, 215), Vector2(80, 235));
	button->setParent(this);
	
	button = makeLeftMenuTextButton("UnGroup", Vector2(0, 240), Vector2(80, 260));
	button->setParent(this);

	button = makeLeftMenuTextButton("Duplicate", Vector2(0, 265), Vector2(80, 285));
	button->setParent(this);

	button = makeBaseTextButton("MENU", Vector2(0,332), Vector2(80,352));
	button->textOutlineColor = Color4(0.5F,0.5F,0.5F,0.5F);
	button->textColor = Color3::white();
	button->boxColor = Color4::clear();
	button->textSize = 14;
	button->setAllColorsSame();
	button->boxColorOvr = Color4(0.6F,0.6F,0.6F,0.4F);
	button->font = fntlighttrek;
	button->fontLocationRelativeTo = Vector2(10, 0);
	button->setParent(this);
	button->name = "MENU";
	//TODO Define Action
	//button->setButtonListener(menuListener);

	ImageButtonInstance* instance = new ToggleImageButtonInstance(
		Texture::fromFile(VS03_WORKAROUND GetFileInPath("/content/images/Run.png")),
		Texture::fromFile(VS03_WORKAROUND GetFileInPath("/content/images/Run_ovr.png")),
		Texture::fromFile(VS03_WORKAROUND GetFileInPath("/content/images/Run_dn.png")),
		NULL,		
		Texture::fromFile(VS03_WORKAROUND GetFileInPath("/content/images/Stop.png")),
		Texture::fromFile(VS03_WORKAROUND GetFileInPath("/content/images/Stop_ovr.png")),
		Texture::fromFile(VS03_WORKAROUND GetFileInPath("/content/images/Stop_dn.png"))
		);
	//TODO Define Action
	//instance->setButtonListener(menuListener);
	instance->name = "go";
	instance->size = Vector2(65,65);
	instance->position = Vector2(6.5, 25);
	instance->setParent(this);


	instance = makeImageButton(
		Texture::fromFile(VS03_WORKAROUND GetFileInPath("/content/images/ArrowTool.png")),
		Texture::fromFile(VS03_WORKAROUND GetFileInPath("/content/images/ArrowTool_ovr.png")),
		Texture::fromFile(VS03_WORKAROUND GetFileInPath("/content/images/ArrowTool_dn.png")),
		Texture::fromFile(VS03_WORKAROUND GetFileInPath("/content/images/ArrowTool_ds.png")));
	instance->size = Vector2(50,50);
	instance->position = Vector2(15, 90);
	instance->setParent(this);
	instance->name = "Cursor";
	//TODO Define Action
	//instance->setButtonListener(msl);

	instance = makeImageButton(Texture::fromFile(VS03_WORKAROUND GetFileInPath("/content/images/ScaleTool.png")),Texture::fromFile(VS03_WORKAROUND GetFileInPath("/content/images/ScaleTool_ovr.png")),Texture::fromFile(VS03_WORKAROUND GetFileInPath("/content/images/ScaleTool_dn.png")),Texture::fromFile(VS03_WORKAROUND GetFileInPath("/content/images/ScaleTool_ds.png")));
	instance->size = Vector2(40,40);
	instance->position = Vector2(0, 140);
	instance->setParent(this);
	instance->name = "Resize";
	//TODO Define Action
	//instance->setButtonListener(msl);
	

	instance = makeImageButton(
		Texture::fromFile(VS03_WORKAROUND GetFileInPath("/content/images/MoveTool.png")),
		Texture::fromFile(VS03_WORKAROUND GetFileInPath("/content/images/MoveTool_ovr.png")),
		Texture::fromFile(VS03_WORKAROUND GetFileInPath("/content/images/MoveTool_dn.png")),
		Texture::fromFile(VS03_WORKAROUND GetFileInPath("/content/images/MoveTool_ds.png")));
	instance->size = Vector2(40,40);
	instance->position = Vector2(40, 140);
	instance->setParent(this);
	instance->name = "Arrows";
	//TODO Define Action
	//instance->setButtonListener(msl);

	instance = makeImageButton(
		Texture::fromFile(VS03_WORKAROUND GetFileInPath("/content/images/SelectionRotate.png")),
		Texture::fromFile(VS03_WORKAROUND GetFileInPath("/content/images/SelectionRotate_ovr.png")),
		NULL,
		Texture::fromFile(VS03_WORKAROUND GetFileInPath("/content/images/SelectionRotate_ds.png")));
	instance->size = Vector2(30,30);
	instance->position = Vector2(10, 175);
	instance->setParent(this);
	instance->name = "Rotate";
	//TODO Define Action
	//instance->setButtonListener(rbl);

	instance = makeImageButton(
		Texture::fromFile(VS03_WORKAROUND GetFileInPath("/content/images/SelectionTilt.png")),
		Texture::fromFile(VS03_WORKAROUND GetFileInPath("/content/images/SelectionTilt_ovr.png")),
		NULL,
		Texture::fromFile(VS03_WORKAROUND GetFileInPath("/content/images/SelectionTilt_ds.png")));
	instance->size = Vector2(30,30);
	instance->position = Vector2(40, 175);
	instance->setParent(this);
	instance->name = "Tilt";
	//TODO Define Action
	//instance->setButtonListener(rbl);


	instance = makeImageButton(
		Texture::fromFile(VS03_WORKAROUND GetFileInPath("/content/images/Delete.png")),
		Texture::fromFile(VS03_WORKAROUND GetFileInPath("/content/images/Delete_ovr.png")),
		Texture::fromFile(VS03_WORKAROUND GetFileInPath("/content/images/Delete_dn.png")),
		Texture::fromFile(VS03_WORKAROUND GetFileInPath("/content/images/Delete_ds.png")));
	instance->size = Vector2(40,46);
	instance->position = Vector2(20, 284);
	instance->setParent(this);
	instance->name = "Delete";
	//TODO Define Action
	//instance->setButtonListener(delet);

	instance = makeImageButton(
		Texture::fromFile(VS03_WORKAROUND GetFileInPath("/content/images/CameraZoomIn.png")),
		Texture::fromFile(VS03_WORKAROUND GetFileInPath("/content/images/CameraZoomIn_ovr.png")),
		Texture::fromFile(VS03_WORKAROUND GetFileInPath("/content/images/CameraZoomIn_dn.png")));
	instance->size = Vector2(34,25);
	instance->floatBottom = true;
	instance->floatRight = true;
	instance->position = Vector2(-77, -90);
	instance->setParent(this);
	instance->name = "ZoomIn";
	//TODO Define Action
	//instance->setButtonListener(cam);

	instance = makeImageButton(
		Texture::fromFile(VS03_WORKAROUND GetFileInPath("/content/images/CameraZoomOut.png")),
		Texture::fromFile(VS03_WORKAROUND GetFileInPath("/content/images/CameraZoomOut_ovr.png")),
		Texture::fromFile(VS03_WORKAROUND GetFileInPath("/content/images/CameraZoomOut_dn.png")));
	instance->size = Vector2(34,26);
	instance->floatBottom = true;
	instance->floatRight = true;
	instance->position = Vector2(-77, -31);
	instance->setParent(this);
	instance->name = "ZoomOut";
	//TODO Define Action
	//instance->setButtonListener(cam);

	instance = makeImageButton(
		Texture::fromFile(VS03_WORKAROUND GetFileInPath("/content/images/CameraPanLeft.png")),
		Texture::fromFile(VS03_WORKAROUND GetFileInPath("/content/images/CameraPanLeft_ovr.png")),
		Texture::fromFile(VS03_WORKAROUND GetFileInPath("/content/images/CameraPanLeft_dn.png")));
	instance->size = Vector2(34,34);
	instance->floatBottom = true;
	instance->floatRight = true;
	instance->position = Vector2(-110, -50);
	instance->setParent(this);
	instance->name = "PanLeft";
	//TODO Define Action
	//instance->setButtonListener(cam);

	instance = makeImageButton(
		Texture::fromFile(VS03_WORKAROUND GetFileInPath("/content/images/CameraPanRight.png")),
		Texture::fromFile(VS03_WORKAROUND GetFileInPath("/content/images/CameraPanRight_ovr.png")),
		Texture::fromFile(VS03_WORKAROUND GetFileInPath("/content/images/CameraPanRight_dn.png")));
	instance->size = Vector2(34,34);
	instance->floatBottom = true;
	instance->floatRight = true;
	instance->position = Vector2(-45, -50);
	instance->setParent(this);
	instance->name = "PanRight";
	//TODO Define Action
	//instance->setButtonListener(cam);

	instance = makeImageButton(
		Texture::fromFile(VS03_WORKAROUND GetFileInPath("/content/images/CameraCenter.png")),
		Texture::fromFile(VS03_WORKAROUND GetFileInPath("/content/images/CameraCenter_ovr.png")),
		Texture::fromFile(VS03_WORKAROUND GetFileInPath("/content/images/CameraCenter_dn.png")));
	instance->size = Vector2(34,20);
	instance->floatBottom = true;
	instance->floatRight = true;
	instance->position = Vector2(-77, -60);
	instance->setParent(this);
	instance->name = "CenterCam";
	//TODO Define Action
	//instance->setButtonListener(cam);

	instance = makeImageButton(
		Texture::fromFile(VS03_WORKAROUND GetFileInPath("/content/images/CameraTiltUp.png")),
		Texture::fromFile(VS03_WORKAROUND GetFileInPath("/content/images/CameraTiltUp_ovr.png")),
		Texture::fromFile(VS03_WORKAROUND GetFileInPath("/content/images/CameraTiltUp_dn.png")));
	instance->size = Vector2(24,24);
	instance->floatBottom = true;
	instance->floatRight = true;
	instance->position = Vector2(-105, -75);
	instance->setParent(this);
	instance->name = "TiltUp";
	//TODO Define Action
	//instance->setButtonListener(cam);

	instance = makeImageButton(
		Texture::fromFile(VS03_WORKAROUND GetFileInPath("/content/images/CameraTiltDown.png")),
		Texture::fromFile(VS03_WORKAROUND GetFileInPath("/content/images/CameraTiltDown_ovr.png")),
		Texture::fromFile(VS03_WORKAROUND GetFileInPath("/content/images/CameraTiltDown_dn.png")));
	instance->size = Vector2(24,24);
	instance->floatBottom = true;
	instance->floatRight = true;
	instance->position = Vector2(-40, -75);
	instance->setParent(this);
	instance->name = "TiltDown";
	//TODO Define Action
	//instance->setButtonListener(cam);
}


void GuiRootInstance::drawButtons(RenderDevice* rd)
{
	rd->pushState();
	rd->beforePrimitive();
			//this->render(rd);
	rd->afterPrimitive();
	rd->popState();
}

void GuiRootInstance::setDebugMessage(std::string msg, G3D::RealTime msgTime)
{
	_messageTime = msgTime;
	_message = msg;
}

//void GuiRootInstance::render(G3D::RenderDevice* renderDevice) {}

void GuiRootInstance::renderGUI(G3D::RenderDevice* rd, double fps)
{
	if(_hideGui) return;
	//TODO--Move these to their own instance

	std::stringstream stream;
	stream << std::fixed << std::setprecision(1) << parentDataModel->getLevel()->timer.getValue();
	fntdominant->draw2D(rd, "Timer: " + stream.str(), Vector2(rd->getWidth() - 120, 25), 20, Color3::fromARGB(0x81C518), Color3::black());
	fntdominant->draw2D(rd, "Score: " + Convert(parentDataModel->getLevel()->score.getValue()), Vector2(rd->getWidth() - 120, 50), 20, Color3::fromARGB(0x81C518), Color3::black());
	//FPS
#ifdef _DEBUG
	stream.str("");
    stream.clear();
    stream << std::fixed << std::setprecision(3) << fps;
    fntdominant->draw2D(rd, "FPS: " + stream.str(), Vector2(120, 25), 10, Color3::fromARGB(0xFFFF00), Color3::black());
#endif
	//GUI Boxes	
	Draw::box(G3D::Box(Vector3(0,25,0),Vector3(80,355,0)),rd,Color4(0.6F,0.6F,0.6F,0.4F), Color4(0,0,0,0));
	Draw::box(G3D::Box(Vector3(rd->getWidth() - 120,rd->getHeight() - 117,0),Vector3(rd->getWidth(),rd->getHeight(),0)),rd,Color4(0.6F,0.6F,0.6F,0.4F), Color4(0,0,0,0));
	
	//Camera menu title
	fntlighttrek->draw2D(rd, "CameraMenu", Vector2(rd->getWidth()-(fntlighttrek->get2DStringBounds("CameraMenu", 14).x+1),rd->getHeight() - 120), 14, Color3::white(), Color4(0.5F,0.5F,0.5F,0.5F));

	//Tools menu
	Draw::box(G3D::Box(Vector3(5, 210,0),Vector3(75, 210,0)),rd,Color4(0.6F,0.6F,0.6F,0.4F), Color4(0.6F,0.6F,0.6F,0.4F));
	

	
	//drawButtons(rd);
	if(System::time() - 3 < _messageTime)
	{
		fntdominant->draw2D(rd, _message, Vector2((rd->getWidth()/2)-(fntdominant->get2DStringBounds(_message, 20).x/2),(rd->getHeight()/2)-(fntdominant->get2DStringBounds(_message, 20).y/2)), 20, Color3::yellow(), Color3::black());
	}

	parentDataModel->drawMessage(rd);
	render(rd);
}

bool GuiRootInstance::mouseInGUI(G3D::RenderDevice* renderDevice,int x,int y)
{
										//What???
	std::vector<Instance*> instances_2D = parentDataModel->getGuiRoot()->getAllChildren();
	for(size_t i = 0; i < instances_2D.size(); i++)
	{
		if(BaseButtonInstance* button = dynamic_cast<BaseButtonInstance*>(instances_2D.at(i)))
		{
			if(button->mouseInButton(x,y, renderDevice))
			{
				return true;
			}
		}
	}
	return false;
}
//Oh eww...
void GuiRootInstance::update()
{		
	Instance * obj6 = this->findFirstChild("Delete");
	Instance * obj = this->findFirstChild("Duplicate");
	Instance * obj2 = this->findFirstChild("Group");
	Instance * obj3 = this->findFirstChild("UnGroup");
	Instance * obj4 = this->findFirstChild("Rotate");
	Instance * obj5 = this->findFirstChild("Tilt");

	SelectionService* getSelectionService = parentDataModel->getSelectionService();

	if(obj != NULL && obj2 != NULL && obj3 != NULL && obj4 !=NULL && obj5 != NULL && obj6 != NULL)
	{
		BaseButtonInstance* button = (BaseButtonInstance*)obj;
		BaseButtonInstance* button2 = (BaseButtonInstance*)obj2;
		BaseButtonInstance* button3 = (BaseButtonInstance*)obj3;
		BaseButtonInstance* button4 = (BaseButtonInstance*)obj4;
		BaseButtonInstance* button5 = (BaseButtonInstance*)obj5;
		BaseButtonInstance* button6 = (BaseButtonInstance*)obj6;
		button->disabled = true;
		button2->disabled = true;
		button3->disabled = true;
		button4->disabled = true;
		button5->disabled = true;
		button6->disabled = true;
		for(size_t i = 0; i < getSelectionService->getSelection().size(); i++)
			if(getSelectionService->getSelection()[i]->canDelete)
			{
				button->disabled = false;
				button4->disabled = false;
				button5->disabled = false;
				button6->disabled = false;
				

				if (getSelectionService->getSelection().size() > 1){
					button2->disabled = false;
				}

				if (dynamic_cast<GroupInstance*>(getSelectionService->getSelection()[i])){
					button3->disabled = false;
				}

				break;
			}
	}
}

GuiRootInstance::~GuiRootInstance()
{
}

void GuiRootInstance::onMouseLeftUp(G3D::RenderDevice* renderDevice, int x,int y)
{
	std::vector<Instance*> instances_2D = this->getAllChildren();
	for(size_t i = 0; i < instances_2D.size(); i++)
	{
		if(BaseButtonInstance* button = dynamic_cast<BaseButtonInstance*>(instances_2D[i]))
		{
			if(button->mouseInButton(x, y, renderDevice))
			{
				button->onMouseClick();
			}
		}
	}
}

void GuiRootInstance::hideGui(bool doHide) {
	_hideGui = doHide;
}