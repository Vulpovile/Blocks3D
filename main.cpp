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

#if G3D_VER < 60800
    #error Requires G3D 6.08
#endif
static const float VNUM = 0.01F;
static const std::string VERSION = "PRE-ALPHA ";
static GFontRef fntdominant = NULL;
static GFontRef fntlighttrek = NULL;
static bool democ = true;
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
    app->debugCamera.setPosition(Vector3(0, 2, 10));
    app->debugCamera.lookAt(Vector3(0, 2, 0));
	std::string str = "Dynamica Duomillenium 5 Version " + VERSION + Convert(VNUM);
	app->renderDevice->setCaption(str);
    GApplet::onInit();
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
	else if(ui->keyReleased(SDL_RIGHT_MOUSE_KEY))
	{
		app->debugController.setActive(false);
	}
	if(ui->keyPressed('d'))
	{
		if(ui->keyDown(SDLK_LCTRL))
		{
			app->setDebugMode(!app->debugMode());
		}
	}

	// Add other key handling here
}

std::string ExePath() {
    char buffer[MAX_PATH];
    GetModuleFileName( NULL, buffer, MAX_PATH );
	std::string::size_type pos = std::string( buffer ).find_last_of( "\\/" );
	return std::string( buffer ).substr( 0, pos);
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
		app->renderDevice->setLight(0, GLight::directional(lighting.lightDirection, lighting.lightColor));
		app->renderDevice->setAmbientLightColor(lighting.ambient);

		Draw::axes(CoordinateFrame(Vector3(0, 0, 0)), app->renderDevice);
		Draw::cylinder(G3D::Cylinder::Cylinder(Vector3(0,0,0),Vector3(0,10,0),1),app->renderDevice,Color4(0,0,1,0.5),Color4(0,0,0,0));

    app->renderDevice->disableLighting();

    if (app->sky.notNull()) {
        app->sky->renderLensFlare(app->renderDevice, lighting);
    }
	app->renderDevice->push2D();

	//std::string str = ;
	
	int offset = 0;
	int offset2 = 0;
	if(app->debugMode())
	{
		offset = 50;
		offset2 = 70;
		fntlighttrek->draw2D(rd, "Debug Mode Enabled", Vector2(0,30 + offset), 15, Color3::white(), Color3::black());
	}

	fntdominant->draw2D(rd, "Dynamica 2004-2005 Simulation Client version " + VERSION + Convert(VNUM), Vector2(0,0 + offset), 20, Color3::white(), Color3::black());
	//fntlighttrek->draw2D(rd, "Button: " + button, Vector2(10,30 + offset), 15, Color3::white(), Color3::black());
	

	Draw::box(G3D::Box(Vector3(0,40 + offset2,0),Vector3(80,330+offset2+40,0)),rd,Color4(0.5F,0.5F,0.5F,0.2F), Color4(0,0,0,0));
	Draw::box(G3D::Box(Vector3(0,rd->getHeight() - 120,0),Vector3(80,rd->getHeight(),0)),rd,Color4(0.5F,0.5F,0.5F,0.4F), Color4(0,0,0,0));
	Draw::box(G3D::Box(Vector3(rd->getWidth() - 120,rd->getHeight() - 120,0),Vector3(rd->getWidth(),rd->getHeight(),0)),rd,Color4(0.5F,0.5F,0.5F,0.4F), Color4(0,0,0,0));
	fntlighttrek->draw2D(rd, "CameraMenu", Vector2(rd->getWidth()-(fntlighttrek->get2DStringBounds("CameraMenu", 14).x+1),rd->getHeight() - 120), 14, Color3::white(), Color4(0.5F,0.5F,0.5F,0.5F));
	//G3D::GFont::draw2D("Debug Mode Enabled", Vector2(0,30), 20, Color3::white(), Color3::black());
	//app->debugFont->draw2D("Dynamica 2004-2005 Simulation Client version " + VERSION + str, Vector2(0,0), 20, Color3::white(), Color3::black());
	//app->debugFont->draw2D("Debug Mode Enabled", Vector2(0,30), 20, Color3::white(), Color3::black());
	app->renderDevice->pop2D();

}



void App::main() {
	setDebugMode(false);
	debugController.setActive(false);
    // Load objects here
	fntdominant = GFont::fromFile(ExePath() + "\\content\\font\\dominant.fnt");
	fntlighttrek = GFont::fromFile(ExePath() + "\\content\\font\\lighttrek.fnt");
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
	settings.window.resizable = true;
	App(settings).run();
    return 0;
}
