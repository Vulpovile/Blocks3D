/**
  @file demos/main.cpp

  This is a sample main.cpp to get you started with G3D.  It is
  designed to make writing an application easy.  Although the
  GApp/GApplet infrastructure is helpful for most projects,
  you are not restricted to using it-- choose the level of
  support that is best for your project (see the G3D Map in the
  documentation).

  @author Morgan McGuire, matrix@graphics3d.com
 */
#include <G3DAll.h>
#include <iomanip>
#include "Instance.h"
#include "resource.h"
#include "PhysicalInstance.h"
#include "TextButtonInstance.h"
#include "ImageButtonInstance.h"
#include "DataModelInstance.h"
#include "AudioPlayer.h"
#include <limits.h>

#if G3D_VER < 61000
	#error Requires G3D 6.10
#endif
HWND hwnd;

static std::string title = "";
static DataModelInstance* dataModel;
GFontRef fntdominant = NULL;
GFontRef fntlighttrek = NULL;
Ray testRay;
static bool democ = true;
static std::string message = "";
static G3D::RealTime messageTime = 0;
static std::string tempPath = "";
static G3D::RealTime inputTime = 0;
static int FPSVal[8] = {10, 20, 30, 60, 120, 240, INT_MAX,1};
static int index = 2;
static std::string cameraSound = "";
static std::string clickSound = "";
static std::string dingSound = "";
static G3D::TextureRef go = NULL;
static G3D::TextureRef go_ovr = NULL;
static G3D::TextureRef go_dn = NULL;
VARAreaRef varStatic = NULL;
static float mousex = 0;
static float mousey = 0;
static int cursorid = 0;
static G3D::TextureRef cursor = NULL;
static bool mouseButton1Down = false;
static bool running = true;
static bool mouseMovedBeginMotion = false;
static bool showMouse = true;
//Controller
static bool forwards = false;
static bool backwards = false;
static bool left = false;
static bool right = false;
static bool centerCam = false;
static bool panRight = false;
static bool panLeft = false;
static bool tiltUp = false;
static const int CURSOR = 0;
static const int ARROWS = 1;
static const int RESIZE = 2;
static int mode = CURSOR;
bool dragging = false;
Vector3 cameraPos = Vector3(0,2,10);
Vector2 oldMouse = Vector2(0,0);
float moveRate = 0.5;
Instance* selectedInstance = NULL;
/**
 This simple demo applet uses the debug mode as the regular
 rendering mode so you can fly around the scene.
 */





class Demo : public GApplet {

public:

    // Add state that should be visible to this applet.
    // If you have multiple applets that need to share
    // state, put it in the App.

    class App*          app;

	virtual void exitApplication();

    Demo(App* app);

    virtual ~Demo() {}

    virtual void onInit();

    virtual void onLogic();

	virtual void onNetwork();

    virtual void onSimulation(RealTime rdt, SimTime sdt, SimTime idt);

    virtual void onGraphics(RenderDevice* rd);

    virtual void onUserInput(UserInput* ui);

    virtual void onCleanup();

};



/*class App : public GApp {
protected:
    void main();
public:
    SkyRef              sky;

    Demo*               applet;

    App(const GAppSettings& settings, GWindow* wnd);

    ~App();
};*/

class App : public GApp {
    protected:
        void main();
    public:
        SkyRef              sky;

        Demo*               applet;

        App(const GAppSettings& settings, GWindow* wnd,HWND tempMainHWnd, SDLWindow*);
		

        ~App();
        HWND getHWND();
        HWND getPropertyHWND();
        HWND getMainHWND();
        //void addHWND(HWND hwnd);
    private:
        HWND hwnd;
        HWND propertyHWnd;
        HWND mainHWnd;
};

App *usableApp = NULL;

HWND App::getHWND()
{
    return hwnd;
}
HWND App::getPropertyHWND()
{
    return propertyHWnd;
}
HWND App::getMainHWND()
{
    return mainHWnd;
}
 

Demo::Demo(App* _app) : GApplet(_app), app(_app) {
	varStatic = VARArea::create(1024 * 1024);
}


void clearInstances()
{
	//for(size_t i = 0; i < instances.size(); i++)
	//{
	//	delete instances.at(i);
	//}
	delete dataModel;
}

void OnError(int err, std::string msg = "")
{
	usableApp->window()->setInputCaptureCount(0);
	usableApp->window()->setMouseVisible(true);
	std::string emsg = "An unexpected error has occured and DUOM 5 has to quit. We're sorry!" + msg;
	clearInstances();
	//DialogBox(NULL, MAKEINTRESOURCE(IDD_DIALOG1), NULL, NULL);
	MessageBox(NULL, emsg.c_str(),"Dynamica Crash", MB_OK);
	exit(err);
}

std::string ExePath() {
    char buffer[MAX_PATH];
	GetModuleFileName( NULL, buffer, MAX_PATH );
	std::string::size_type pos = std::string( buffer ).find_last_of( "\\/" );
	return std::string( buffer ).substr( 0, pos);
}

std::string GetFileInPath(std::string file)
{
	std::string name = ExePath() + file;
	struct stat buf;
    if (stat(name.c_str(), &buf) != -1)
    {
        return name;
    }
	else
		OnError(202, " \r\nFile not found: " + name);
		return NULL;
		
	
}

#include <sstream>
std::string Convert (float number){
    std::ostringstream buff;
    buff<<number;
    return buff.str();   
}


PhysicalInstance* makePart()
{
	PhysicalInstance* part = new PhysicalInstance();
//	instances.push_back(part);
	return part;
}

TextButtonInstance* makeTextButton()
{
	TextButtonInstance* part = new TextButtonInstance();
//	instances.push_back(part);
//	instances_2D.push_back(part);
	return part;
}

ImageButtonInstance* makeImageButton(G3D::TextureRef newImage = NULL, G3D::TextureRef overImage = NULL, G3D::TextureRef downImage = NULL, G3D::TextureRef disableImage = NULL)
{
	ImageButtonInstance* part = new ImageButtonInstance(newImage,overImage, downImage, disableImage);
//	instances.push_back(part);
//	instances_2D.push_back(part);
	return part;
}



class CameraButtonListener : public ButtonListener {
public:
	void onButton1MouseClick(BaseButtonInstance*);
};

void CameraButtonListener::onButton1MouseClick(BaseButtonInstance* button)
{
	AudioPlayer::playSound(cameraSound);
	CoordinateFrame frame = usableApp->debugCamera.getCoordinateFrame();
	if(button->name == "CenterCam")
		centerCam = true;
	else if(button->name == "ZoomIn")
		cameraPos = Vector3(cameraPos.x, cameraPos.y, cameraPos.z) + frame.lookVector()*2;
	else if(button->name == "ZoomOut")
		cameraPos = Vector3(cameraPos.x, cameraPos.y, cameraPos.z) - frame.lookVector()*2;
	else if(button->name == "PanRight")
		panRight = true;
	else if(button->name == "PanLeft")
		panLeft = true;
	else if(button->name == "TiltUp")
		tiltUp = true;
}

class GUDButtonListener : public ButtonListener {
public:
	void onButton1MouseClick(BaseButtonInstance*);
};

void GUDButtonListener::onButton1MouseClick(BaseButtonInstance* button)
{
	if(selectedInstance != NULL)
	{
		AudioPlayer::playSound(dingSound);
		if(button->name == "Duplicate")
		{

		}
	}
		
}

class RotateButtonListener : public ButtonListener {
public:
	void onButton1MouseClick(BaseButtonInstance*);
};

void RotateButtonListener::onButton1MouseClick(BaseButtonInstance* button)
{
	if(selectedInstance != NULL)
	{
		AudioPlayer::playSound(clickSound);
		if(selectedInstance->getClassName() == "Part")
		{
			PhysicalInstance* part = (PhysicalInstance*) selectedInstance;
			if(button->name == "Tilt")
				part->setCFrame(part->getCFrame()*Matrix3::fromEulerAnglesXYZ(0,0,toRadians(90)));
			else if(button->name == "Rotate")
				part->setCFrame(part->getCFrame()*Matrix3::fromEulerAnglesXYZ(0,toRadians(90),0));
		}
	}
		
}


