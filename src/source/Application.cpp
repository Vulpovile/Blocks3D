#include <G3DAll.h>
#include <initguid.h>
#include <iomanip>
#include "../../resource.h"
#include "DataModelV2/Instance.h"
#include "DataModelV2/PartInstance.h"
#include "DataModelV2/TextButtonInstance.h"
#include "DataModelV2/ImageButtonInstance.h"
#include "DataModelV2/DataModelInstance.h"
#include "DataModelV2/GuiRootInstance.h"
#include "CameraController.h"
#include "AudioPlayer.h"
#include "Globals.h"
#include "Application.h"
#include "win32Defines.h"
#include "WindowFunctions.h"
#include <limits.h>
#include <mshtml.h>
#include <exdisp.h>
#include <vector>
#include <string>
#include "ax.h"
#include <cguid.h>
#include "PropertyWindow.h"
#include <commctrl.h>
#include "StringFunctions.h"

#include "Listener/GUDButtonListener.h"
#include "Listener/ModeSelectionListener.h"
#include "Listener/DeleteListener.h"
#include "Listener/CameraButtonListener.h"
#include "Listener/RotateButtonListener.h"
#include "Faces.h"
#define LEGACY_LOAD_G3DFUN_LEVEL
//Ray testRay;
//static int cursorid = 0;
//static int cursorOvrid = 0;
//static int currentcursorid = 0;
static bool mouseMovedBeginMotion = false;
static POINT oldGlobalMouse;
Vector2 oldMouse = Vector2(0,0);
float moveRate = 0.5;

void Application::clearInstances()
{
	delete _dataModel;
}

PartInstance* Application::makePart()
{
	PartInstance* part = new PartInstance();
	return part;
}

void Application::setFocus(bool focus)
{
	if(_propWindow != NULL)
		if(focus)
		{
			ShowWindow(_propWindow->_hwndProp, SW_SHOW);
			SetWindowPos(_propWindow->_hwndProp, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_NOACTIVATE);
		}
		else 
		{
			SetWindowPos(_propWindow->_hwndProp, HWND_NOTOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_NOACTIVATE);
		}
}

Application::Application(HWND parentWindow) : _propWindow(NULL) { //: GApp(settings,window) {
	

	std::string tempPath = ((std::string)getenv("temp")) + "/"+g_appName;
	CreateDirectory(tempPath.c_str(), NULL);
	
	_hWndMain = parentWindow;

	HMODULE hThisInstance = GetModuleHandle(NULL);

	_hwndToolbox = CreateWindowEx(
		WS_EX_ACCEPTFILES,
		"AX",
		"{8856F961-340A-11D0-A96B-00C04FD705A2}",
		WS_CHILD | WS_VISIBLE,
		0,
		560,
		800,
		60,
		_hWndMain, // parent
		NULL, // menu
		hThisInstance,
		NULL
	);
	
	_hwndRenderer = CreateWindowEx(
		WS_EX_ACCEPTFILES,
		"G3DWindow",
		"3D",
		WS_CHILD,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		1,
		1,
		_hWndMain, // parent
		NULL, // menu
		hThisInstance,
		NULL
	);
	_settings.window.resizable = true;
	_settings.writeLicenseFile = false;
	_settings.logFilename = tempPath + "/g3dlog.txt";
	_settings.window.center = true; 
	Win32Window* window = Win32Window::create(_settings.window,_hwndRenderer);
	ShowWindow(_hwndRenderer, SW_SHOW);
	ShowWindow(_hWndMain, SW_SHOW);
	
	quit=false;
	rightButtonHolding=false;
	mouseOnScreen=false;
	// GApp replacement
	renderDevice = new RenderDevice();
	if (window != NULL) {
	renderDevice->init(window, NULL);
	}
	else
	{
		MessageBox(NULL,"Window not found!","Error",MB_OK | MB_ICONSTOP);
		return;
	}

    _window = renderDevice->window();
    _window->makeCurrent();
	
	SetWindowLongPtr(_hWndMain,GWL_USERDATA,(LONG)this);
	SetWindowLongPtr(_hwndRenderer,GWL_USERDATA,(LONG)this);
	_propWindow = new PropertyWindow(0, 0, 200, 640, hThisInstance);
	webBrowser = new IEBrowser(_hwndToolbox);
	
	SetProp(_hwndToolbox,"Browser",(HANDLE)webBrowser);
	//navigateToolbox("http://androdome.com/res/ClientToolbox.php");
	navigateToolbox(GetFileInPath("/content/page/surface.html"));
	//navigateToolbox(GetFileInPath("/content/page/controller.html"));

}

