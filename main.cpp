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
#include "Instance.h"
#include "resource.h"
#include "PhysicalInstance.h"
#include "TextButtonInstance.h"
#include "ImageButtonInstance.h"


#if G3D_VER < 61000
	#error Requires G3D 6.10
#endif
HWND hwnd;
static const float VNUM = 0.01F;
static std::string title = "";
static const std::string VERSION = "PRE-ALPHA ";
static std::vector<Instance*> instances;
static std::vector<Instance*> instances_2D;
static Instance* dataModel;
GFontRef fntdominant = NULL;
GFontRef fntlighttrek = NULL;
static bool democ = true;
static std::string message = "";
static G3D::RealTime messageTime = 0;
static G3D::RealTime inputTime = 0;
static int FPSVal[8] = {10, 20, 30, 60, 120, 240, INT_MAX,1};
static int index = 2;
static float TIMERVAL = 60.0F;
static int SCOREVAL = 0;
static G3D::TextureRef go = NULL;
static G3D::TextureRef go_ovr = NULL;
static G3D::TextureRef go_dn = NULL;
static float mousex = 0;
static float mousey = 0;
static int go_id = 0;
static int go_ovr_id = 0;
static int go_dn_id = 0;
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
static const int CURSOR = 0;
static const int ARROWS = 1;
static const int RESIZE = 2;
static int mode = CURSOR;
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



class App : public GApp {
protected:
    void main();
public:
    SkyRef              sky;

    Demo*               applet;

    App(const GAppSettings& settings, GWindow* wnd);

    ~App();
};
 

Demo::Demo(App* _app) : GApplet(_app), app(_app) {
}

void clearInstances()
{
	for(size_t i = 0; i < instances.size(); i++)
	{
		delete instances.at(i);
	}
	delete dataModel;
}

void OnError(int err, std::string msg = "")
{
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
	instances.push_back(part);
	return part;
}

TextButtonInstance* makeTextButton()
{
	TextButtonInstance* part = new TextButtonInstance();
	instances.push_back(part);
	instances_2D.push_back(part);
	return part;
}

ImageButtonInstance* makeImageButton(G3D::TextureRef newImage = NULL, G3D::TextureRef overImage = NULL, G3D::TextureRef downImage = NULL)
{
	ImageButtonInstance* part = new ImageButtonInstance(newImage,overImage, downImage);
	instances.push_back(part);
	instances_2D.push_back(part);
	return part;
}


void initGUI()
{
	TextButtonInstance* button = makeTextButton();
	button->boxBegin = Vector2(0, -24);
	button->boxEnd = Vector2(80, 0);
	button->floatBottom = true;
	button->parent = dataModel;
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
	button->parent = dataModel;
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
	button->parent = dataModel;
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
	button->parent = dataModel;
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
	button->parent = dataModel;
	button->font = fntlighttrek;
	button->textColor = Color3(0,255,255);
	button->boxOutlineColor = Color3(0,255,255);
	button->title = "Model";
	button->fontLocationRelativeTo = Vector2(10, 3);
	button->setAllColorsSame();

	button = makeTextButton();
	button->boxBegin = Vector2(0, 0);
	button->boxEnd = Vector2(125, 25);
	button->parent = dataModel;
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
	button->parent = dataModel;
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
	button->parent = dataModel;
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
	button->parent = dataModel;
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
	button->parent = dataModel;
	button->font = fntlighttrek;
	button->textColor = Color3::white();
	button->boxColor = Color4::clear();
	button->textOutlineColor = Color4(0.5F,0.5F,0.5F,0.5F);
	button->title = "Format";
	button->textSize = 16;
	button->fontLocationRelativeTo = Vector2(10, 0);
	button->setAllColorsSame();

	ImageButtonInstance* instance = makeImageButton(go, go_ovr, go_dn);
	instance->size = Vector2(60,60);
	instance->position = Vector2(10, 25);
	instance->parent = dataModel;
}

