#include <G3DAll.h>
#include <initguid.h>
#include <iomanip>
#include "resource.h"
#include "DataModelV2/Instance.h"
#include "DataModelV2/PartInstance.h"
#include "DataModelV2/TextButtonInstance.h"
#include "DataModelV2/ImageButtonInstance.h"
#include "DataModelV2/DataModelInstance.h"
#include "DataModelV2/GuiRootInstance.h"
#include "XplicitNgine/XplicitNgine.h"
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
	
	// Needs to be enabled if "B3DCCService" (still need to finalize that name)
	//_settings.window.fsaaSamples = 8;

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

	AudioPlayer::init();

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

bool Application::viewportHasFocus()
{
	return GetActiveWindow() == this->_hWndMain;
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
	if(_dataModel->getSelectionService()->getSelection().size() > 0)
	{
		std::vector<Instance *> selection = _dataModel->getSelectionService()->getSelection();
		std::vector<Instance *> toDelete;
		for(size_t i = 0; i < selection.size(); i++) {
			if(selection[i]->canDelete) {
				toDelete.push_back(selection[i]);
			}
		}
		if(toDelete.size() > 0)
		{
			AudioPlayer::playSound(GetFileInPath("/content/sounds/pageturn.wav"));
			for(size_t i = 0; i < toDelete.size(); i++) {
				Instance* selectedInstance = toDelete[i];
				_dataModel->getSelectionService()->removeSelected(selectedInstance);
				selectedInstance->setParent(NULL);
				delete selectedInstance;
				selectedInstance = NULL;
			}
		}
	}
	if(_dataModel->getSelectionService()->getSelection().size() == 0)
		_dataModel->getSelectionService()->addSelected(_dataModel);
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

#ifdef LEGACY_LOAD_G3DFUN_LEVEL
	// Anchored this baseplate for XplicitNgine tests
	PartInstance* test = makePart();
	test->setParent(_dataModel->getWorkspace());
	test->color = Color3(0.2F,0.3F,1);
	test->setSize(Vector3(24,1,24));
	test->setPosition(Vector3(0,0,0));
	test->setCFrame(test->getCFrame() * Matrix3::fromEulerAnglesXYZ(0,toRadians(0),toRadians(0)));
	test->setSurface(TOP, Enum::SurfaceType::Bumps);
	test->setAnchored(true);

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
	
	_dataModel->getSelectionService()->clearSelection();
	_dataModel->getSelectionService()->addSelected(_dataModel);
}

void Application::onCleanup() {
    clearInstances();
}

void Application::onLogic() {
	
}

void Application::onNetwork() {
	// Poll net messages here
}

void Application::onSimulation(RealTime rdt, SimTime sdt, SimTime idt) {

	if(_dataModel->isRunning())
	{
		LevelInstance* Level = _dataModel->getLevel();
		Level->Step(sdt);

		// XplicitNgine Start
		std::vector<PartInstance *> toDelete;
		for(size_t i = 0; i < _dataModel->getWorkspace()->partObjects.size(); i++)
		{
			PartInstance* partInstance = _dataModel->getWorkspace()->partObjects[i];
			if(partInstance->getPosition().y < -255)
			{
				toDelete.push_back(partInstance);
			}
			else 
				_dataModel->getEngine()->createBody(partInstance);
		}
		while(toDelete.size() > 0)
		{
			PartInstance * p = toDelete.back();
			toDelete.pop_back();
			if(g_dataModel->getSelectionService()->isSelected(p))
				g_dataModel->getSelectionService()->removeSelected(p);
			p->setParent(NULL);
			delete p;
		}
		for(int i = 0; i < 4; i++)
		{
			_dataModel->getEngine()->step(0.03F);
		}
		onLogic();
		
	}

	_dataModel->getGuiRoot()->update();

	if(_dataModel->name != _title)
	{
		_title = _dataModel->name;
		std::string text = "Game \"" + _title + "\"";
		SetWindowText(_hWndMain, text.c_str());
		
	}

	cameraController.update(this);

}