void Application::navigateToolbox(std::string path)
{
	int len = path.size() + 1;
	wchar_t * nstr = new wchar_t[len];
	MultiByteToWideChar(0, 0, path.c_str(), len, nstr, len);
	webBrowser->navigateSyncURL(nstr);
	delete[] nstr;
}

void Application::deleteInstance()
{
	if(g_selectedInstances.size() > 0)
	{
		size_t undeletable = 0;
		while(g_selectedInstances.size() > undeletable)
		{
			if(g_selectedInstances.at(0)->canDelete)
			{
				AudioPlayer::playSound(GetFileInPath("/content/sounds/pageturn.wav"));
				Instance* selectedInstance = g_selectedInstances.at(0);
				selectedInstance->setParent(NULL);
				delete selectedInstance;
				selectedInstance = NULL;
				g_selectedInstances.erase(g_selectedInstances.begin());
			}
			else
			{
				undeletable++;
			}
		}
	}
	if(g_selectedInstances.size() == 0)
		g_usableApp->_propWindow->ClearProperties();
}


void Application::onInit()  {
	tool = new Tool();
    // Called before Application::run() beings
	cameraController.setFrame(Vector3(0,2,10));
	_dataModel = new DataModelInstance();
	_dataModel->setParent(NULL);
	_dataModel->setName("undefined");
	_dataModel->font = g_fntdominant;
	g_dataModel = _dataModel;
	
	//initGUI();

#ifdef LEGACY_LOAD_G3DFUN_LEVEL
	PartInstance* test = makePart();
	test->setParent(_dataModel->getWorkspace());
	test->color = Color3(0.2F,0.3F,1);
	test->setSize(Vector3(24,1,24));
	test->setPosition(Vector3(0,0,0));
	test->setCFrame(test->getCFrame() * Matrix3::fromEulerAnglesXYZ(0,toRadians(0),toRadians(0)));
	test->setSurface(TOP, Enum::SurfaceType::Bumps);
	
	test = makePart();
	test->setParent(_dataModel->getWorkspace());
	test->color = Color3(.5F,1,.5F);
	test->setSize(Vector3(4,1,2));
	test->setPosition(Vector3(-10,1,0));
	test->setSurface(TOP, Enum::SurfaceType::Bumps);

	test = makePart();
	test->setParent(_dataModel->getWorkspace());
	test->color = Color3(.5F,1,.5F);
	test->setSize(Vector3(4,1,2));
	test->setPosition(Vector3(10,1,0));
	test->setSurface(TOP, Enum::SurfaceType::Bumps);

	test = makePart();
	test->setParent(_dataModel->getWorkspace());
	test->color = Color3::gray();
	test->setSize(Vector3(4,1,2));
	test->setPosition(Vector3(7,2,0));
	test->setSurface(TOP, Enum::SurfaceType::Bumps);

	test = makePart();
	test->setParent(_dataModel->getWorkspace());
	test->color = Color3::gray();
	test->setSize(Vector3(4,1,2));
	test->setPosition(Vector3(-7,2,0));
	test->setSurface(TOP, Enum::SurfaceType::Bumps);

	test = makePart();
	test->setParent(_dataModel->getWorkspace());
	test->color = Color3::gray();
	test->setSize(Vector3(4,1,2));
	test->setPosition(Vector3(4,3,0));
	test->setSurface(TOP, Enum::SurfaceType::Bumps);

	test = makePart();
	test->setParent(_dataModel->getWorkspace());
	test->color = Color3::gray();
	test->setSize(Vector3(4,1,2));
	test->setPosition(Vector3(-5,3,0));
	test->setSurface(TOP, Enum::SurfaceType::Bumps);

	test = makePart();
	test->setParent(_dataModel->getWorkspace());
	test->color = Color3::gray();
	test->setSize(Vector3(4,1,2));
	test->setPosition(Vector3(1,4,0));
	test->setSurface(TOP, Enum::SurfaceType::Bumps);

	test = makePart();
	test->setParent(_dataModel->getWorkspace());
	test->color = Color3::gray();
	test->setSize(Vector3(4,1,2));
	test->setPosition(Vector3(-3,4,0));
	test->setSurface(TOP, Enum::SurfaceType::Bumps);

	test = makePart();
	test->setParent(_dataModel->getWorkspace());
	test->color = Color3::gray();
	test->setSize(Vector3(4,1,2));
	test->setPosition(Vector3(-2,5,0));
	test->setSurface(TOP, Enum::SurfaceType::Bumps);
	

	

	test = makePart();
	test->setParent(_dataModel->getWorkspace());
	test->color = Color3::gray();
	test->setSize(Vector3(4,1,2));
	test->setPosition(Vector3(0,6,0));
	test->setSurface(TOP, Enum::SurfaceType::Bumps);

	test = makePart();
	test->setParent(_dataModel->getWorkspace());
	test->color = Color3::gray();
	test->setSize(Vector3(4,1,2));
	test->setPosition(Vector3(2,7,0));
	test->setSurface(TOP, Enum::SurfaceType::Bumps);
#else
	_dataModel->debugGetOpen();
#endif
	



	//setDesiredFrameRate(60);
	
	
	

    //GApplet::onInit();
	
}






