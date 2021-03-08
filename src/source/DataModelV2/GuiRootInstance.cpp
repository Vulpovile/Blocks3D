#include <iomanip>
#include <sstream>
#include "G3DAll.h"
#include "DataModelV2/BaseButtonInstance.h"
#include "DataModelV2/TextButtonInstance.h"
#include "DataModelV2/ImageButtonInstance.h"
#include "DataModelV2/ToggleImageButtonInstance.h"
#include "DataModelV2/GuiRootInstance.h"
#include "DataModelV2/ImageButtonInstance.h"
#include "Globals.h"
#include "StringFunctions.h"

#include "Listener/GUDButtonListener.h"
#include "Listener/ModeSelectionListener.h"
#include "Listener/MenuButtonListener.h"
#include "Listener/RotateButtonListener.h"
#include "Listener/CameraButtonListener.h"
#include "Listener/DeleteListener.h"
#include "Listener/ToolbarListener.h"


ImageButtonInstance* GuiRootInstance::makeImageButton(G3D::TextureRef newImage = NULL, G3D::TextureRef overImage = NULL, G3D::TextureRef downImage = NULL, G3D::TextureRef disableImage = NULL)
{
	ImageButtonInstance* part = new ImageButtonInstance(newImage,overImage, downImage, disableImage);
//	instances.push_back(part);
//	instances_2D.push_back(part);
	return part;
}