void deleteInstance()
{
	if(selectedInstance != NULL)
	{
		if(selectedInstance->getParent() != NULL)
			selectedInstance->getParent()->removeChild(selectedInstance);
		delete selectedInstance;
		selectedInstance = NULL;
		AudioPlayer::playSound(GetFileInPath("/content/sounds/pageturn.wav"));
	}
}


class DeleteListener : public ButtonListener {
public:
	void onButton1MouseClick(BaseButtonInstance*);
};

void DeleteListener::onButton1MouseClick(BaseButtonInstance* button)
{
	deleteInstance();
}




class ModeSelectionListener : public ButtonListener {
public:
	void onButton1MouseClick(BaseButtonInstance*);
};


void ModeSelectionListener::onButton1MouseClick(BaseButtonInstance* button)
{
	CoordinateFrame frame = usableApp->debugCamera.getCoordinateFrame();
	
	std::vector<Instance*> instances_2D = dataModel->getGuiRoot()->getAllChildren();
	for(size_t i = 0; i < instances_2D.size(); i++)
		{
			if(instances_2D.at(i)->name == "Cursor" || instances_2D.at(i)->name == "Resize" || instances_2D.at(i)->name == "Arrows")
			{
				BaseButtonInstance* button = (BaseButtonInstance*)instances_2D.at(i);
				button->selected = false;
			}
		}

	button->selected = true;
	if(button->name == "Cursor")
		mode = CURSOR;
	else if(button->name == "Resize")
		mode = RESIZE;
	else if(button->name == "Arrows")
		mode = ARROWS;
}


void initGUI()
{
	TextButtonInstance* button = makeTextButton();
	button->boxBegin = Vector2(0, -24);
	button->boxEnd = Vector2(80, 0);
	button->floatBottom = true;
	button->setParent(dataModel->getGuiRoot());
	button->font = fntlighttrek;
	button->textColor = Color3(0,255,255);
	button->textOutlineColor = Color4::clear();
	button->title = "Hopper";
	button->fontLocationRelativeTo = Vector2(10, 3);
	button->setAllColorsSame();
	
	button = makeTextButton();
	button->boxBegin = Vector2(0, -48);
	button->boxEnd = Vector2(80, -24);
	button->floatBottom = true;
	button->setParent(dataModel->getGuiRoot());
	button->font = fntlighttrek;
	button->textColor = Color3(0,255,255);
	button->textOutlineColor = Color4::clear();
	button->title = "Controller";
	button->fontLocationRelativeTo = Vector2(10, 3);
	button->setAllColorsSame();

	button = makeTextButton();
	button->boxBegin = Vector2(0, -72);
	button->boxEnd = Vector2(80, -48);
	button->floatBottom = true;
	button->setParent(dataModel->getGuiRoot());
	button->font = fntlighttrek;
	button->textColor = Color3(0,255,255);
	button->textOutlineColor = Color4::clear();
	button->title = "Color";
	button->fontLocationRelativeTo = Vector2(10, 3);
	button->setAllColorsSame();

	button = makeTextButton();
	button->boxBegin = Vector2(0, -96);
	button->boxEnd = Vector2(80, -72);
	button->floatBottom = true;
	button->setParent(dataModel->getGuiRoot());
	button->font = fntlighttrek;
	button->textColor = Color3(0,255,255);
	button->textOutlineColor = Color4::clear();
	button->title = "Surface";
	button->fontLocationRelativeTo = Vector2(10, 3);
	button->setAllColorsSame();

	button = makeTextButton();
	button->boxBegin = Vector2(0, -120);
	button->boxEnd = Vector2(80, -96);
	button->floatBottom = true;
	button->setParent(dataModel->getGuiRoot());
	button->font = fntlighttrek;
	button->textColor = Color3(0,255,255);
	button->boxOutlineColor = Color3(0,255,255);
	button->title = "Model";
	button->fontLocationRelativeTo = Vector2(10, 3);
	button->setAllColorsSame();

	button = makeTextButton();
	button->boxBegin = Vector2(0, 0);
	button->boxEnd = Vector2(125, 25);
	button->setParent(dataModel->getGuiRoot());
	button->font = fntlighttrek;
	button->textColor = Color3::white();
	button->boxColor = Color4::clear();
	button->textOutlineColor = Color4(0.5F,0.5F,0.5F,0.5F);
	button->title = "File";
	button->textSize = 16;
	button->fontLocationRelativeTo = Vector2(10, 0);
	button->setAllColorsSame();

	button = makeTextButton();
	button->boxBegin = Vector2(125, 0);
	button->boxEnd = Vector2(250, 25);
	button->setParent(dataModel->getGuiRoot());
	button->font = fntlighttrek;
	button->textColor = Color3::white();
	button->boxColor = Color4::clear();
	button->textOutlineColor = Color4(0.5F,0.5F,0.5F,0.5F);
	button->title = "Edit";
	button->textSize = 16;
	button->fontLocationRelativeTo = Vector2(10, 0);
	button->setAllColorsSame();

	button = makeTextButton();
	button->boxBegin = Vector2(250, 0);
	button->boxEnd = Vector2(375, 25);
	button->setParent(dataModel->getGuiRoot());
	button->font = fntlighttrek;
	button->textColor = Color3::white();
	button->boxColor = Color4::clear();
	button->textOutlineColor = Color4(0.5F,0.5F,0.5F,0.5F);
	button->title = "View";
	button->textSize = 16;
	button->fontLocationRelativeTo = Vector2(10, 0);
	button->setAllColorsSame();

	button = makeTextButton();
	button->boxBegin = Vector2(375, 0);
	button->boxEnd = Vector2(500, 25);
	button->setParent(dataModel->getGuiRoot());
	button->font = fntlighttrek;
	button->textColor = Color3::white();
	button->boxColor = Color4::clear();
	button->textOutlineColor = Color4(0.5F,0.5F,0.5F,0.5F);
	button->title = "Insert";
	button->textSize = 16;
	button->fontLocationRelativeTo = Vector2(10, 0);
	button->setAllColorsSame();

	button = makeTextButton();
	button->boxBegin = Vector2(500, 0);
	button->boxEnd = Vector2(625, 25);
	button->setParent(dataModel->getGuiRoot());
	button->font = fntlighttrek;
	button->textColor = Color3::white();
	button->boxColor = Color4::clear();
	button->textOutlineColor = Color4(0.5F,0.5F,0.5F,0.5F);
	button->title = "Format";
	button->textSize = 16;
	button->fontLocationRelativeTo = Vector2(10, 0);
	button->setAllColorsSame();



	button = makeTextButton();
	button->boxBegin = Vector2(0,215);
	button->boxEnd = Vector2(80,235);
	button->textOutlineColor = Color4(0.5F,0.5F,0.5F,0.5F);
	button->textColor = Color3::white();
	button->boxColor = Color4::clear();
	button->textSize = 12;
	button->title = "Group";
	button->setAllColorsSame();
	button->font = fntlighttrek;
	button->fontLocationRelativeTo = Vector2(10, 0);
	button->setParent(dataModel->getGuiRoot());


	button = makeTextButton();
	button->boxBegin = Vector2(0,240);
	button->boxEnd = Vector2(80,260);
	button->textOutlineColor = Color4(0.5F,0.5F,0.5F,0.5F);
	button->textColor = Color3::white();
	button->boxColor = Color4::clear();
	button->textSize = 12;
	button->title = "UnGroup";
	button->setAllColorsSame();
	button->font = fntlighttrek;
	button->fontLocationRelativeTo = Vector2(10, 0);
	button->setParent(dataModel->getGuiRoot());

	button = makeTextButton();
	button->boxBegin = Vector2(0,265);
	button->boxEnd = Vector2(80,285);
	button->textOutlineColor = Color4(0.5F,0.5F,0.5F,0.5F);
	button->textColor = Color3::white();
	button->boxColor = Color4::clear();
	button->textSize = 12;
	button->title = "Duplicate";
	button->setAllColorsSame();
	button->font = fntlighttrek;
	button->fontLocationRelativeTo = Vector2(10, 0);
	button->setParent(dataModel->getGuiRoot());
	button->name = "Duplicate";
	button->setButtonListener(new GUDButtonListener());


	ImageButtonInstance* instance = makeImageButton(go, go_ovr, go_dn);
	instance->name = "go";
	instance->size = Vector2(65,65);
	instance->position = Vector2(6.5, 25);
	instance->setParent(dataModel->getGuiRoot());

	

	instance = makeImageButton(
		Texture::fromFile(GetFileInPath("/content/images/ArrowTool.png")),
		Texture::fromFile(GetFileInPath("/content/images/ArrowTool_ovr.png")),
		Texture::fromFile(GetFileInPath("/content/images/ArrowTool_dn.png")),
		Texture::fromFile(GetFileInPath("/content/images/ArrowTool_ds.png")));
	instance->size = Vector2(50,50);
	instance->position = Vector2(15, 90);
	instance->setParent(dataModel->getGuiRoot());
	instance->name = "Cursor";
	instance->setButtonListener(new ModeSelectionListener());

	instance = makeImageButton(Texture::fromFile(GetFileInPath("/content/images/ScaleTool.png")),Texture::fromFile(GetFileInPath("/content/images/ScaleTool_ovr.png")),Texture::fromFile(GetFileInPath("/content/images/ScaleTool_dn.png")),Texture::fromFile(GetFileInPath("/content/images/ScaleTool_ds.png")));
	instance->size = Vector2(40,40);
	instance->position = Vector2(0, 140);
	instance->setParent(dataModel->getGuiRoot());
	instance->name = "Resize";
	instance->setButtonListener(new ModeSelectionListener());
	

	instance = makeImageButton(
		Texture::fromFile(GetFileInPath("/content/images/MoveTool.png")),
		Texture::fromFile(GetFileInPath("/content/images/MoveTool_ovr.png")),
		Texture::fromFile(GetFileInPath("/content/images/MoveTool_dn.png")),
		Texture::fromFile(GetFileInPath("/content/images/MoveTool_ds.png")));
	instance->size = Vector2(40,40);
	instance->position = Vector2(40, 140);
	instance->setParent(dataModel->getGuiRoot());
	instance->name = "Arrows";
	instance->setButtonListener(new ModeSelectionListener());

	instance = makeImageButton(
		Texture::fromFile(GetFileInPath("/content/images/SelectionRotate.png")),
		Texture::fromFile(GetFileInPath("/content/images/SelectionRotate_ovr.png")),
		NULL,
		Texture::fromFile(GetFileInPath("/content/images/SelectionRotate_ds.png")));
	instance->size = Vector2(30,30);
	instance->position = Vector2(10, 175);
	instance->setParent(dataModel->getGuiRoot());
	instance->name = "Rotate";
	instance->setButtonListener(new RotateButtonListener());

	instance = makeImageButton(
		Texture::fromFile(GetFileInPath("/content/images/SelectionTilt.png")),
		Texture::fromFile(GetFileInPath("/content/images/SelectionTilt_ovr.png")),
		NULL,
		Texture::fromFile(GetFileInPath("/content/images/SelectionTilt_ds.png")));
	instance->size = Vector2(30,30);
	instance->position = Vector2(40, 175);
	instance->setParent(dataModel->getGuiRoot());
	instance->name = "Tilt";
	instance->setButtonListener(new RotateButtonListener());


	instance = makeImageButton(
		Texture::fromFile(GetFileInPath("/content/images/Delete.png")),
		Texture::fromFile(GetFileInPath("/content/images/Delete_ovr.png")),
		Texture::fromFile(GetFileInPath("/content/images/Delete_dn.png")),
		Texture::fromFile(GetFileInPath("/content/images/Delete_ds.png")));
	instance->size = Vector2(40,46);
	instance->position = Vector2(20, 284);
	instance->setParent(dataModel->getGuiRoot());
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
	instance->setParent(dataModel->getGuiRoot());
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
	instance->setParent(dataModel->getGuiRoot());
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
	instance->setParent(dataModel->getGuiRoot());
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
	instance->setParent(dataModel->getGuiRoot());
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
	instance->setParent(dataModel->getGuiRoot());
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
	instance->setParent(dataModel->getGuiRoot());
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
	instance->setParent(dataModel->getGuiRoot());
	instance->name = "TiltDown";
	instance->setButtonListener(new CameraButtonListener());
}