void Application::onCleanup() {
    clearInstances();
	sky->~Sky();
}



/*

Class HyperSnapSolver

function getCollisionDepth(Part colliding, part collider);
function getFaceCollision(Part colliding, part collider);

function eject(Part colliding, Part collider)
{
    if(!colliding.canCollide || !collider.canCollide)
        return;
    if(getCollisionDepth(colliding, collider) != 0)    {
        int ejectMultiplier, ejectMultipliery = 1-(collider.Friction+colliding.Friction), ejectMultiplierz = 1-(collider.Friction/2+colliding.Friction/2);
        if(colliding.Anchored)
            ejectMultiplier = collider.elasticity;
        int faceCollided = getFaceCollision(colliding, collider);
        if(faceCollided % 3 == 1)
        {
            ejectMultipliery = ejectMultiplier;
            ejectMultiplier = 1-(collider.Friction+colliding.Friction/2);
        }
        else if(faceCollided % 3 == 2)
        {
            ejectMultiplierz = ejectMultiplier;
            ejectMultiplier = 1-(collider.Friction+colliding.Friction/2);
        }

        collider.Velocity *= Vector3.new(colliding.Velocity.x*ejectMultiplier,colliding.Velocity.y*ejectMultipliery,colliding.Velocity.z)
    }
}

*/

double grav = 0.32666666666666666666666666666667;
void simGrav(PartInstance * collider)
{
	if(!collider->anchored)
	{
		collider->setPosition(collider->getPosition()+collider->getVelocity());
		collider->setVelocity(collider->getVelocity()-Vector3(0,grav,0));
	}
}

void eject(PartInstance * colliding, PartInstance * collider)
{
	if(colliding == collider || !colliding->canCollide || !collider->canCollide)
		return;
	if(G3D::CollisionDetection::fixedSolidBoxIntersectsFixedSolidBox(collider->getBox(), colliding->getBox()))
		collider->setVelocity(collider->getVelocity().reflectionDirection(colliding->getCFrame().upVector())/1.3F);

}



void Application::onLogic() {	
	//PhysicsStart
	for_each (_dataModel->getWorkspace()->partObjects.begin(), _dataModel->getWorkspace()->partObjects.end(), simGrav);
	for(size_t i = 0; i < _dataModel->getWorkspace()->partObjects.size(); i++)
	{
		for(size_t j = 0; j < _dataModel->getWorkspace()->partObjects.size(); j++)
		{
			eject(_dataModel->getWorkspace()->partObjects[i], _dataModel->getWorkspace()->partObjects[j]);
		}
	}	
}



void Application::onNetwork() {
	// Poll net messages here
}


//double getVectorDistance(Vector3 vector1, Vector3 vector2)
//{
//	return pow(pow((double)vector1.x - (double)vector2.x, 2) + pow((double)vector1.y - (double)vector2.y, 2) + pow((double)vector1.z - (double)vector2.z, 2), 0.5);
//}