void Application::onUserInput(UserInput* ui) {
	if(mouseMoveState)
	{
		mouseMoveState = false;
		tool->onMouseMoved(mouse);
	}

	if(GetHoldKeyState(VK_F8))
	{
		_dataModel->getGuiRoot()->setDebugMessage("FOV Set to 10", System::time());	
	}

	mouse.setMouseDown((GetKeyState(VK_LBUTTON) & 0x100) != 0);

	// Camera KB Handling
	if (GetKPBool(VK_OEM_COMMA)) //Left
		g_usableApp->cameraController.panLeft();
	else if (GetKPBool(VK_OEM_PERIOD)) // Right
		g_usableApp->cameraController.panRight();
	else if (GetKPBool(0x49)) // Zoom In (I)
		g_usableApp->cameraController.Zoom(1);
	else if (GetKPBool(0x4F)) // Zoom Out (O)
		g_usableApp->cameraController.Zoom(-1);
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

void Application::exitApplication()
{
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
			if(_hwndRenderer != WindowFromPoint(pointm))
			{
				mouseOnScreen = false;
			}
			else
			{
				mouseOnScreen = true;
			}
			
		}
	}
	
	if(Globals::useMousePoint)
	{
		mousepos = Globals::mousepoint;
		ScreenToClient(_hWndMain, &mousepos);
	}
	
	renderDevice->setProjectionAndCameraMatrix(*cameraController.getCamera());
	
	// Moved a lot of code to lighting
	g_dataModel->getLighting()->update();

	renderDevice->push2D();
		_dataModel->getGuiRoot()->renderGUI(renderDevice, m_graphicsWatch.FPS());
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
	tool->onKeyDown(key);
}
void Application::onKeyUp(int key)
{
	tool->onKeyUp(key);
}

void Application::onMouseLeftPressed(HWND hwnd,int x,int y)
{
	bool onGUI = _dataModel->getGuiRoot()->mouseInGUI(renderDevice, x, y);
	
	
	if(!onGUI)
	{
		tool->onButton1MouseDown(mouse);
	}
}

G3D::RenderDevice* Application::getRenderDevice()
{
	return renderDevice;
}

void Application::onMouseLeftUp(G3D::RenderDevice* renderDevice, int x, int y)
{
	_dataModel->getGuiRoot()->onMouseLeftUp(renderDevice, x, y);
	_dragging = false;
	tool->onButton1MouseUp(mouse);
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
	mouseMoveState = true;

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
	UpdateWindow(_hWndMain);

    // Load objects here
	cameraSound = GetFileInPath("/content/sounds/SWITCH3.wav");
	clickSound = GetFileInPath("/content/sounds/switch.wav");
	dingSound = GetFileInPath("/content/sounds/electronicpingshort.wav");
	RealTime	now=0, lastTime=0;
	double		simTimeRate = 1.0f;
	float		fps=30.0f;

	RealTime	desiredFrameDuration=1.0/fps;
	onInit();
	RealTime    lastWaitTime=0;

	MSG			messages;

	resizeWithParent(_hWndMain);
	glEnable(GL_CULL_FACE);
	while (!quit)
	{
		
		lastTime = now;
		now = System::getTick();
		RealTime timeStep = now - lastTime;
		
		m_userInputWatch.tick();
			onUserInput(userInput);
		m_userInputWatch.tock();
		
		m_simulationWatch.tick();

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

void Application::resize3DView(int w, int h)
{
	Rect2D newViewport = Rect2D::xywh(0, 0, w, h);
	renderDevice->notifyResize(w, h);
	renderDevice->setViewport(newViewport);
}

void Application::QuitApp()
{
	PostQuitMessage(0);
	quit=true;
}

void Application::onCreate(HWND parentWindow)
{
}