void Demo::onInit()  {
	
    // Called before Demo::run() beings
	

	dataModel = new DataModelInstance();
	dataModel->setParent(NULL);
	dataModel->name = "undefined";
	
	initGUI();

	
	PhysicalInstance* test = makePart();
	test->setParent(dataModel->getWorkspace());
	test->color = Color3(0.2F,0.3F,1);
	test->setSize(Vector3(24,1,24));
	test->setPosition(Vector3(0,0,0));
	test->setCFrame(test->getCFrame() * Matrix3::fromEulerAnglesXYZ(0,toRadians(40),toRadians(40)));
	//selectedInstance = test;
	

	
	test = makePart();
	test->setParent(dataModel->getWorkspace());
	test->color = Color3(.5F,1,.5F);
	test->setSize(Vector3(4,1,2));
	test->setPosition(Vector3(-10,1,0));
	test = makePart();
	test->setParent(dataModel->getWorkspace());
	test->color = Color3(.5F,1,.5F);
	test->setSize(Vector3(4,1,2));
	test->setPosition(Vector3(10,1,0));

	test = makePart();
	test->setParent(dataModel->getWorkspace());
	test->color = Color3::gray();
	test->setSize(Vector3(4,1,2));
	test->setPosition(Vector3(7,2,0));

	test = makePart();
	test->setParent(dataModel->getWorkspace());
	test->color = Color3::gray();
	test->setSize(Vector3(4,1,2));
	test->setPosition(Vector3(-7,2,0));

	test = makePart();
	test->setParent(dataModel->getWorkspace());
	test->color = Color3::gray();
	test->setSize(Vector3(4,1,2));
	test->setPosition(Vector3(4,3,0));

	test = makePart();
	test->setParent(dataModel->getWorkspace());
	test->color = Color3::gray();
	test->setSize(Vector3(4,1,2));
	test->setPosition(Vector3(-5,3,0));

	test = makePart();
	test->setParent(dataModel->getWorkspace());
	test->color = Color3::gray();
	test->setSize(Vector3(4,1,2));
	test->setPosition(Vector3(1,4,0));

	test = makePart();
	test->setParent(dataModel->getWorkspace());
	test->color = Color3::gray();
	test->setSize(Vector3(4,1,2));
	test->setPosition(Vector3(-3,4,0));

	test = makePart();
	test->setParent(dataModel->getWorkspace());
	test->color = Color3::gray();
	test->setSize(Vector3(4,1,2));
	test->setPosition(Vector3(-2,5,0));
	

	

	test = makePart();
	test->setParent(dataModel->getWorkspace());
	test->color = Color3::gray();
	test->setSize(Vector3(4,1,2));
	test->setPosition(Vector3(0,6,0));

	test = makePart();
	test->setParent(dataModel->getWorkspace());
	test->color = Color3::gray();
	test->setSize(Vector3(4,1,2));
	test->setPosition(Vector3(2,7,0));

	
	



	setDesiredFrameRate(FPSVal[index]);
	
	
	

    GApplet::onInit();
	
}






void Demo::onCleanup() {
    clearInstances();
	go->~Texture();
	go_ovr->~Texture();
	go_dn->~Texture();
	go_dn.~ReferenceCountedPointer();
	delete go_dn.pointer();
	go.~ReferenceCountedPointer();
	delete go.pointer();
	go_ovr.~ReferenceCountedPointer();
	delete go_ovr.pointer();
	app->sky->~Sky();
}




void Demo::onLogic() {
    // Add non-simulation game logic and AI code here
	
	Instance* obj = dataModel->getGuiRoot()->findFirstChild("Delete");
		if(obj != NULL)
		{
			ImageButtonInstance* button = (ImageButtonInstance*)obj;
			if(selectedInstance == NULL)
				button->disabled = true;
			else
				button->disabled = false;	
		}


}


void Demo::onNetwork() {
	// Poll net messages here
}


double getVectorDistance(Vector3 vector1, Vector3 vector2)
{
	return pow(pow((double)vector1.x - (double)vector2.x, 2) + pow((double)vector1.y - (double)vector2.y, 2) + pow((double)vector1.z - (double)vector2.z, 2), 0.5);
}