std::vector<Instance*> Application::getSelection()
{
	return g_selectedInstances;
}
void Application::onSimulation(RealTime rdt, SimTime sdt, SimTime idt) {

	if(_dataModel->isRunning())
		onLogic();
		
	_dataModel->getGuiRoot()->update();

	if(_dataModel->name != _title)
	{
		_title = _dataModel->name;
		std::string text = "Game \"" + _title + "\"";
		SetWindowText(_hWndMain, text.c_str());
		
	}

	cameraController.update(this);

}

/*double getOSVersion() {
    OSVERSIONINFO osvi;

    ZeroMemory(&osvi, sizeof(OSVERSIONINFO));
    osvi.dwOSVersionInfoSize = sizeof(OSVERSIONINFO);

    GetVersionEx(&osvi);
	std::string version = Convert(osvi.dwMajorVersion) + "." + Convert(osvi.dwMinorVersion);
	return ::atof(version.c_str());
}*/
/* 
bool IsHolding(int button)
{
	return (GetKeyState(button) >> 1)>0;
}

*/

void Application::onUserInput(UserInput* ui) {
	if(mouseMoveState)
	{
		mouseMoveState = false;
		tool->onMouseMoved(mouse);
	}
	/*
	if(GetHoldKeyState(VK_LCONTROL))
	{
		if(GetHoldKeyState('D'))
		{
			_messageTime = System::time();
			if(debugMode())
				_message = "Debug Mode Disabled";
			else
				_message = "Debug Mode Enabled";
			setDebugMode(!debugMode());
		}
	}
	*/
	if(GetHoldKeyState(VK_F8))
	{
		_dataModel->getGuiRoot()->setDebugMessage("FOV Set to 10", System::time());	
	}
	//}

	//_dataModel->mousex = ui->getMouseX();
	//_dataModel->mousey = ui->getMouseY();
	mouse.setMouseDown((GetKeyState(VK_LBUTTON) & 0x100) != 0);

	if (GetHoldKeyState(VK_LBUTTON)) {
	/*	if (_dragging) {
			PartInstance* part = NULL;
			if(g_selectedInstances.size() > 0)
				part = (PartInstance*) g_selectedInstances.at(0);
		Ray dragRay = cameraController.getCamera()->worldRay(mouse.x, mouse.y, renderDevice->getViewport());
		std::vector<Instance*> instances = _dataModel->getWorkspace()->getAllChildren();
		for(size_t i = 0; i < instances.size(); i++)
			{
				if(PartInstance* moveTo = dynamic_cast<PartInstance*>(instances.at(i)))
				{
					float __time = testRay.intersectionTime(moveTo->getBox());
					float __nearest=std::numeric_limits<float>::infinity();
					if (__time != inf()) 
					{
						if (__nearest>__time)
						{
							// BROKEN
							//Vector3 closest = (dragRay.closestPoint(moveTo->getPosition()) * 2);
							//part->setPosition(closest);
							//part->setPosition(Vector3(floor(closest.x),part->getPosition().y,floor(closest.z)));
						}
					}
				}
			}
			Sleep(10);
		}*/
	}
	// Camera KB Handling {
		if (GetKPBool(VK_OEM_COMMA)) //Left
			g_usableApp->cameraController.panLeft();
		else if (GetKPBool(VK_OEM_PERIOD)) // Right
			g_usableApp->cameraController.panRight();
		else if (GetKPBool(0x49)) // Zoom In (I)
			g_usableApp->cameraController.Zoom(1);
		else if (GetKPBool(0x4F)) // Zoom Out (O)
			g_usableApp->cameraController.Zoom(-1);
	// }

	//readMouseGUIInput();
	// Add other key handling here
}

void Application::changeTool(Tool * newTool)
{
	tool->onDeselect(mouse);
	delete tool;
	if(newTool != NULL)
		tool = newTool;
	else
		tool = new Tool(); //Nulltool
	tool->onSelect(mouse);
	
}

void Application::setMode(int mode)
{
	_mode = mode;
}

void Application::unSetMode()
{
	_mode = NULL;
}

int Application::getMode()
{
	return _mode;
}