TextButtonInstance* GuiRootInstance::makeTextButton()
{
	TextButtonInstance* part = new TextButtonInstance();
	return part;
}
ToolbarListener * toolbar;
GuiRootInstance::GuiRootInstance() : _message(""), _messageTime(0)
{
	toolbar = new ToolbarListener();
	toolbar->doDelete = false;
	g_fntdominant = GFont::fromFile(GetFileInPath("/content/font/dominant.fnt"));
	g_fntlighttrek = GFont::fromFile(GetFileInPath("/content/font/lighttrek.fnt"));

	//Bottom Left
	TextButtonInstance* button = makeTextButton();
	button->boxBegin = Vector2(0, -24);
	button->boxEnd = Vector2(80, 0);
	button->floatBottom = true;
	button->setParent(this);
	button->font = g_fntlighttrek;
	button->textColor = Color3(0,255,255);
	button->textOutlineColor = Color4::clear();
	button->title = "Hopper";
	button->fontLocationRelativeTo = Vector2(10, 3);
	button->setAllColorsSame();
	button->boxOutlineColorOvr = Color3(0,255,255);
	button->boxColorDn = Color4(button->boxColor.r,button->boxColor.g,button->boxColor.b, 0.2F);
	button->setButtonListener(toolbar);
	toolbar->addButtonRef(button);

	
	button = makeTextButton();
	button->boxBegin = Vector2(0, -48);
	button->boxEnd = Vector2(80, -24);
	button->floatBottom = true;
	button->setParent(this);
	button->font = g_fntlighttrek;
	button->textColor = Color3(0,255,255);
	button->textOutlineColor = Color4::clear();
	button->title = "Controller";
	button->fontLocationRelativeTo = Vector2(10, 3);
	button->setAllColorsSame();
	button->boxOutlineColorOvr = Color3(0,255,255);
	button->boxColorDn = Color4(button->boxColor.r,button->boxColor.g,button->boxColor.b, 0.2F);
	button->setButtonListener(toolbar);
	toolbar->addButtonRef(button);

	button = makeTextButton();
	button->boxBegin = Vector2(0, -72);
	button->boxEnd = Vector2(80, -48);
	button->floatBottom = true;
	button->setParent(this);
	button->font = g_fntlighttrek;
	button->textColor = Color3(0,255,255);
	button->textOutlineColor = Color4::clear();
	button->title = "Color";
	button->fontLocationRelativeTo = Vector2(10, 3);
	button->setAllColorsSame();
	button->boxOutlineColorOvr = Color3(0,255,255);
	button->boxColorDn = Color4(button->boxColor.r,button->boxColor.g,button->boxColor.b, 0.2F);
	button->setButtonListener(toolbar);
	toolbar->addButtonRef(button);

	button = makeTextButton();
	button->boxBegin = Vector2(0, -96);
	button->boxEnd = Vector2(80, -72);
	button->floatBottom = true;
	button->setParent(this);
	button->font = g_fntlighttrek;
	button->textColor = Color3(0,255,255);
	button->textOutlineColor = Color4::clear();
	button->title = "Surface";
	button->fontLocationRelativeTo = Vector2(10, 3);
	button->setAllColorsSame();
	button->boxOutlineColorOvr = Color3(0,255,255);
	button->boxColorDn = Color4(button->boxColor.r,button->boxColor.g,button->boxColor.b, 0.2F);
	button->setButtonListener(toolbar);
	toolbar->addButtonRef(button);

	button = makeTextButton();
	button->boxBegin = Vector2(0, -120);
	button->boxEnd = Vector2(80, -96);
	button->floatBottom = true;
	button->setParent(this);
	button->font = g_fntlighttrek;
	button->textColor = Color3(0,255,255);
	button->title = "Model";
	button->selected = true;
	button->fontLocationRelativeTo = Vector2(10, 3);
	button->setAllColorsSame();
	button->boxOutlineColorOvr = Color3(0,255,255);
	button->boxColorDn = Color4(button->boxColor.r,button->boxColor.g,button->boxColor.b, 0.2F);
	button->setButtonListener(toolbar);
	toolbar->addButtonRef(button);

	//Top bar
	button = makeTextButton();
	button->boxBegin = Vector2(0, 0);
	button->boxEnd = Vector2(125, 25);
	button->setParent(this);
	button->font = g_fntlighttrek;
	button->textColor = Color3::white();
	button->boxColor = Color4::clear();
	button->textOutlineColor = Color4(0.5F,0.5F,0.5F,0.5F);
	button->title = "File";
	button->textSize = 16;
	button->fontLocationRelativeTo = Vector2(10, 0);
	button->setAllColorsSame();
	button->boxColorOvr = Color4(0.6F,0.6F,0.6F,0.4F);
	button->name = "file";
	button->setButtonListener(new MenuButtonListener());

	button = makeTextButton();
	button->boxBegin = Vector2(125, 0);
	button->boxEnd = Vector2(250, 25);
	button->setParent(this);
	button->font = g_fntlighttrek;
	button->textColor = Color3::white();
	button->boxColor = Color4::clear();
	button->textOutlineColor = Color4(0.5F,0.5F,0.5F,0.5F);
	button->title = "Edit";
	button->textSize = 16;
	button->fontLocationRelativeTo = Vector2(10, 0);
	button->setAllColorsSame();
	button->boxColorOvr = Color4(0.6F,0.6F,0.6F,0.4F);

	button = makeTextButton();
	button->boxBegin = Vector2(250, 0);
	button->boxEnd = Vector2(375, 25);
	button->setParent(this);
	button->font = g_fntlighttrek;
	button->textColor = Color3::white();
	button->boxColor = Color4::clear();
	button->textOutlineColor = Color4(0.5F,0.5F,0.5F,0.5F);
	button->title = "View";
	button->textSize = 16;
	button->fontLocationRelativeTo = Vector2(10, 0);
	button->setAllColorsSame();
	button->boxColorOvr = Color4(0.6F,0.6F,0.6F,0.4F);

	button = makeTextButton();
	button->boxBegin = Vector2(375, 0);
	button->boxEnd = Vector2(500, 25);
	button->setParent(this);
	button->font = g_fntlighttrek;
	button->textColor = Color3::white();
	button->boxColor = Color4::clear();
	button->textOutlineColor = Color4(0.5F,0.5F,0.5F,0.5F);
	button->title = "Insert";
	button->textSize = 16;
	button->fontLocationRelativeTo = Vector2(10, 0);
	button->setAllColorsSame();
	button->boxColorOvr = Color4(0.6F,0.6F,0.6F,0.4F);

	button = makeTextButton();
	button->boxBegin = Vector2(500, 0);
	button->boxEnd = Vector2(625, 25);
	button->setParent(this);
	button->font = g_fntlighttrek;
	button->textColor = Color3::white();
	button->boxColor = Color4::clear();
	button->textOutlineColor = Color4(0.5F,0.5F,0.5F,0.5F);
	button->title = "Format";
	button->textSize = 16;
	button->fontLocationRelativeTo = Vector2(10, 0);
	button->setAllColorsSame();
	button->boxColorOvr = Color4(0.6F,0.6F,0.6F,0.4F);


	//Menu
	button = makeTextButton();
	button->boxBegin = Vector2(0,215);
	button->boxEnd = Vector2(80,235);
	button->textOutlineColor = Color4(0.5F,0.5F,0.5F,0.5F);
	button->textColor = Color3::white();
	button->boxColor = Color4::clear();
	button->textSize = 12;
	button->title = "Group";
	button->name = "Group";
	button->setAllColorsSame();	
	button->textColorDis = Color3(0.8F,0.8F,0.8F);
	button->font = g_fntlighttrek;
	button->fontLocationRelativeTo = Vector2(10, 0);
	button->setParent(this);
	button->setButtonListener(new GUDButtonListener());

	button = makeTextButton();
	button->boxBegin = Vector2(0,240);
	button->boxEnd = Vector2(80,260);
	button->textOutlineColor = Color4(0.5F,0.5F,0.5F,0.5F);
	button->textColor = Color3::white();
	button->boxColor = Color4::clear();
	button->textSize = 12;
	button->title = "UnGroup";
	button->name = "UnGroup";
	button->setAllColorsSame();
	button->textColorDis = Color3(0.8F,0.8F,0.8F);
	button->font = g_fntlighttrek;
	button->fontLocationRelativeTo = Vector2(10, 0);
	button->setParent(this);
	button->setButtonListener(new GUDButtonListener());

	button = makeTextButton();
	button->boxBegin = Vector2(0,265);
	button->boxEnd = Vector2(80,285);
	button->textOutlineColor = Color4(0.5F,0.5F,0.5F,0.5F);
	button->textColor = Color3::white();
	button->boxColor = Color4::clear();
	button->textSize = 12;
	button->title = "Duplicate";
	button->setAllColorsSame();
	button->textColorDis = Color3(0.8F,0.8F,0.8F);
	button->font = g_fntlighttrek;
	button->fontLocationRelativeTo = Vector2(10, 0);
	button->setParent(this);
	button->name = "Duplicate";
	button->setButtonListener(new GUDButtonListener());

	ImageButtonInstance* instance = new ToggleImageButtonInstance(
		Texture::fromFile(GetFileInPath("/content/images/Run.png")),
		Texture::fromFile(GetFileInPath("/content/images/Run_ovr.png")),
		Texture::fromFile(GetFileInPath("/content/images/Run_dn.png")),
		NULL,		
		Texture::fromFile(GetFileInPath("/content/images/Stop.png")),
		Texture::fromFile(GetFileInPath("/content/images/Stop_ovr.png")),
		Texture::fromFile(GetFileInPath("/content/images/Stop_dn.png"))
		);
	instance->setButtonListener(new MenuButtonListener());
	instance->name = "go";
	instance->size = Vector2(65,65);
	instance->position = Vector2(6.5, 25);
	instance->setParent(this);


	instance = makeImageButton(
		Texture::fromFile(GetFileInPath("/content/images/ArrowTool.png")),
		Texture::fromFile(GetFileInPath("/content/images/ArrowTool_ovr.png")),
		Texture::fromFile(GetFileInPath("/content/images/ArrowTool_dn.png")),
		Texture::fromFile(GetFileInPath("/content/images/ArrowTool_ds.png")));
	instance->size = Vector2(50,50);
	instance->position = Vector2(15, 90);
	instance->setParent(this);
	instance->name = "Cursor";
	instance->setButtonListener(new ModeSelectionListener());

	instance = makeImageButton(Texture::fromFile(GetFileInPath("/content/images/ScaleTool.png")),Texture::fromFile(GetFileInPath("/content/images/ScaleTool_ovr.png")),Texture::fromFile(GetFileInPath("/content/images/ScaleTool_dn.png")),Texture::fromFile(GetFileInPath("/content/images/ScaleTool_ds.png")));
	instance->size = Vector2(40,40);
	instance->position = Vector2(0, 140);
	instance->setParent(this);
	instance->name = "Resize";
	instance->setButtonListener(new ModeSelectionListener());
	

	instance = makeImageButton(
		Texture::fromFile(GetFileInPath("/content/images/MoveTool.png")),
		Texture::fromFile(GetFileInPath("/content/images/MoveTool_ovr.png")),
		Texture::fromFile(GetFileInPath("/content/images/MoveTool_dn.png")),
		Texture::fromFile(GetFileInPath("/content/images/MoveTool_ds.png")));
	instance->size = Vector2(40,40);
	instance->position = Vector2(40, 140);
	instance->setParent(this);
	instance->name = "Arrows";
	instance->setButtonListener(new ModeSelectionListener());

	instance = makeImageButton(
		Texture::fromFile(GetFileInPath("/content/images/SelectionRotate.png")),
		Texture::fromFile(GetFileInPath("/content/images/SelectionRotate_ovr.png")),
		NULL,
		Texture::fromFile(GetFileInPath("/content/images/SelectionRotate_ds.png")));
	instance->size = Vector2(30,30);
	instance->position = Vector2(10, 175);
	instance->setParent(this);
	instance->name = "Rotate";
	instance->setButtonListener(new RotateButtonListener());

	instance = makeImageButton(
		Texture::fromFile(GetFileInPath("/content/images/SelectionTilt.png")),
		Texture::fromFile(GetFileInPath("/content/images/SelectionTilt_ovr.png")),
		NULL,
		Texture::fromFile(GetFileInPath("/content/images/SelectionTilt_ds.png")));
	instance->size = Vector2(30,30);
	instance->position = Vector2(40, 175);
	instance->setParent(this);
	instance->name = "Tilt";
	instance->setButtonListener(new RotateButtonListener());


	instance = makeImageButton(
		Texture::fromFile(GetFileInPath("/content/images/Delete.png")),
		Texture::fromFile(GetFileInPath("/content/images/Delete_ovr.png")),
		Texture::fromFile(GetFileInPath("/content/images/Delete_dn.png")),
		Texture::fromFile(GetFileInPath("/content/images/Delete_ds.png")));
	instance->size = Vector2(40,46);
	instance->position = Vector2(20, 284);
	instance->setParent(this);
	instance->name = "Delete";
	instance->setButtonListener(new DeleteListener());

	instance = makeImageButton(
		Texture::fromFile(GetFileInPath("/content/images/CameraZoomIn.png")),
		Texture::fromFile(GetFileInPath("/content/images/CameraZoomIn_ovr.png")),
		Texture::fromFile(GetFileInPath("/content/images/CameraZoomIn_dn.png")));
	instance->size = Vector2(34,25);
	instance->floatBottom = true;
	instance->floatRight = true;
	instance->position = Vector2(-77, -90);
	instance->setParent(this);
	instance->name = "ZoomIn";
	instance->setButtonListener(new CameraButtonListener());

	instance = makeImageButton(
		Texture::fromFile(GetFileInPath("/content/images/CameraZoomOut.png")),
		Texture::fromFile(GetFileInPath("/content/images/CameraZoomOut_ovr.png")),
		Texture::fromFile(GetFileInPath("/content/images/CameraZoomOut_dn.png")));
	instance->size = Vector2(34,26);
	instance->floatBottom = true;
	instance->floatRight = true;
	instance->position = Vector2(-77, -31);
	instance->setParent(this);
	instance->name = "ZoomOut";
	instance->setButtonListener(new CameraButtonListener());

	instance = makeImageButton(
		Texture::fromFile(GetFileInPath("/content/images/CameraPanLeft.png")),
		Texture::fromFile(GetFileInPath("/content/images/CameraPanLeft_ovr.png")),
		Texture::fromFile(GetFileInPath("/content/images/CameraPanLeft_dn.png")));
	instance->size = Vector2(34,34);
	instance->floatBottom = true;
	instance->floatRight = true;
	instance->position = Vector2(-110, -50);
	instance->setParent(this);
	instance->name = "PanLeft";
	instance->setButtonListener(new CameraButtonListener());

	instance = makeImageButton(
		Texture::fromFile(GetFileInPath("/content/images/CameraPanRight.png")),
		Texture::fromFile(GetFileInPath("/content/images/CameraPanRight_ovr.png")),
		Texture::fromFile(GetFileInPath("/content/images/CameraPanRight_dn.png")));
	instance->size = Vector2(34,34);
	instance->floatBottom = true;
	instance->floatRight = true;
	instance->position = Vector2(-45, -50);
	instance->setParent(this);
	instance->name = "PanRight";
	instance->setButtonListener(new CameraButtonListener());

	instance = makeImageButton(
		Texture::fromFile(GetFileInPath("/content/images/CameraCenter.png")),
		Texture::fromFile(GetFileInPath("/content/images/CameraCenter_ovr.png")),
		Texture::fromFile(GetFileInPath("/content/images/CameraCenter_dn.png")));
	instance->size = Vector2(34,20);
	instance->floatBottom = true;
	instance->floatRight = true;
	instance->position = Vector2(-77, -60);
	instance->setParent(this);
	instance->name = "CenterCam";
	instance->setButtonListener(new CameraButtonListener());

	instance = makeImageButton(
		Texture::fromFile(GetFileInPath("/content/images/CameraTiltUp.png")),
		Texture::fromFile(GetFileInPath("/content/images/CameraTiltUp_ovr.png")),
		Texture::fromFile(GetFileInPath("/content/images/CameraTiltUp_dn.png")));
	instance->size = Vector2(24,24);
	instance->floatBottom = true;
	instance->floatRight = true;
	instance->position = Vector2(-105, -75);
	instance->setParent(this);
	instance->name = "TiltUp";
	instance->setButtonListener(new CameraButtonListener());

	instance = makeImageButton(
		Texture::fromFile(GetFileInPath("/content/images/CameraTiltDown.png")),
		Texture::fromFile(GetFileInPath("/content/images/CameraTiltDown_ovr.png")),
		Texture::fromFile(GetFileInPath("/content/images/CameraTiltDown_dn.png")));
	instance->size = Vector2(24,24);
	instance->floatBottom = true;
	instance->floatRight = true;
	instance->position = Vector2(-40, -75);
	instance->setParent(this);
	instance->name = "TiltDown";
	instance->setButtonListener(new CameraButtonListener());
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
	//TODO--Move these to their own instance

	std::stringstream stream;
	stream << std::fixed << std::setprecision(1) << g_dataModel->getLevel()->timer;
	g_fntdominant->draw2D(rd, "Timer: " + stream.str(), Vector2(rd->getWidth() - 120, 25), 20, Color3::fromARGB(0x81C518), Color3::black());
	g_fntdominant->draw2D(rd, "Score: " + Convert(g_dataModel->getLevel()->score), Vector2(rd->getWidth() - 120, 50), 20, Color3::fromARGB(0x81C518), Color3::black());
	//FPS
#ifdef _DEBUG
	stream.str("");
    stream.clear();
    stream << std::fixed << std::setprecision(3) << fps;
    g_fntdominant->draw2D(rd, "FPS: " + stream.str(), Vector2(120, 25), 10, Color3::fromARGB(0xFFFF00), Color3::black());
#endif
	//GUI Boxes	
	Draw::box(G3D::Box(Vector3(0,25,0),Vector3(80,355,0)),rd,Color4(0.6F,0.6F,0.6F,0.4F), Color4(0,0,0,0));
	Draw::box(G3D::Box(Vector3(rd->getWidth() - 120,rd->getHeight() - 117,0),Vector3(rd->getWidth(),rd->getHeight(),0)),rd,Color4(0.6F,0.6F,0.6F,0.4F), Color4(0,0,0,0));
	
	//Camera menu title
	g_fntlighttrek->draw2D(rd, "CameraMenu", Vector2(rd->getWidth()-(g_fntlighttrek->get2DStringBounds("CameraMenu", 14).x+1),rd->getHeight() - 120), 14, Color3::white(), Color4(0.5F,0.5F,0.5F,0.5F));

	//Tools menu
	Draw::box(G3D::Box(Vector3(5, 210,0),Vector3(75, 210,0)),rd,Color4(0.6F,0.6F,0.6F,0.4F), Color4(0.6F,0.6F,0.6F,0.4F));
	g_fntlighttrek->draw2D(rd,"MENU", Vector2(10,332), 14, Color3::white(), Color4(0.5F,0.5F,0.5F,0.5F));

	
	//drawButtons(rd);
	if(System::time() - 3 < _messageTime)
	{
		g_fntdominant->draw2D(rd, _message, Vector2((rd->getWidth()/2)-(g_fntdominant->get2DStringBounds(_message, 20).x/2),(rd->getHeight()/2)-(g_fntdominant->get2DStringBounds(_message, 20).y/2)), 20, Color3::yellow(), Color3::black());
	}

	g_dataModel->drawMessage(rd);
	render(rd);
}

bool GuiRootInstance::mouseInGUI(G3D::RenderDevice* renderDevice,int x,int y)
{
	std::vector<Instance*> instances_2D = g_dataModel->getGuiRoot()->getAllChildren();
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
		for(size_t i = 0; i < g_selectedInstances.size(); i++)
			if(g_selectedInstances.at(i)->canDelete)
			{
				button->disabled = false;
				button2->disabled = false;
				button3->disabled = false;
				button4->disabled = false;
				button5->disabled = false;
				button6->disabled = false;
				break;
			}
	}
}

GuiRootInstance::~GuiRootInstance()
{
	delete toolbar;
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