void Demo::onSimulation(RealTime rdt, SimTime sdt, SimTime idt) {
	if(dataModel->name != title)
	{
		title = dataModel->name;
		std::string text = "Game \"" + title + "\"";
		SetWindowText(app->getMainHWND(), text.c_str());
	}

	CoordinateFrame frame = app->debugCamera.getCoordinateFrame();
	if(forwards)
	{
		forwards = false;
		cameraPos = Vector3(cameraPos.x, cameraPos.y, cameraPos.z) + frame.lookVector()*moveRate;
	}
	else if(backwards)
	{
		backwards = false;
		cameraPos = Vector3(cameraPos.x, cameraPos.y, cameraPos.z) - frame.lookVector()*moveRate;
	}
	if(left)
	{
		left = false;
		cameraPos = Vector3(cameraPos.x, cameraPos.y, cameraPos.z) + frame.leftVector()*moveRate;
	}
	else if(right)
	{
		right = false;
		cameraPos = Vector3(cameraPos.x, cameraPos.y, cameraPos.z) + frame.rightVector()*moveRate;
	}
	app->debugCamera.setPosition(cameraPos);
	if(centerCam)
	{
		CoordinateFrame frame = CoordinateFrame(app->debugCamera.getCoordinateFrame().translation);
		if(selectedInstance == NULL)
			frame.lookAt(Vector3(0,0,0));
		else
			frame.lookAt(((PhysicalInstance*)selectedInstance)->getPosition());
		app->debugController.setCoordinateFrame(frame);
		centerCam = false;
	}
	
	if(panRight)
	{
		panRight = false;
		CoordinateFrame frame = app->debugCamera.getCoordinateFrame();
		float y = frame.translation.y;
		CoordinateFrame frame2 = CoordinateFrame(frame.rotation, frame.translation + frame.lookVector()*25);
		Vector3 focus = frame.translation+frame.lookVector()*25;
		frame2 = frame2 * Matrix3::fromEulerAnglesXYZ(0,toRadians(45),0);
		frame2 = frame2 - frame2.lookVector()*25;
		cameraPos = Vector3(frame2.translation.x, y, frame2.translation.z);
		CoordinateFrame newFrame = CoordinateFrame(frame2.rotation, Vector3(frame2.translation.x, y, frame2.translation.z));
		newFrame.lookAt(focus);
		app->debugController.setCoordinateFrame(newFrame);

		/*Vector3 camerapoint = frame.translation;
		Vector3 focalPoint = camerapoint + frame.lookVector() * 25;
		

		float distb = getVectorDistance(Vector3(focalPoint.x, camerapoint.y, focalPoint.z), Vector3(camerapoint.x, camerapoint.y, focalPoint.z));
		float distc = abs(((float)getVectorDistance(Vector3(focalPoint.x, camerapoint.y, focalPoint.z), camerapoint)));




		float angle = atan2(camerapoint.z - focalPoint.z, focalPoint.x - camerapoint.x);
		
		
		//message = Convert(angle);
		messageTime = System::time();
		//frame.rotation.toEulerAnglesXYZ(x, angle, z);
		//angle = toDegrees(angle);
		
//		if(camerapoint.z < focalPoint.z)
//		{
//			float angleadd = abs(angle - 90);
//			angle = angleadd + 5 + 90;
//		}
//		else
//		{
//			angle = angle + 5;
//		}
		

		
		messageTime = System::time();

		//abs(((float)(getVectorDistance(Vector3(focalPoint.x, camerapoint.y, focalPoint.z), camerapoint))));
		float x = distc * cos(angle + toRadians(2)) + focalPoint.x;
        float z = distc * sin(angle + toRadians(2)) + focalPoint.z;
		message = "NOT 0, " + Convert(toDegrees(angle)) + ", " + Convert(toDegrees(angle + toRadians(2)));
		//camerapoint = Vector3(sin(angle)*distc,camerapoint.y,cos(angle)*distc);
		camerapoint = Vector3(x,camerapoint.y,z);
		CoordinateFrame newFrame = CoordinateFrame(camerapoint);
		newFrame.lookAt(focalPoint);
		cameraPos = camerapoint;
		app->debugController.setCoordinateFrame(newFrame);*/

	}
	if(panLeft)
	{
		panLeft = false;
		CoordinateFrame frame = app->debugCamera.getCoordinateFrame();
		float y = frame.translation.y;
		CoordinateFrame frame2 = CoordinateFrame(frame.rotation, frame.translation + frame.lookVector()*25);
		Vector3 focus = frame.translation+frame.lookVector()*25;
		frame2 = frame2 * Matrix3::fromEulerAnglesXYZ(0,toRadians(-45),0);
		frame2 = frame2 - frame2.lookVector()*25;
		cameraPos = Vector3(frame2.translation.x, y, frame2.translation.z);
		CoordinateFrame newFrame = CoordinateFrame(frame2.rotation, Vector3(frame2.translation.x, y, frame2.translation.z));
		newFrame.lookAt(focus);
		app->debugController.setCoordinateFrame(newFrame);
	}
	if(tiltUp)
	{
		tiltUp = false;
		CoordinateFrame frame = CoordinateFrame(app->debugCamera.getCoordinateFrame().rotation, app->debugCamera.getCoordinateFrame().translation);
		Vector3 camerapoint = frame.translation;

		Vector3 focalPoint = camerapoint + frame.lookVector() * 25;
		float distance = pow(pow((double)focalPoint.x - (double)camerapoint.x, 2) + pow((double)camerapoint.y - (double)camerapoint.y, 2) + pow((double)focalPoint.z - (double)camerapoint.z, 2), 0.5);
		float x = distance * cos(22.5 * G3D::pi() / 180) + focalPoint.x;
        float z = distance * sin(22.5 * G3D::pi() / 180) + focalPoint.z;
		camerapoint = Vector3(camerapoint.x, camerapoint.y+2, camerapoint.z);
		
		CoordinateFrame newFrame = CoordinateFrame(camerapoint);
		newFrame.lookAt(focalPoint);
		cameraPos = camerapoint;
		app->debugController.setCoordinateFrame(newFrame);
		
		
	}
		
}


//void readMouseGUIInput()
//{
	
//}

double getOSVersion() {
    OSVERSIONINFO osvi;

    ZeroMemory(&osvi, sizeof(OSVERSIONINFO));
    osvi.dwOSVersionInfoSize = sizeof(OSVERSIONINFO);

    GetVersionEx(&osvi);
	std::string version = Convert(osvi.dwMajorVersion) + "." + Convert(osvi.dwMinorVersion);
	return ::atof(version.c_str());
}