void Application::drawOutline(Vector3 from, Vector3 to, RenderDevice* rd, LightingParameters lighting, Vector3 size, Vector3 pos, CoordinateFrame c)
{
	rd->disableLighting();
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
	
	if(_mode == ARROWS)
	{
		
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



	}
	else if(_mode == RESIZE)
	{
		Color3 sphereColor = outline;
		Vector3 gamepoint = pos;
		Vector3 camerapoint = rd->getCameraToWorldMatrix().translation;
		float distance = pow(pow((double)gamepoint.x - (double)camerapoint.x, 2) + pow((double)gamepoint.y - (double)camerapoint.y, 2) + pow((double)gamepoint.z - (double)camerapoint.z, 2), 0.5);
		if(distance < 200)
		{
			
			float multiplier = distance * 0.025F/2;
			if(multiplier < 0.25F)
				multiplier = 0.25F;
			Vector3 position = pos + (c.lookVector()*((size.z)+1));
			Draw::sphere(Sphere(position, multiplier), rd, sphereColor, Color4::clear());
			position = pos - (c.lookVector()*((size.z)+1));
			Draw::sphere(Sphere(position, multiplier), rd, sphereColor, Color4::clear());

			position = pos + (c.rightVector()*((size.x)+1));
			Draw::sphere(Sphere(position, multiplier), rd, sphereColor, Color4::clear());
			position = pos - (c.rightVector()*((size.x)+1));
			Draw::sphere(Sphere(position, multiplier), rd, sphereColor, Color4::clear());

			position = pos + (c.upVector()*((size.y)+1));
			Draw::sphere(Sphere(position, multiplier), rd, sphereColor, Color4::clear());
			position = pos - (c.upVector()*((size.y)+1));
			Draw::sphere(Sphere(position, multiplier), rd, sphereColor, Color4::clear());
		}
	}
	rd->enableLighting();
}

void Application::exitApplication()
{
	//endApplet = true;
    //endProgram = true;
}