void Demo::onInit()  {
	
    // Called before Demo::run() beings
	

	dataModel = new Instance();
	dataModel->parent = NULL;
	dataModel->name = "undefined";
	
	initGUI();

	
	PhysicalInstance* test = makePart();
	test->parent = dataModel;
	test->color = Color3(0.2F,0.3F,1);
	test->size = Vector3(24,1,24);

	

	
	test = makePart();
	test->parent = dataModel;
	test->color = Color3(.5F,1,.5F);
	test->size = Vector3(4,1,2);
	test->position = Vector3(10,1,0);
	test = makePart();
	test->parent = dataModel;
	test->color = Color3(.5F,1,.5F);
	test->size = Vector3(4,1,2);
	test->position = Vector3(-10,1,0);

	test = makePart();
	test->parent = dataModel;
	test->color = Color3::gray();
	test->size = Vector3(4,1,2);
	test->position = Vector3(-7,2,0);

	test = makePart();
	test->parent = dataModel;
	test->color = Color3::gray();
	test->size = Vector3(4,1,2);
	test->position = Vector3(7,2,0);

	test = makePart();
	test->parent = dataModel;
	test->color = Color3::gray();
	test->size = Vector3(4,1,2);
	test->position = Vector3(-4,3,0);

	test = makePart();
	test->parent = dataModel;
	test->color = Color3::gray();
	test->size = Vector3(4,1,2);
	test->position = Vector3(5,3,0);

	test = makePart();
	test->parent = dataModel;
	test->color = Color3::gray();
	test->size = Vector3(4,1,2);
	test->position = Vector3(-1,4,0);

	test = makePart();
	test->parent = dataModel;
	test->color = Color3::gray();
	test->size = Vector3(4,1,2);
	test->position = Vector3(3,4,0);

	test = makePart();
	test->parent = dataModel;
	test->color = Color3::gray();
	test->size = Vector3(4,1,2);
	test->position = Vector3(2,5,0);

	selectedInstance = test;

	test = makePart();
	test->parent = dataModel;
	test->color = Color3::gray();
	test->size = Vector3(4,1,2);
	test->position = Vector3(0,6,0);

	test = makePart();
	test->parent = dataModel;
	test->color = Color3::gray();
	test->size = Vector3(4,1,2);
	test->position = Vector3(-2,7,0);

	
	



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
}


void Demo::onNetwork() {
	// Poll net messages here
}