//User Input
void Demo::onUserInput(UserInput* ui) {
	
    if (ui->keyPressed(SDLK_ESCAPE)) {
        // Even when we aren't in debug mode, quit on escape.
        endApplet = true;
        app->endProgram = true;
    }
	if(mouseMovedBeginMotion)
	{
		mouseMovedBeginMotion = false;
		app->debugController.setActive(true);
	}
	if(ui->keyPressed(SDL_RIGHT_MOUSE_KEY))
	{
		oldMouse = ui->getMouseXY();
		showMouse = false;
		app->window()->setRelativeMousePosition(app->window()->width()/2, app->window()->height()/2);
		mouseMovedBeginMotion = true;
		
	}
	else if(ui->keyReleased(SDL_RIGHT_MOUSE_KEY))
	{
		ui->setMouseXY(oldMouse);
		showMouse = true;
		app->debugController.setActive(false);
	}
	if(ui->keyPressed(SDLK_LSHIFT) || ui->keyPressed(SDLK_RSHIFT))
	{
		moveRate = 1;
	}
	else if(ui->keyReleased(SDLK_LSHIFT) || ui->keyReleased(SDLK_RSHIFT))
	{
		moveRate = 0.5;
	}

	if(ui->keyPressed(SDL_MOUSE_WHEEL_UP_KEY))
	{
		AudioPlayer::playSound(cameraSound);
		CoordinateFrame frame = app->debugCamera.getCoordinateFrame();
		cameraPos = cameraPos + frame.lookVector()*2;
	}
	if(ui->keyPressed(SDL_MOUSE_WHEEL_DOWN_KEY))
	{
		AudioPlayer::playSound(cameraSound);
		CoordinateFrame frame = app->debugCamera.getCoordinateFrame();
		cameraPos = cameraPos - frame.lookVector()*2;
	}

	if(ui->keyPressed(SDLK_DELETE))
	{
		deleteInstance();
	}

	if(ui->keyDown(SDLK_LCTRL))
	{
		if(ui->keyPressed('d'))
		{
			messageTime = System::time();
			if(app->debugMode())
				message = "Debug Mode Disabled";
			else
				message = "Debug Mode Enabled, Soon to be depricated";
			app->setDebugMode(!app->debugMode());
		}
	}
	if(ui->keyDown(SDLK_LCTRL))
	{
		if(ui->keyPressed('v'))
		{
			messageTime = System::time();
			message = Convert(getOSVersion());
		}
	}
	if(ui->keyPressed(SDLK_F8))
	{
		//index++;
		//if(index >= 7)
		//{
		//	index = 0;
		//}
		messageTime = System::time();
		message = "FPS has been locked at " + Convert(FPSVal[index]);
		//setDesiredFrameRate(FPSVal[index]);
	}
	mousex = ui->getMouseX();
	mousey = ui->getMouseY();
	mouseButton1Down = ui->keyDown(SDL_LEFT_MOUSE_KEY);
	if(ui->keyDown(SDLK_UP))
	{
		forwards = true;
	}
	else if(ui->keyDown(SDLK_DOWN))
	{
		backwards = true;
	}
	if(ui->keyDown(SDLK_LEFT))
	{
		left = true;
	}
	else if(ui->keyDown(SDLK_RIGHT))
	{
		
		right = true;
	}
	
	if(ui->keyPressed(SDL_LEFT_MOUSE_KEY))
	{
		bool onGUI = false;
		std::vector<Instance*> instances_2D = dataModel->getGuiRoot()->getAllChildren();
		for(size_t i = 0; i < instances_2D.size(); i++)
		{
			if(instances_2D.at(i)->getClassName() == "TextButton" || instances_2D.at(i)->getClassName() == "ImageButton")
			{
				BaseButtonInstance* button = (BaseButtonInstance*)instances_2D.at(i);
				if(button->mouseInButton(ui->mouseXY().x, ui->mouseXY().y, app->renderDevice))
				{
					onGUI = true;
					break;
				}
			}
		}
		if(!onGUI)
		{
			selectedInstance = NULL;
			testRay = app->debugCamera.worldRay(mousex, mousey, app->renderDevice->getViewport());
			float nearest=std::numeric_limits<float>::infinity();
			Vector3 camPos = app->debugCamera.getCoordinateFrame().translation;
			std::vector<Instance*> instances = dataModel->getWorkspace()->getAllChildren();
            for(size_t i = 0; i < instances.size(); i++)
			{
				if(instances.at(i)->getClassName() == "Part")
				{
					PhysicalInstance* test = (PhysicalInstance*)instances.at(i);
					float time = testRay.intersectionTime(test->getBox());
					if (time != inf()) 
					{
						if (nearest>time)
						{
							nearest=time;
							selectedInstance = test;
							//message = "Dragging = true.";
							//messageTime = System::time();
							dragging = true;
						}
					}
				}
			}
			
				
				
			//message = Convert(closest);
            
		}
	}

	if(ui->keyReleased(SDL_LEFT_MOUSE_KEY))
	{
		dragging = false;
		//message = "Dragging = false.";
		//messageTime = System::time();
		std::vector<Instance*> instances_2D = dataModel->getGuiRoot()->getAllChildren();
		std::vector<Instance*> instances = dataModel->getWorkspace()->getAllChildren();
		for(size_t i = 0; i < instances_2D.size(); i++)
		{
			if(instances_2D.at(i)->getClassName() == "TextButton" || instances_2D.at(i)->getClassName() == "ImageButton")
			{
				BaseButtonInstance* button = (BaseButtonInstance*)instances_2D.at(i);
				if(button->mouseInButton(ui->mouseXY().x, ui->mouseXY().y, app->renderDevice))
				{
					button->onMouseClick();
				}
			}
		}
	}

	if (ui->keyDown(SDL_LEFT_MOUSE_KEY)) {
		if (dragging) {
		PhysicalInstance* part = (PhysicalInstance*) selectedInstance;
		Ray dragRay = app->debugCamera.worldRay(mousex, mousey, app->renderDevice->getViewport());
		std::vector<Instance*> instances = dataModel->getWorkspace()->getAllChildren();
		for(size_t i = 0; i < instances.size(); i++)
			{
				if(instances.at(i)->getClassName() == "Part")
				{
					PhysicalInstance* moveTo = (PhysicalInstance*)instances.at(i);
					float __time = testRay.intersectionTime(moveTo->getBox());
					float __nearest=std::numeric_limits<float>::infinity();
					if (__time != inf()) 
					{
						if (__nearest>__time)
						{
							Vector3 closest = (dragRay.closestPoint(moveTo->getPosition()) * 2);
							part->setPosition(closest);
							//part->setPosition(Vector3(floor(closest.x),part->getPosition().y,floor(closest.z)));
						}
					}
				}
			}
			Sleep(10);
		}
	}


	//readMouseGUIInput();
	// Add other key handling here
}





void makeFlag(Vector3 &vec, RenderDevice* &rd)
{

	Vector3 up = Vector3(vec.x, vec.y+3, vec.z);
	//Draw::lineSegment(G3D::LineSegment::fromTwoPoints(vec, up), rd, Color3::blue(), 3);
	rd->setColor(Color3::blue());
	rd->beforePrimitive();

		glBegin(GL_LINES);
		glVertex3f(vec.x, vec.y, vec.z);
		glVertex3f(up.x, up.y, up.z);
		glEnd();

		glBegin( GL_TRIANGLES );
		glVertex3f(up.x, up.y-1, up.z);
		glVertex3f(up.x, up.y-0.5, up.z-1);
		glVertex3f(up.x, up.y, up.z);
		
		glVertex3f(up.x, up.y, up.z);
		glVertex3f(up.x, up.y-0.5, up.z-1);
		glVertex3f(up.x, up.y-1, up.z);

		glEnd();
	rd->afterPrimitive();
	rd->setColor(Color3::white());
	//I know how i will approach this now
}



bool mouseInArea(float point1x, float point1y, float point2x, float point2y)
{
	

	if(mousex >= point1x && mousey >= point1y)
	{
		if(mousex < point2x && mousey < point2y)
		{
			return true;
		}
	}
	return false;
}


void drawButtons(RenderDevice* rd)
{
	std::vector<Instance*> instances_2D = dataModel->getGuiRoot()->getChildren();
	for(size_t i = 0; i < instances_2D.size(); i++)
		{
			Instance* instance = instances_2D.at(i);
			if(instance->getClassName() == "TextButton" || instance->getClassName() == "ImageButton")
			{
				BaseButtonInstance* tbi = (BaseButtonInstance*)instance;
				tbi->drawObj(rd, Vector2(mousex, mousey), mouseButton1Down);				
			}
		}
}