void Application::onGraphics(RenderDevice* rd) {
	
	G3D::uint8 num = 0;
	POINT mousepos;
	mouseOnScreen = true;
	if (GetCursorPos(&mousepos))
	{
		POINT pointm = mousepos;
	if (ScreenToClient(_hWndMain, &mousepos))
	{
		//mouseOnScreen = true;
		//POINT pointm;
		///GetCursorPos(&pointm);
		if(_hwndRenderer != WindowFromPoint(pointm)) //OLD: mousepos.x < 1 || mousepos.y < 1 || mousepos.x >= rd->getViewport().width()-1 || mousepos.y >= rd->getViewport().height()-1
		{
			mouseOnScreen = false;
			//ShowCursor(true);
			//_window->setMouseVisible(true);
			//rd->window()->setInputCaptureCount(0);
		}
		else
		{
			mouseOnScreen = true;
			//SetCursor(NULL);
			//_window->setMouseVisible(false);
			//rd->window()->setInputCaptureCount(1);
		}
		
	}
	}
	
	if(Globals::useMousePoint)
	{
		mousepos = Globals::mousepoint;
		ScreenToClient(_hWndMain, &mousepos);
	}
	
    LightingParameters lighting(G3D::toSeconds(2, 00, 00, PM));
	lighting.ambient = Color3(0.6F,0.6F,0.6F);
    renderDevice->setProjectionAndCameraMatrix(*cameraController.getCamera());
	
    // Cyan background
    //renderDevice->setColorClearValue(Color3(0.0f, 0.5f, 1.0f));

    renderDevice->clear(sky.isNull(), true, true);
    if (sky.notNull()) {
        sky->render(renderDevice, lighting);
    }
	
    // Setup lighting
    renderDevice->enableLighting();

	renderDevice->setShadeMode(RenderDevice::SHADE_SMOOTH);
	renderDevice->setAmbientLightColor(Color3(1,1,1));

	renderDevice->setLight(0, GLight::directional(lighting.lightDirection, lighting.lightColor, true, true));
	renderDevice->setAmbientLightColor(lighting.ambient);

	//renderDevice->setBlendFunc(RenderDevice::BLEND_ONE, RenderDevice::BLEND_ONE);



	//renderDevice->setShininess(70);
	//renderDevice->setSpecularCoefficient(Color3(0.1F, 0.1F, 0.1F));
	
	float   lightAmbient[]  = { 0.5F, 0.6F, 0.9F, 1.0F };
    float   lightDiffuse[]  = { 0.6F, 0.4F, 0.9F, 1.0F };
    float   lightSpecular[] = { 0.8F, 0.8F, 0.8F, 1.0F };
    //float   lightSpecular[] = { 0.8F, 0.6F, 1.0F, 1.0F };

	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, lightAmbient);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, lightDiffuse);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, lightSpecular);
	glMateriali(GL_FRONT_AND_BACK, GL_SHININESS, 70);
	

	rd->beforePrimitive();
	CoordinateFrame forDraw = rd->getObjectToWorldMatrix();
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_COLOR_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);
	//if(_dataModel->getWorkspace() != NULL)
	
	_dataModel->getWorkspace()->render(rd);
	//else throw std::exception("Workspace not found");
	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_COLOR_ARRAY);
	glDisableClientState(GL_NORMAL_ARRAY);
	rd->setObjectToWorldMatrix(forDraw);
	rd->afterPrimitive();


	//Draw::box(G3D::Box(mouse.getPosition()-Vector3(2,0.5F,1),mouse.getPosition()+Vector3(2,0.5F,1)), rd, Color3::cyan(), Color4::clear());
	if(g_selectedInstances.size() > 0)
	{
		for(size_t i = 0; i < g_selectedInstances.size(); i++)
		{
			if(PartInstance* part = dynamic_cast<PartInstance*>(g_selectedInstances.at(i)))
			{
			Vector3 size = part->getSize();
			Vector3 pos = part->getPosition();
			drawOutline(Vector3(0+size.x/2, 0+size.y/2, 0+size.z/2) ,Vector3(0-size.x/2,0-size.y/2,0-size.z/2), rd, lighting, Vector3(size.x/2, size.y/2, size.z/2), Vector3(pos.x, pos.y, pos.z), part->getCFrame());
			}
		}
	}
	

	//Vector3 gamepoint = Vector3(0, 5, 0);
	//Vector3 camerapoint = rd->getCameraToWorldMatrix().translation;
	//float distance = pow(pow((double)gamepoint.x - (double)camerapoint.x, 2) + pow((double)gamepoint.y - (double)camerapoint.y, 2) + pow((double)gamepoint.z - (double)camerapoint.z, 2), 0.5);
	//if(distance < 50 && distance > -50)
	
	//{
	//	if(distance < 0)
	//	distance = distance*-1;
	//	fntdominant->draw3D(rd, "Testing", CoordinateFrame(rd->getCameraToWorldMatrix().rotation, gamepoint), 0.04*distance, Color3::yellow(), Color3::black(), G3D::GFont::XALIGN_CENTER, G3D::GFont::YALIGN_CENTER);
	//}

    renderDevice->disableLighting();

    if (sky.notNull()) {
        sky->renderLensFlare(renderDevice, lighting);
    }
	renderDevice->push2D();
		_dataModel->getGuiRoot()->renderGUI(renderDevice, m_graphicsWatch.FPS());
		/*rd->pushState();
			rd->beforePrimitive();

			if(Globals::showMouse && mouseOnScreen)
			{
			glEnable( GL_TEXTURE_2D );
			glEnable(GL_BLEND);// you enable blending function
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); 
			/*
			std::vector<Instance*> instances = _dataModel->getWorkspace()->getAllChildren();
			currentcursorid = cursorid;
			for(size_t i = 0; i < instances.size(); i++)
			{
				if(PartInstance* test = dynamic_cast<PartInstance*>(instances.at(i)))
				{
					float time = cameraController.getCamera()->worldRay(_dataModel->mousex, _dataModel->mousey, renderDevice->getViewport()).intersectionTime(test->getBox());
					//float time = testRay.intersectionTime(test->getBox());
					if (time != inf()) 
					{
						currentcursorid = cursorOvrid;
						break;
					}
					
				}
			}
			*/
			/*glBindTexture( GL_TEXTURE_2D, tool->getCursorId());

			
			glBegin( GL_QUADS );
			glTexCoord2d(0.0,0.0);
			glVertex2f(mousepos.x-64, mousepos.y-64);
			glTexCoord2d( 1.0,0.0 );
			glVertex2f(mousepos.x+64, mousepos.y-64);
			glTexCoord2d(1.0,1.0 );
			glVertex2f(mousepos.x+64, mousepos.y+64 );
			glTexCoord2d( 0.0,1.0 );
			glVertex2f( mousepos.x-64, mousepos.y+64 );
			glEnd();

			glDisable( GL_TEXTURE_2D );*/
			//}

			/*rd->afterPrimitive();
		rd->popState();*/
	renderDevice->pop2D();
}

