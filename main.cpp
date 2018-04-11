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

#if G3D_VER < 61000
	#error Requires G3D 6.10
#endif
static const float VNUM = 0.01F;
static const std::string VERSION = "PRE-ALPHA ";
static std::vector<Instance> Instances;
static GFontRef fntdominant = NULL;
static GFontRef fntlighttrek = NULL;
static bool democ = true;
static std::string message = "";
static G3D::RealTime messageTime = 0;
static int FPSVal[7] = {10, 20, 30, 60, 120, 240, INT_MAX};
static int index = 2;
static float TIMERVAL = 60.0F;
static int SCOREVAL = 0;
static int sep = 125;
static int spacing = 25;
static G3D::TextureRef go = NULL;
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

    App(const GAppSettings& settings);

    ~App();
};
 
Demo::Demo(App* _app) : GApplet(_app), app(_app) {
}

#include <sstream>
std::string Convert (float number){
    std::ostringstream buff;
    buff<<number;
    return buff.str();   
}

void Demo::onInit()  {
	
    // Called before Demo::run() beings
	setDesiredFrameRate(FPSVal[index]);
    app->debugCamera.setPosition(Vector3(0, 2, 10));
    app->debugCamera.lookAt(Vector3(0, 2, 0));
	//std::string str = "Dynamica Duomillenium 5 Version " + VERSION + Convert(VNUM);
	std::string str = "Game \"undefined\"";
	app->renderDevice->setCaption(str);
    GApplet::onInit();
}

void OnError(int err, std::string msg = "")
{
	std::string emsg = "An unexpected error has occured and DUOM 5 has to quit. We're sorry!" + msg;
	MessageBox(NULL, emsg.c_str(),"Dynamica Crash", MB_OK);
	exit(err);
}

void Demo::onCleanup() {
    // Called when Demo::run() exits
	
}


void Demo::onLogic() {
    // Add non-simulation game logic and AI code here
}


void Demo::onNetwork() {
	// Poll net messages here
}


void Demo::onSimulation(RealTime rdt, SimTime sdt, SimTime idt) {
	
}