void drawOutline(Vector3 from, Vector3 to, RenderDevice* rd, LightingParameters lighting, Vector3 size, Vector3 pos, CoordinateFrame c)
{
	
	//rd->setLight(0, NULL);
	//rd->setAmbientLightColor(Color3(1,1,1));
	Color3 outline = Color3::cyan();//Color3(0.098F,0.6F,1.0F);
	float offsetSize = 0.05F;
	//X
	Draw::box(c.toWorldSpace(Box(Vector3(from.x - offsetSize, from.y + offsetSize, from.z + offsetSize), Vector3(to.x + offsetSize, from.y - offsetSize, from.z - offsetSize))), rd, outline, Color4::clear()); 
	Draw::box(c.toWorldSpace(Box(Vector3(from.x - offsetSize, to.y + offsetSize, from.z + offsetSize), Vector3(to.x + offsetSize, to.y - offsetSize, from.z - offsetSize))), rd, outline, Color4::clear()); 
	Draw::box(c.toWorldSpace(Box(Vector3(from.x - offsetSize, to.y + offsetSize, to.z + offsetSize), Vector3(to.x + offsetSize, to.y - offsetSize, to.z - offsetSize))), rd, outline, Color4::clear()); 
	Draw::box(c.toWorldSpace(Box(Vector3(from.x - offsetSize, from.y + offsetSize, to.z + offsetSize), Vector3(to.x + offsetSize, from.y - offsetSize, to.z - offsetSize))), rd, outline, Color4::clear()); 
	//Y
	Draw::box(c.toWorldSpace(Box(Vector3(from.x + offsetSize, from.y - offsetSize + 0.1, from.z + offsetSize), Vector3(from.x - offsetSize, to.y + offsetSize - 0.1, from.z - offsetSize))), rd, outline, Color4::clear()); 
	Draw::box(c.toWorldSpace(Box(Vector3(to.x + offsetSize, from.y - offsetSize + 0.1, from.z + offsetSize), Vector3(to.x - offsetSize, to.y + offsetSize - 0.1, from.z - offsetSize))), rd, outline, Color4::clear()); 
	Draw::box(c.toWorldSpace(Box(Vector3(to.x + offsetSize, from.y - offsetSize + 0.1, to.z + offsetSize), Vector3(to.x - offsetSize, to.y + offsetSize-0.1, to.z - offsetSize))), rd, outline, Color4::clear()); 
	Draw::box(c.toWorldSpace(Box(Vector3(from.x + offsetSize, from.y - offsetSize + 0.1, to.z + offsetSize), Vector3(from.x - offsetSize, to.y + offsetSize - 0.1, to.z - offsetSize))), rd, outline, Color4::clear()); 

	//Z
	Draw::box(c.toWorldSpace(Box(Vector3(from.x + offsetSize, from.y + offsetSize, from.z - offsetSize), Vector3(from.x - offsetSize, from.y - offsetSize, to.z + offsetSize))), rd, outline, Color4::clear()); 
	Draw::box(c.toWorldSpace(Box(Vector3(from.x + offsetSize, to.y + offsetSize, from.z - offsetSize), Vector3(from.x - offsetSize, to.y - offsetSize, to.z + offsetSize))), rd, outline, Color4::clear()); 
	Draw::box(c.toWorldSpace(Box(Vector3(to.x + offsetSize, from.y + offsetSize, from.z - offsetSize), Vector3(to.x - offsetSize, from.y - offsetSize, to.z + offsetSize))), rd, outline, Color4::clear()); 
	Draw::box(c.toWorldSpace(Box(Vector3(to.x + offsetSize, to.y + offsetSize, from.z - offsetSize), Vector3(to.x - offsetSize, to.y - offsetSize, to.z + offsetSize))), rd, outline, Color4::clear()); 
	
	if(mode == ARROWS)
	{
		rd->setLight(0, NULL);
		rd->setAmbientLightColor(Color3(1,1,1));
		
		AABox box;
		c.toWorldSpace(Box(from, to)).getBounds(box);
		float max = box.high().y - pos.y;

		Draw::arrow(pos, Vector3(0, 1.5+max, 0), rd);
		Draw::arrow(pos, Vector3(0, (-1.5)-max, 0), rd);
		
		max = box.high().x - pos.x;

		Draw::arrow(pos, Vector3(1.5+max, 0, 0), rd);
		Draw::arrow(pos, Vector3((-1.5)-max, 0, 0), rd);

		max = box.high().z - pos.z;

		Draw::arrow(pos, Vector3(0, 0, 1.5+max), rd);
		Draw::arrow(pos, Vector3(0, 0, (-1.5)-max), rd);



		rd->setAmbientLightColor(lighting.ambient);
		rd->setLight(0, GLight::directional(lighting.lightDirection, lighting.lightColor));
	}
	else if(mode == RESIZE)
	{
		//Box box = c.toWorldSpace(Box(from, to))
		Color3 sphereColor = outline;
		rd->setLight(0, NULL);
		rd->setAmbientLightColor(Color3(1,1,1));
		Vector3 gamepoint = pos;
		Vector3 camerapoint = rd->getCameraToWorldMatrix().translation;
		float distance = pow(pow((double)gamepoint.x - (double)camerapoint.x, 2) + pow((double)gamepoint.y - (double)camerapoint.y, 2) + pow((double)gamepoint.z - (double)camerapoint.z, 2), 0.5);
		if(distance < 200)
		{
			
			float multiplier = distance * 0.025F/2;
			if(multiplier < 0.25F)
				multiplier = 0.25F;
			Vector3 position = pos + (c.lookVector()*((size.z/2)+1));
			Draw::sphere(Sphere(position, multiplier), rd, sphereColor, Color4::clear());
			position = pos - (c.lookVector()*((size.z/2)+1));
			Draw::sphere(Sphere(position, multiplier), rd, sphereColor, Color4::clear());

			position = pos + (c.rightVector()*((size.x/2)+1));
			Draw::sphere(Sphere(position, multiplier), rd, sphereColor, Color4::clear());
			position = pos - (c.rightVector()*((size.x/2)+1));
			Draw::sphere(Sphere(position, multiplier), rd, sphereColor, Color4::clear());

			position = pos + (c.upVector()*((size.y/2)+1));
			Draw::sphere(Sphere(position, multiplier), rd, sphereColor, Color4::clear());
			position = pos - (c.upVector()*((size.y/2)+1));
			Draw::sphere(Sphere(position, multiplier), rd, sphereColor, Color4::clear());
			//Draw::sphere(Sphere(Vector3(pos.x, pos.y - (size.y/2 + 1), pos.z), multiplier), rd, sphereColor, Color4::clear());
			//Draw::sphere(Sphere(Vector3(pos.x + (size.x/2 + 1), pos.y, pos.z), multiplier), rd, sphereColor, Color4::clear());
			//Draw::sphere(Sphere(Vector3(pos.x - (size.x/2 + 1), pos.y, pos.z), multiplier), rd, sphereColor, Color4::clear());
			//Draw::sphere(Sphere(Vector3(pos.x, pos.y, pos.z + (size.z/2 + 1)), multiplier), rd, sphereColor, Color4::clear());
			//Draw::sphere(Sphere(Vector3(pos.x, pos.y, pos.z - (size.z/2 + 1)), multiplier), rd, sphereColor, Color4::clear());


		}
		rd->setAmbientLightColor(lighting.ambient);
		rd->setLight(0, GLight::directional(lighting.lightDirection, lighting.lightColor));
	}
	
}

void Demo::exitApplication()
{
	endApplet = true;
    app->endProgram = true;
}

void makeBeveledBox(Box box, RenderDevice* rd, Color4 color, CoordinateFrame cFrame)
{
	Vector3 v0, v1, v2, v3;
    //glDiffuse();
    rd->setColor(color);
    rd->setObjectToWorldMatrix(CoordinateFrame());
    rd->beginPrimitive(RenderDevice::QUADS);
    for (int f = 0; f < 6; ++f) {
        box.getFaceCorners(f, v0, v1, v2, v3);
		glShadeModel(GL_SMOOTH);
        //rd->setNormal((v1 - v0).cross(v3 - v0).direction());
        rd->sendVertex(v0);
        rd->sendVertex(v1);
        rd->sendVertex(v2);
        rd->sendVertex(v3);
    }
	rd->setColor(Color3::white());
    rd->endPrimitive();
}