void Application::onKeyPressed(int key)
{
	if(key==VK_DELETE)
	{
		deleteInstance();
	}
	if ((GetHoldKeyState(VK_LCONTROL) || GetHoldKeyState(VK_RCONTROL)) && key=='O')
	{
			_dataModel->getOpen();
	}
	if ((GetHoldKeyState(VK_LCONTROL) || GetHoldKeyState(VK_RCONTROL)) && key=='A')
	{
		std::vector<Instance *> vec = _dataModel->getWorkspace()->getAllChildren();
		g_selectedInstances.insert(g_selectedInstances.end(), vec.begin(), vec.end());
	}
	tool->onKeyDown(key);
}
void Application::onKeyUp(int key)
{
	tool->onKeyUp(key);
}

void Application::onMouseLeftPressed(HWND hwnd,int x,int y)
{
	//Removed set focus 


	//std::cout << "Click: " << x << "," << y << std::endl;
	
	
	bool onGUI = _dataModel->getGuiRoot()->mouseInGUI(renderDevice, x, y);
	
	
	if(!onGUI)
	{
		tool->onButton1MouseDown(mouse);
	}
}

void Application::selectInstance(Instance* selectedInstance, PropertyWindow* propWindow)
{
	if(!GetHoldKeyState(VK_RCONTROL) && !GetHoldKeyState(VK_LCONTROL))
	{
		printf("No control key hold \n");
		g_selectedInstances.clear();
	}
	else printf("Control held\n");
	if(std::find(g_selectedInstances.begin(), g_selectedInstances.end(),selectedInstance)==g_selectedInstances.end())
		g_selectedInstances.push_back(selectedInstance);
	propWindow->UpdateSelected(selectedInstance);

}
G3D::RenderDevice* Application::getRenderDevice()
{
	return renderDevice;
}

void Application::onMouseLeftUp(G3D::RenderDevice* renderDevice, int x, int y)
{
	//std::cout << "Release: " << x << "," << y << std::endl;
	_dataModel->getGuiRoot()->onMouseLeftUp(renderDevice, x, y);
	_dragging = false;
	tool->onButton1MouseUp(mouse);
	//_message = "Dragging = false.";
	//_messageTime = System::time();

}

void Application::onMouseRightPressed(int x,int y)
{
	tool->onButton2MouseDown(mouse);
}
void Application::onMouseRightUp(int x,int y)
{
	tool->onButton2MouseUp(mouse);
}
void Application::onMouseMoved(int x,int y)
{
	oldMouse = Vector2(mouse.x, mouse.y);
	mouse.oldx = mouse.x;
	mouse.oldy = mouse.y;
	mouse.x = x;
	mouse.y = y;
	//tool->onMouseMoved(mouse);
	mouseMoveState = true;
	//_dataModel->mousex = x;
	//_dataModel->mousey = y;

}
void Application::onMouseWheel(int x,int y,short delta)
{
	if (mouseOnScreen==true)
	if (cameraController.onMouseWheel(x, y, delta))
	{
		AudioPlayer::playSound(cameraSound);
	}
	tool->onMouseScroll(mouse);
}