void Demo::onUserInput(UserInput* ui) {
    if (ui->keyPressed(SDLK_ESCAPE)) {
        // Even when we aren't in debug mode, quit on escape.
        endApplet = true;
        app->endProgram = true;
    }
	if(ui->keyPressed(SDL_RIGHT_MOUSE_KEY))
	{
		app->debugController.setActive(true);
	}
	if(ui->keyPressed(SDLK_KP_PLUS))
	{
		spacing++;
		messageTime = System::time();
		message = "Spacing set to " + Convert(spacing);
	}
	if(ui->keyPressed(SDLK_KP_MINUS))
	{
		spacing--;
		messageTime = System::time();
		message = "Spacing set to " + Convert(spacing);
		OnError(3423);
	}
	else if(ui->keyReleased(SDL_RIGHT_MOUSE_KEY))
	{
		app->debugController.setActive(false);
	}
	if(ui->keyDown(SDLK_LCTRL))
	{
		if(ui->keyPressed('d'))
		{
			messageTime = System::time();
			if(app->debugMode())
				message = "Debug Mode Disabled";
			else
				message = "Debug Mode Enabled";
			app->setDebugMode(!app->debugMode());
		}
	}
	if(ui->keyPressed(SDLK_F8))
	{
		index++;
		if(index >= 7)
		{
			index = 0;
		}
		messageTime = System::time();
		message = "FPS has been set to " + Convert(FPSVal[index]);
		setDesiredFrameRate(FPSVal[index]);
	}

	// Add other key handling here
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

void makeFlag(Vector3 &vec, RenderDevice* &rd)
{
	Vector3 up = Vector3(vec.x, vec.y+3, vec.z);
	Draw::lineSegment(G3D::LineSegment::fromTwoPoints(vec, up), rd, Color3::blue());
	G3D::Array<Vector2> parray;
	parray.push(Vector2(up.x, up.y));
	parray.push(Vector2(up.x-1, up.y-.5));
	parray.push(Vector2(up.x, up.y-1));
	Draw::poly2D(parray, rd, Color3::blue());
	//rd->pushState();
	//rd->beginPrimitive(RenderDevice::QUADS);
	//rd->setColor(Color4(0,0,1,1));
	//	rd->sendVertex(up);
	//	rd->sendVertex(Vector3(up.x-1, up.y-1, up.z));
	//	rd->sendVertex(Vector3(up.x, up.y-2, up.z));
	//rd->endPrimitive();
	//rd->popState();
}

void Demo::onGraphics(RenderDevice* rd) {
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


		makeFlag(Vector3(1, 0.5, 0.5), rd);
		
		

		app->renderDevice->setLight(0, GLight::directional(lighting.lightDirection, lighting.lightColor));
		app->renderDevice->setAmbientLightColor(lighting.ambient);

		Draw::box(G3D::Box(Vector3(4.0/2,1.0/2,2.0/2),Vector3(0,0,0)), rd, Color3::gray(), Color4(0,0,0,0));
		
		Draw::cylinder(G3D::Cylinder::Cylinder(Vector3(0,5,0),Vector3(0,10,0),1),app->renderDevice,Color4(0,0,1,0.5),Color4(0,0,0,0));
		
		

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
	//fntlighttrek->draw2D(rd, "Button: " + button, Vector2(10,30 + offset), 15, Color3::white(), Color3::black());
	
	//GUI Boxes

	
	Draw::box(G3D::Box(Vector3(0,offset,0),Vector3(80,330+offset,0)),rd,Color4(0.6F,0.6F,0.6F,0.4F), Color4(0,0,0,0));
	Draw::box(G3D::Box(Vector3(0,rd->getHeight() - 120,0),Vector3(80,rd->getHeight(),0)),rd,Color4(0.6F,0.6F,0.6F,0.4F), Color4(0,0,0,0));

	Draw::box(G3D::Box(Vector3(rd->getWidth() - 120,rd->getHeight() - 120,0),Vector3(rd->getWidth(),rd->getHeight(),0)),rd,Color4(0.6F,0.6F,0.6F,0.4F), Color4(0,0,0,0));
	

	//Camera menu title

	

	fntlighttrek->draw2D(rd, "CameraMenu", Vector2(rd->getWidth()-(fntlighttrek->get2DStringBounds("CameraMenu", 14).x+1),rd->getHeight() - 120), 14, Color3::white(), Color4(0.5F,0.5F,0.5F,0.5F));


	fntlighttrek->draw2D(rd, "Model", Vector2(10,rd->getHeight() - (120 - spacing*0)), 12, Color3(0,255,255), Color4(0,0,0,0));
	fntlighttrek->draw2D(rd, "Surface", Vector2(10,rd->getHeight() - (120 - spacing*1)), 12, Color3(0,255,255), Color4(0,0,0,0));
	fntlighttrek->draw2D(rd, "Color", Vector2(10,rd->getHeight() - (120 - spacing*2)), 12, Color3(0,255,255), Color4(0,0,0,0));
	fntlighttrek->draw2D(rd, "Controller", Vector2(10,rd->getHeight() - (120 - spacing*3)), 12, Color3(0,255,255), Color4(0,0,0,0));
	fntlighttrek->draw2D(rd, "Hopper", Vector2(10,rd->getHeight() - (120 - spacing*4)), 12, Color3(0,255,255), Color4(0,0,0,0));


	//Top menu
	fntlighttrek->draw2D(rd,"File", Vector2(10+0*sep,0), 16, Color3::white(), Color4(0.5F,0.5F,0.5F,0.5F));
	fntlighttrek->draw2D(rd,"Edit", Vector2(10+1*sep,0), 16, Color3::white(), Color4(0.5F,0.5F,0.5F,0.5F));
	fntlighttrek->draw2D(rd,"View", Vector2(10+2*sep,0), 16, Color3::white(), Color4(0.5F,0.5F,0.5F,0.5F));
	fntlighttrek->draw2D(rd,"Insert", Vector2(10+3*sep,0), 16, Color3::white(), Color4(0.5F,0.5F,0.5F,0.5F));
	fntlighttrek->draw2D(rd,"Format", Vector2(10+4*sep,0), 16, Color3::white(), Color4(0.5F,0.5F,0.5F,0.5F));

	//Tools menu
	Draw::box(G3D::Box(Vector3(5, 165+offset,0),Vector3(75, 165+offset,0)),rd,Color4(0.6F,0.6F,0.6F,0.4F), Color4(0.6F,0.6F,0.6F,0.4F));
	fntlighttrek->draw2D(rd,"Group", Vector2(10,170+offset), 12, Color3::white(), Color4(0.5F,0.5F,0.5F,0.5F));
	fntlighttrek->draw2D(rd,"UnGroup", Vector2(10,195+offset), 12, Color3::white(), Color4(0.5F,0.5F,0.5F,0.5F));
	fntlighttrek->draw2D(rd,"Duplicate", Vector2(10,220+offset), 12, Color3::white(), Color4(0.5F,0.5F,0.5F,0.5F));
	fntlighttrek->draw2D(rd,"MENU", Vector2(10,305+offset), 16, Color3::white(), Color4(0.5F,0.5F,0.5F,0.5F));
	//G3D::GFont::draw2D("Debug Mode Enabled", Vector2(0,30), 20, Color3::white(), Color3::black());
	//app->debugFont->draw2D("Dynamica 2004-2005 Simulation Client version " + VERSION + str, Vector2(0,0), 20, Color3::white(), Color3::black());
	//app->debugFont->draw2D("Debug Mode Enabled", Vector2(0,30), 20, Color3::white(), Color3::black());



	//rd->pushState();
	
	//rd->setTexture(0, go);


	/*rd->enableAlphaWrite();
	rd->setTexCoord(0, Vector2(0.0F, 0.0F));
	rd->setTexCoord(0, Vector2(1.0F, 0.0F));
	rd->setTexCoord(0, Vector2(0.0F, 1.0F));
	rd->setTexCoord(0, Vector2(1.0F, 1.0F));
	rd->setTextureCombineMode(0, RenderDevice::CombineMode::TEX_ADD);
	rd->beginPrimitive(RenderDevice::QUADS);
	rd->sendVertex(Vector2(10,25));
	rd->sendVertex(Vector2(70,25));
	rd->sendVertex(Vector2(70,85));
	rd->sendVertex(Vector2(10,85));
	rd->endPrimitive();
	rd->setTexture(0, NULL);
	//rd->popState();*/


	app->renderDevice->pop2D();
}



void App::main() {
	setDebugMode(false);
	debugController.setActive(false);
    // Load objects here
	go = Texture::fromFile(GetFileInPath("/content/images/Run.png"));
	fntdominant = GFont::fromFile(GetFileInPath("/content/font/dominant.fnt"));
	fntlighttrek = GFont::fromFile(GetFileInPath("/content/font/lighttrek.fnt"));
    sky = Sky::create(NULL, ExePath() + "/content/sky/");
    applet->run();
}



App::App(const GAppSettings& settings) : GApp(settings) {
    applet = new Demo(this);
}


App::~App() {
    delete applet;
}

int main(int argc, char** argv) {
    GAppSettings settings;
	//settings.debugFontName = "lighttrek.fnt";
    //settings.useNetwork = false;
	//settings.window.width = 1024;
	//settings.window.height = 768;
	settings.window.defaultIconFilename = GetFileInPath("/content/images/rico.png");
	settings.window.resizable = true;

	App app = App(settings);
	//app.window()->setIcon(ExePath() + "/content/images/rico.png");
	app.run();
    return 0;
}