void Demo::onGraphics(RenderDevice* rd) {
	
	float angle, x, z;
	app->debugCamera.getCoordinateFrame().rotation.toEulerAnglesXYZ(x, angle, z);
	//message = Convert(toDegrees(angle)) + " X: " + Convert(app->debugCamera.getCoordinateFrame().translation.x) + " Z: " + Convert(app->debugCamera.getCoordinateFrame().translation.z);
	//messageTime = System::time();

		CoordinateFrame frame = CoordinateFrame(app->debugCamera.getCoordinateFrame().rotation, app->debugCamera.getCoordinateFrame().translation);
	Vector2 mousepos = Vector2(0,0);
	G3D::uint8 num = 0;
	rd->window()->getRelativeMouseState(mousepos, num);
	
	bool mouseOnScreen = true;
	if(mousepos.x < 1 || mousepos.y < 1 || mousepos.x >= rd->getViewport().width()-1 || mousepos.y >= rd->getViewport().height()-1)
	{
		mouseOnScreen = false;
		rd->window()->setInputCaptureCount(0);
	}
	else
	{
		mouseOnScreen = true;
		rd->window()->setInputCaptureCount(1);
	}
	
    LightingParameters lighting(G3D::toSeconds(11, 00, 00, AM));
    app->renderDevice->setProjectionAndCameraMatrix(app->debugCamera);
	


	
	
    // Cyan background
    app->renderDevice->setColorClearValue(Color3(0.0f, 0.5f, 1.0f));

    app->renderDevice->clear(app->sky.isNull(), true, true);
    if (app->sky.notNull()) {
        app->sky->render(app->renderDevice, lighting);
    }

	
	
    // Setup lighting
    app->renderDevice->enableLighting();

		app->renderDevice->setShadeMode(RenderDevice::SHADE_SMOOTH);
		app->renderDevice->setAmbientLightColor(Color3(1,1,1));
		//Draw::axes(CoordinateFrame(Vector3(0, 0, 0)), app->renderDevice);
		//makeFlag(Vector3(-1, 3.5, 0), rd);
		
		//Vector3 vector = app->debugCamera.getCoordinateFrame().translation + app->debugCamera.getCoordinateFrame().lookVector()*20;

		app->renderDevice->setLight(0, GLight::directional(lighting.lightDirection, lighting.lightColor));
		app->renderDevice->setAmbientLightColor(lighting.ambient);

		//app->renderDevice->pushState();
		//app->renderDevice->popState();
		dataModel->getWorkspace()->render(rd);
		if(selectedInstance != NULL)
		{
			PhysicalInstance* part = (PhysicalInstance*)selectedInstance;
			Vector3 size = part->getSize();
			Vector3 pos = part->getPosition();
			drawOutline(Vector3(0+size.x/4, 0+size.y/4, 0+size.z/4) ,Vector3(0-size.x/4,0-size.y/4,0-size.z/4), rd, lighting, Vector3(size.x/2, size.y/2, size.z/2), Vector3(pos.x/2, pos.y/2, pos.z/2), part->getCFrameRenderBased());
		}
		/*std::vector<Instance*> instances = dataModel->getWorkspace()->getAllChildren();
		for(size_t i = 0; i < instances.size(); i++)
		{
			Instance* instance = instances.at(i);
			if(instance->getClassName() == "Part")
			{
				instance->render(rd);
				PhysicalInstance* part = (PhysicalInstance*)instance;
				//part->render(rd);
				//Draw::box(part->getBox(), app->renderDevice, part->color, Color4::clear());
				if(selectedInstance == part)
				{
					Vector3 size = part->getSize();
					Vector3 pos = part->getCFrame().translation;
					drawOutline(Vector3(0+size.x/4, 0+size.y/4, 0+size.z/4) ,Vector3(0-size.x/4,0-size.y/4,0-size.z/4), rd, lighting, Vector3(size.x/2, size.y/2, size.z/2), Vector3(pos.x/2, pos.y/2, pos.z/2), part->getCFrameRenderBased());
				}
				
			}
			
		}
		Box box;*/
		
		//Draw::ray(testRay, rd, Color3::orange(), 1);

		Vector3 gamepoint = Vector3(0, 5, 0);
		Vector3 camerapoint = rd->getCameraToWorldMatrix().translation;
		float distance = pow(pow((double)gamepoint.x - (double)camerapoint.x, 2) + pow((double)gamepoint.y - (double)camerapoint.y, 2) + pow((double)gamepoint.z - (double)camerapoint.z, 2), 0.5);
		if(distance < 50 && distance > -50)
		
		{
			if(distance < 0)
			distance = distance*-1;
			fntdominant->draw3D(rd, "Testing", CoordinateFrame(rd->getCameraToWorldMatrix().rotation, gamepoint), 0.04*distance, Color3::yellow(), Color3::black(), G3D::GFont::XALIGN_CENTER, G3D::GFont::YALIGN_CENTER);
		}

    app->renderDevice->disableLighting();

    if (app->sky.notNull()) {
        app->sky->renderLensFlare(app->renderDevice, lighting);
    }
	app->renderDevice->push2D();

	//std::string str = ;
	
	int offset = 25;
	if(app->debugMode())
	{
		offset = 60;
	}

	if(System::time() - 3 < messageTime)
	{
		fntdominant->draw2D(rd, message, Vector2((rd->getWidth()/2)-(fntdominant->get2DStringBounds(message, 20).x/2),(rd->getHeight()/2)-(fntdominant->get2DStringBounds(message, 20).y/2)), 20, Color3::yellow(), Color3::black());
	}

	std::stringstream stream;
	stream << std::fixed << std::setprecision(1) << dataModel->getWorkspace()->timer;
	fntdominant->draw2D(rd, "Timer: " + stream.str(), Vector2(rd->getWidth() - 120, 0+offset), 20, Color3::fromARGB(0x81C518), Color3::black());
	fntdominant->draw2D(rd, "Score: " + Convert(dataModel->getWorkspace()->score), Vector2(rd->getWidth() - 120, 25+offset), 20, Color3::fromARGB(0x81C518), Color3::black());
	
	//GUI Boxes

	
	Draw::box(G3D::Box(Vector3(0,offset,0),Vector3(80,330+offset,0)),rd,Color4(0.6F,0.6F,0.6F,0.4F), Color4(0,0,0,0));
	//Draw::box(G3D::Box(Vector3(0,rd->getHeight() - 120,0),Vector3(80,rd->getHeight(),0)),rd,Color4(0.6F,0.6F,0.6F,0.4F), Color4(0,0,0,0));
	Draw::box(G3D::Box(Vector3(rd->getWidth() - 120,rd->getHeight() - 120,0),Vector3(rd->getWidth(),rd->getHeight(),0)),rd,Color4(0.6F,0.6F,0.6F,0.4F), Color4(0,0,0,0));
	

	//Camera menu title

	

	fntlighttrek->draw2D(rd, "CameraMenu", Vector2(rd->getWidth()-(fntlighttrek->get2DStringBounds("CameraMenu", 14).x+1),rd->getHeight() - 120), 14, Color3::white(), Color4(0.5F,0.5F,0.5F,0.5F));


	/*
	fntlighttrek->draw2D(rd, "Model", Vector2(10,rd->getHeight() - (120 - spacing*0)), 12, Color3(0,255,255), Color4(0,0,0,0));
	fntlighttrek->draw2D(rd, "Surface", Vector2(10,rd->getHeight() - (120 - spacing*1)), 12, Color3(0,255,255), Color4(0,0,0,0));
	fntlighttrek->draw2D(rd, "Color", Vector2(10,rd->getHeight() - (120 - spacing*2)), 12, Color3(0,255,255), Color4(0,0,0,0));
	fntlighttrek->draw2D(rd, "Controller", Vector2(10,rd->getHeight() - (120 - spacing*3)), 12, Color3(0,255,255), Color4(0,0,0,0));
	fntlighttrek->draw2D(rd, "Hopper", Vector2(10,rd->getHeight() - (120 - spacing*4)), 12, Color3(0,255,255), Color4(0,0,0,0));
	*/


	//Tools menu
	Draw::box(G3D::Box(Vector3(5, 185+offset,0),Vector3(75, 185+offset,0)),rd,Color4(0.6F,0.6F,0.6F,0.4F), Color4(0.6F,0.6F,0.6F,0.4F));
	fntlighttrek->draw2D(rd,"MENU", Vector2(10,307+offset), 14, Color3::white(), Color4(0.5F,0.5F,0.5F,0.5F));
	//G3D::GFont::draw2D("Debug Mode Enabled", Vector2(0,30), 20, Color3::white(), Color3::black());
	//app->debugFont->draw2D("Dynamica 2004-2005 Simulation Client version " + VERSION + str, Vector2(0,0), 20, Color3::white(), Color3::black());
	//app->debugFont->draw2D("Debug Mode Enabled", Vector2(0,30), 20, Color3::white(), Color3::black());

	
	drawButtons(rd);
	rd->pushState();
		rd->beforePrimitive();

		if(showMouse && mouseOnScreen)
		{
		glEnable( GL_TEXTURE_2D );
		glEnable(GL_BLEND);// you enable blending function
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); 
		
		
		glBindTexture( GL_TEXTURE_2D, cursorid);

		
		glBegin( GL_QUADS );
		glTexCoord2d(0.0,0.0);
		glVertex2f(mousepos.x-40, mousepos.y-40);
		glTexCoord2d( 1.0,0.0 );
		glVertex2f(mousepos.x+40, mousepos.y-40);
		glTexCoord2d(1.0,1.0 );
		glVertex2f(mousepos.x+40, mousepos.y+40 );
		glTexCoord2d( 0.0,1.0 );
		glVertex2f( mousepos.x-40, mousepos.y+40 );
		glEnd();

		glDisable( GL_TEXTURE_2D );
		}

		rd->afterPrimitive();

	rd->popState();



	


	

	app->renderDevice->pop2D();


	
}