void Application::run() {
	g_usableApp = this;
	//setDebugMode(false);
	//debugController.setActive(false);
	/*
	if (!createWindowClass("ToolWindowClass",ToolProc,GetModuleHandle(0)))
	{
		return;
	}

    HWND propertyHWnd = CreateWindowEx(
    WS_EX_TOOLWINDOW,"ToolWindowClass", "ToolWindow",
    WS_SYSMENU | WS_VISIBLE | WS_CHILD,
	0, 0, 800, 64,
    hWndMain, NULL, GetModuleHandle(0), NULL);

	ShowWindow(propertyHWnd,SW_SHOW);
	*/
	UpdateWindow(_hWndMain);

    // Load objects here=

	Globals::surface = Texture::fromFile(GetFileInPath("/content/images/surfacebr.png"));
	Globals::surfaceId = Globals::surface->getOpenGLID();
	cameraSound = GetFileInPath("/content/sounds/SWITCH3.wav");
	clickSound = GetFileInPath("/content/sounds/switch.wav");
	dingSound = GetFileInPath("/content/sounds/electronicpingshort.wav");
    sky = Sky::create(NULL, ExePath() + "/content/sky/");
	RealTime	now=0, lastTime=0;
	double		simTimeRate = 1.0f;
	float		fps=30.0f;

	RealTime	desiredFrameDuration=1.0/fps;
	onInit();
	RealTime    lastWaitTime=0;

	MSG			messages;
	//RECT cRect;
	//GetClientRect(_hWndMain,&cRect);
	//renderDevice->notifyResize(cRect.right,cRect.bottom);
	//Rect2D viewportRect = Rect2D::xywh(0,0,cRect.right,cRect.bottom);
	//renderDevice->setViewport(viewportRect);
	//window()->setInputCaptureCount(1);
	resizeWithParent(_hWndMain);
	glEnable(GL_CULL_FACE);
	while (!quit)
	{
		
		lastTime = now;
		now = System::getTick();
		RealTime timeStep = now - lastTime;
		
		m_userInputWatch.tick();
			onUserInput(userInput);
			//m_moduleManager->onUserInput(_userInput);
		m_userInputWatch.tock();
		
		m_simulationWatch.tick();
			//debugController.doSimulation(clamp(timeStep, 0.0, 0.1));
			//g3dCamera.setCoordinateFrame
				//(debugController.getCoordinateFrame());

			double rate = simTimeRate;    
			RealTime rdt = timeStep;
			SimTime  sdt = timeStep * rate;
			SimTime  idt = desiredFrameDuration * rate;

			onSimulation(rdt,sdt,idt);
		m_simulationWatch.tock();

		m_waitWatch.tick();
		{
			RealTime now = System::time();
			// Compute accumulated time
			System::sleep(max(0.0, desiredFrameDuration - (now - lastWaitTime)));
			lastWaitTime = System::time();
		}
		m_waitWatch.tock();

		m_graphicsWatch.tick();
			renderDevice->beginFrame();
				renderDevice->pushState();
					onGraphics(renderDevice);
				renderDevice->popState();
				//renderDebugInfo();
			renderDevice->endFrame();
			//debugText.clear();
		m_graphicsWatch.tock();

		while (PeekMessage (&messages, NULL, 0, 0,PM_REMOVE))
		{
			if (IsDialogMessage(_hWndMain, &messages) == 0)
			{
				TranslateMessage(&messages);
				DispatchMessage(&messages);
			}
		}
	}
	onCleanup();
}
void Application::resizeWithParent(HWND parentWindow)
{
	RECT rect;
	GetClientRect(parentWindow,&rect);
	SetWindowPos(_hwndRenderer,NULL,0,0,rect.right,rect.bottom-60,SWP_NOMOVE);
	SetWindowPos(_hwndToolbox,NULL,0,rect.bottom-60,rect.right,60,SWP_NOACTIVATE | SWP_SHOWWINDOW);
	GetClientRect(_hwndRenderer,&rect);
	int viewWidth=rect.right;
	int viewHeight=rect.bottom;
	renderDevice->notifyResize(viewWidth,viewHeight);
	Rect2D viewportRect = Rect2D::xywh(0,0,viewWidth,viewHeight);
	renderDevice->setViewport(viewportRect);

}

void Application::QuitApp()
{
	PostQuitMessage(0);
	quit=true;
}

void Application::onCreate(HWND parentWindow)
{
	//SetWindowLongPtr(hwndRenderer,GWL_USERDATA,(LONG)this);
	//SetWindowLongPtr(hwndToolbox,GWL_USERDATA,(LONG)this);
	//SetWindowLongPtr(hwndMain,GWL_USERDATA,(LONG)&app);
}