void Demo::onSimulation(RealTime rdt, SimTime sdt, SimTime idt) {
	if(dataModel->name != title)
	{
		title = dataModel->name;
		app->renderDevice->setCaption("Game \"" + title + "\"");
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
		CoordinateFrame frame = app->debugCamera.getCoordinateFrame();
		cameraPos = cameraPos + frame.lookVector()*2;
	}
	if(ui->keyPressed(SDL_MOUSE_WHEEL_DOWN_KEY))
	{
		CoordinateFrame frame = app->debugCamera.getCoordinateFrame();
		cameraPos = cameraPos - frame.lookVector()*2;
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
	if(ui->keyPressed('u'))
	{
		DialogBox(NULL, MAKEINTRESOURCE(IDD_ABOUT_DIALOG), NULL, NULL);
	}
	mousex = ui->getMouseX();
	mousey = ui->getMouseY();
	mouseButton1Down = ui->keyDown(SDL_LEFT_MOUSE_KEY);
	messageTime = System::time();
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
	for(size_t i = 0; i < instances_2D.size(); i++)
		{
			Instance* instance = instances_2D.at(i);
			if((instance->className == "TextButton" || instance->className == "ImageButton") && instance->parent == dataModel)
			{
				BaseButtonInstance* tbi = (BaseButtonInstance*)instance;
				tbi->drawObj(rd, Vector2(mousex, mousey), mouseButton1Down);				
			}
		}
}

void drawOutline(Vector3 from, Vector3 to, RenderDevice* rd, LightingParameters lighting, Vector3 size, Vector3 pos)
{
	rd->setLight(0, NULL);
	rd->setAmbientLightColor(Color3(1,1,1));
	Color3 outline = Color3(0.098F,0.6F,1.0F);
	float offsetSize = 0.05F;
	//X
	Draw::box(Box(Vector3(from.x - offsetSize, from.y + offsetSize, from.z + offsetSize), Vector3(to.x + offsetSize, from.y - offsetSize, from.z - offsetSize)), rd, outline, Color4::clear()); 
	Draw::box(Box(Vector3(from.x - offsetSize, to.y + offsetSize, from.z + offsetSize), Vector3(to.x + offsetSize, to.y - offsetSize, from.z - offsetSize)), rd, outline, Color4::clear()); 
	Draw::box(Box(Vector3(from.x - offsetSize, to.y + offsetSize, to.z + offsetSize), Vector3(to.x + offsetSize, to.y - offsetSize, to.z - offsetSize)), rd, outline, Color4::clear()); 
	Draw::box(Box(Vector3(from.x - offsetSize, from.y + offsetSize, to.z + offsetSize), Vector3(to.x + offsetSize, from.y - offsetSize, to.z - offsetSize)), rd, outline, Color4::clear()); 
	//Y
	Draw::box(Box(Vector3(from.x + offsetSize, from.y - offsetSize, from.z + offsetSize), Vector3(from.x - offsetSize, to.y + offsetSize, from.z - offsetSize)), rd, outline, Color4::clear()); 
	Draw::box(Box(Vector3(to.x + offsetSize, from.y - offsetSize, from.z + offsetSize), Vector3(to.x - offsetSize, to.y + offsetSize, from.z - offsetSize)), rd, outline, Color4::clear()); 
	Draw::box(Box(Vector3(to.x + offsetSize, from.y - offsetSize, to.z + offsetSize), Vector3(to.x - offsetSize, to.y + offsetSize, to.z - offsetSize)), rd, outline, Color4::clear()); 
	Draw::box(Box(Vector3(from.x + offsetSize, from.y - offsetSize, to.z + offsetSize), Vector3(from.x - offsetSize, to.y + offsetSize, to.z - offsetSize)), rd, outline, Color4::clear()); 

	//Z
	Draw::box(Box(Vector3(from.x + offsetSize, from.y + offsetSize, from.z - offsetSize), Vector3(from.x - offsetSize, from.y - offsetSize, to.z + offsetSize)), rd, outline, Color4::clear()); 
	Draw::box(Box(Vector3(from.x + offsetSize, to.y + offsetSize, from.z - offsetSize), Vector3(from.x - offsetSize, to.y - offsetSize, to.z + offsetSize)), rd, outline, Color4::clear()); 
	Draw::box(Box(Vector3(to.x + offsetSize, from.y + offsetSize, from.z - offsetSize), Vector3(to.x - offsetSize, from.y - offsetSize, to.z + offsetSize)), rd, outline, Color4::clear()); 
	Draw::box(Box(Vector3(to.x + offsetSize, to.y + offsetSize, from.z - offsetSize), Vector3(to.x - offsetSize, to.y - offsetSize, to.z + offsetSize)), rd, outline, Color4::clear()); 

	mode = RESIZE;
	
	if(mode == ARROWS)
	{
		float max = size.x;
		if(abs(size.y) > max)
			max = size.y;
		if(abs(size.z) > max)
			max = size.z;
		max = max / 2;
		Draw::arrow(pos, Vector3(0, 1+max, 0), rd);
		Draw::arrow(pos, Vector3(1+max, 0, 0), rd);
		Draw::arrow(pos, Vector3(0, 0, 1+max), rd);
		Draw::arrow(pos, Vector3(0, (-1)-max, 0), rd);
		Draw::arrow(pos, Vector3((-1)-max, 0, 0), rd);
		Draw::arrow(pos, Vector3(0, 0, (-1)-max), rd);
	}
	else if(mode == RESIZE)
	{
		Vector3 gamepoint = pos;
		Vector3 camerapoint = rd->getCameraToWorldMatrix().translation;
		float distance = pow(pow((double)gamepoint.x - (double)camerapoint.x, 2) + pow((double)gamepoint.y - (double)camerapoint.y, 2) + pow((double)gamepoint.z - (double)camerapoint.z, 2), 0.5);
		if(distance < 200)
		{
		Color3 sphereColor = outline;
		float multiplier = distance * 0.025F/2;
		if(multiplier < 0.25F)
			multiplier = 0.25F;
		
		Draw::sphere(Sphere(Vector3(pos.x, pos.y + (size.y/2 + 1), pos.z), multiplier), rd, sphereColor, Color4::clear());
		Draw::sphere(Sphere(Vector3(pos.x, pos.y - (size.y/2 + 1), pos.z), multiplier), rd, sphereColor, Color4::clear());
		Draw::sphere(Sphere(Vector3(pos.x + (size.x/2 + 1), pos.y, pos.z), multiplier), rd, sphereColor, Color4::clear());
		Draw::sphere(Sphere(Vector3(pos.x - (size.x/2 + 1), pos.y, pos.z), multiplier), rd, sphereColor, Color4::clear());
		Draw::sphere(Sphere(Vector3(pos.x, pos.y, pos.z + (size.z/2 + 1)), multiplier), rd, sphereColor, Color4::clear());
		Draw::sphere(Sphere(Vector3(pos.x, pos.y, pos.z - (size.z/2 + 1)), multiplier), rd, sphereColor, Color4::clear());
		}
	}

	rd->setAmbientLightColor(lighting.ambient);
	rd->setLight(0, GLight::directional(lighting.lightDirection, lighting.lightColor));
}

void Demo::onGraphics(RenderDevice* rd) {

	

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

		app->renderDevice->setAmbientLightColor(Color3(1,1,1));
		Draw::axes(CoordinateFrame(Vector3(0, 0, 0)), app->renderDevice);

		makeFlag(Vector3(-1, 3.5, 0), rd);
		

		app->renderDevice->setLight(0, GLight::directional(lighting.lightDirection, lighting.lightColor));
		app->renderDevice->setAmbientLightColor(lighting.ambient);

		for(size_t i = 0; i < instances.size(); i++)
		{
			Instance* instance = instances.at(i);
			if(instance->className == "Part" && instance->parent != NULL)
			{
				PhysicalInstance* part = (PhysicalInstance*)instance;
				Vector3 size = part->size;
				Vector3 pos = part->position;
				Vector3 pos2 = Vector3((pos.x-size.x/2)/2,(pos.y-size.y/2)/2,(pos.z-size.z/2)/2);
				Vector3 pos3 = Vector3((pos.x+size.x/2)/2,(pos.y+size.y/2)/2,(pos.z+size.z/2)/2);
				Draw::box(Box(pos2 ,pos3), app->renderDevice, part->color, Color4::clear());
				if(selectedInstance == part)
				{
					drawOutline(pos2, pos3, rd, lighting, Vector3(size.x/2, size.y/2, size.z/2), Vector3(pos.x/2, pos.y/2, pos.z/2));
				}
				
			}
			
		}
	
		

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

	fntdominant->draw2D(rd, "Timer: " + Convert(TIMERVAL), Vector2(rd->getWidth() - 120, 0+offset), 20, Color3::fromARGB(0x81C518), Color3::black());
	fntdominant->draw2D(rd, "Score: " + Convert(SCOREVAL), Vector2(rd->getWidth() - 120, 25+offset), 20, Color3::fromARGB(0x81C518), Color3::black());
	
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
	Draw::box(G3D::Box(Vector3(5, 165+offset,0),Vector3(75, 165+offset,0)),rd,Color4(0.6F,0.6F,0.6F,0.4F), Color4(0.6F,0.6F,0.6F,0.4F));
	fntlighttrek->draw2D(rd,"Group", Vector2(10,170+offset), 12, Color3::white(), Color4(0.5F,0.5F,0.5F,0.5F));
	fntlighttrek->draw2D(rd,"UnGroup", Vector2(10,195+offset), 12, Color3::white(), Color4(0.5F,0.5F,0.5F,0.5F));
	fntlighttrek->draw2D(rd,"Duplicate", Vector2(10,220+offset), 12, Color3::white(), Color4(0.5F,0.5F,0.5F,0.5F));
	fntlighttrek->draw2D(rd,"MENU", Vector2(10,305+offset), 16, Color3::white(), Color4(0.5F,0.5F,0.5F,0.5F));
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
	setDebugMode(false);
	debugController.setActive(false);
    // Load objects here
	go = Texture::fromFile(GetFileInPath("/content/images/Run.png"));
	go_ovr = Texture::fromFile(GetFileInPath("/content/images/Run_ovr.png"));
	go_dn = Texture::fromFile(GetFileInPath("/content/images/Run_dn.png"));
	cursor = Texture::fromFile(GetFileInPath("/content/cursor.png"));
	go_id = go->getOpenGLID();
	go_dn_id = go_dn->getOpenGLID();
	go_ovr_id = go_ovr->getOpenGLID();
	fntdominant = GFont::fromFile(GetFileInPath("/content/font/dominant.fnt"));
	fntlighttrek = GFont::fromFile(GetFileInPath("/content/font/lighttrek.fnt"));
    sky = Sky::create(NULL, ExePath() + "/content/sky/");
	cursorid = cursor->openGLID();
    applet->run();
}



App::App(const GAppSettings& settings, GWindow* wnd) : GApp(settings, wnd) {
    applet = new Demo(this);
}


App::~App() {
    delete applet;
}


LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    switch(msg)
    {
        case WM_CLOSE:
            DestroyWindow(hwnd);
        break;
        case WM_DESTROY:
            PostQuitMessage(0);
        break;
        default:
            return DefWindowProc(hwnd, msg, wParam, lParam);
    }
    return 0;
}

int main(int argc, char** argv) {
	//_CrtSetDbgFlag( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF );
	//_CrtSetBreakAlloc(1279);

    GAppSettings settings;
	if(getOSVersion() > 5.0)
		settings.window.defaultIconFilename = GetFileInPath("/content/images/rico.png");
	else
		settings.window.defaultIconFilename = GetFileInPath("/content/images/rico256c.png");
	settings.window.resizable = true;
	settings.writeLicenseFile = false;

	//Using the damned SDL window now
	SDLWindow* wnd = new SDLWindow(settings.window);
	//wnd->setInputCaptureCount(200);
	wnd->setMouseVisible(false);
	App app = App(settings, wnd);
	HWND hwnd = wnd->win32HWND();
	
	app.run();
    return 0;
}