void App::main() {
	usableApp = this;
	setDebugMode(false);
	debugController.setActive(false);
    // Load objects here
	go = Texture::fromFile(GetFileInPath("/content/images/Run.png"));
	go_ovr = Texture::fromFile(GetFileInPath("/content/images/Run_ovr.png"));
	go_dn = Texture::fromFile(GetFileInPath("/content/images/Run_dn.png"));
	cursor = Texture::fromFile(GetFileInPath("/content/cursor2.png"));
	fntdominant = GFont::fromFile(GetFileInPath("/content/font/dominant.fnt"));
	fntlighttrek = GFont::fromFile(GetFileInPath("/content/font/lighttrek.fnt"));
	cameraSound = GetFileInPath("/content/sounds/SWITCH3.wav");
	clickSound = GetFileInPath("/content/sounds/switch.wav");
	dingSound = GetFileInPath("/content/sounds/electronicpingshort.wav");
    sky = Sky::create(NULL, ExePath() + "/content/sky/");
	cursorid = cursor->openGLID();
    applet->run();
}



//App::App(const GAppSettings& settings, GWindow* wnd) : GApp(settings, wnd) {
//    applet = new Demo(this);
//}

App::App(const GAppSettings& settings, GWindow* wnd,HWND tempMainHWnd, SDLWindow* wndSDL) : GApp(settings, wnd) {
    applet = new Demo(this);
    hwnd = wndSDL->win32HWND();
    mainHWnd = tempMainHWnd;
    propertyHWnd = CreateWindowEx(
        WS_EX_TOOLWINDOW,
        "ToolWindowClass", "ToolWindow",
        WS_SYSMENU | WS_THICKFRAME | WS_VISIBLE | WS_CHILD,
        200, 700, 400, 64,
        mainHWnd, NULL, GetModuleHandle(0), NULL
    );
}


App::~App() {
    delete applet;
}


LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    App *app = (App *)GetWindowLongPtr(hwnd, GWL_USERDATA);
    switch(msg)
    {
        case WM_CLOSE:
        if (app != 0)
        {
			
            HWND g3DWind = app->getHWND();
			app->applet->exitApplication();
            //DestroyWindow(hwnd);
        }
        //DestroyWindow(hwnd);
        break;
        case WM_DESTROY:
            PostQuitMessage(0);
        break;
		case WM_SIZE:
			if(app != 0)
			{
				HWND g3DWind = app->getHWND();
				int width = 640;
				int height = 480;
				RECT rect;
				if(GetClientRect(hwnd, &rect))
				{
				  width = rect.right - rect.left;
				  height = rect.bottom - rect.top;
				}
				SetWindowPos(g3DWind, NULL, 0, 0, width, height, NULL);
			}
		break;
		case WM_MOUSEMOVE:
			  {
				  if(app != 0)
				  {
					  POINT p;
					  if(GetCursorPos(&p))
					  {
						HWND wnd = WindowFromPoint(p);
						if(wnd != app->getHWND())
						{
							app->window()->setInputCaptureCount(0);
						}
						else
						{
							app->window()->setInputCaptureCount(200);
						}
					  }
				  }
			  }
        default:
		{
            return DefWindowProc(hwnd, msg, wParam, lParam);
		}
    }
    return 0;
}

int main(int argc, char** argv) {
	//_CrtSetDbgFlag( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF );
	//_CrtSetBreakAlloc(1279);
	try{
		tempPath = ((std::string)getenv("temp")) + "/Dynamica";
	CreateDirectory(tempPath.c_str(), NULL);
    
	message = tempPath;
	messageTime = System::time();
	AudioPlayer::init();
    GAppSettings settings;
	settings.window.resizable = true;
	//settings.window.fsaaSamples = 8;
	settings.writeLicenseFile = false;
	settings.logFilename = tempPath + "/g3dlog.txt";
	settings.window.center = true;
	//Using the damned SDL window now
	G3D::SDLWindow* wnd = new SDLWindow(settings.window);
	//wnd->setInputCaptureCount(200);
	wnd->setMouseVisible(false);
	


	WNDCLASSEX wc;
    HINSTANCE hInstance = GetModuleHandle(NULL);
    wc.cbSize        = sizeof(WNDCLASSEX);
    wc.style         = 0;
    wc.lpfnWndProc   = WndProc;
    wc.cbClsExtra    = 0;
    wc.cbWndExtra    = 0;
    wc.hInstance     = hInstance;
    wc.hIcon         = LoadIcon(NULL, IDI_APPLICATION);
    wc.hCursor       = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW+1);
    wc.lpszMenuName  = NULL;
    wc.lpszClassName = "containerHWND";
    wc.hIconSm       = LoadIcon(NULL, IDI_APPLICATION);
	
	if (!RegisterClassEx (&wc))
            return false;

	HMODULE hThisInstance = GetModuleHandle(NULL);
	HWND hwnd = wnd->win32HWND();
	    HWND hwndMain = CreateWindowEx(
        WS_EX_ACCEPTFILES | WS_EX_CLIENTEDGE,
        "containerHWND",
        "Main test",
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT,
        CW_USEDEFAULT,
        800,
        600,
        NULL, // parent
        NULL, // menu
        hThisInstance,
        NULL
    );
	ShowWindow(hwndMain, SW_SHOW);
	if(hwndMain == NULL)
	{
		MessageBox(NULL, "Failed to create HWND","Dynamica Crash", MB_OK);
		return 0;
	}
    SetParent(hwnd, hwndMain);
	App app = App(settings, wnd, hwndMain, wnd);
	RECT rect;
	int width = 640;
	int height = 480;
	if(GetClientRect(hwndMain, &rect))
	{
	  width = rect.right - rect.left;
	  height = rect.bottom - rect.top;
	}
	SetWindowPos(hwnd, NULL, 0, 0, width, height, NULL);
	
	LONG lStyle = GetWindowLong(hwnd, GWL_STYLE);
	lStyle &= ~(WS_CAPTION | WS_THICKFRAME | WS_MINIMIZEBOX | WS_MAXIMIZEBOX | WS_SYSMENU);
	SetWindowLong(hwnd, GWL_STYLE, lStyle);

	LONG lExStyle = GetWindowLong(hwnd, GWL_EXSTYLE);
	lExStyle &= ~(WS_EX_DLGMODALFRAME | WS_EX_CLIENTEDGE | WS_EX_STATICEDGE);
	SetWindowLong(hwnd, GWL_EXSTYLE, lExStyle);
	
	//SetWindowLong(hwnd, GWL_STYLE, WS_VISIBLE | WS_CHILD);
	SetWindowLongPtr(hwndMain, GWL_USERDATA, (LONG)&app);
	HICON hicon = (HICON)LoadImage(GetModuleHandleW(NULL), (LPCSTR)MAKEINTRESOURCEW(IDI_ICON1), IMAGE_ICON, 0, 0, LR_DEFAULTCOLOR | LR_DEFAULTSIZE);
	SendMessage(hwndMain, WM_SETICON, ICON_BIG, (LPARAM)hicon);
	
	
	
	SetWindowPos(hwndMain, NULL, 0, 0, 800, 600, NULL);
	
	
	if(GetClientRect(hwndMain, &rect))
	{
		width = rect.right - rect.left;
		height = rect.bottom - rect.top;
	}
	SetWindowPos(hwnd, NULL, 0, 0, width, height, NULL);

	//message = Convert(widthMON) + ", " + Convert(heightMON);
	//messageTime = G3D::System::time();

	app.run();
	}
	catch(...)
	{
		OnError(-1);
	}
    return 0;
}
