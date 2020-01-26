#include <G3DAll.h>
#include <initguid.h>
#include <iomanip>
#include "Instance.h"
#include "resource.h"
#include "PartInstance.h"
#include "TextButtonInstance.h"
#include "ImageButtonInstance.h"
#include "DataModelInstance.h"
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
#include "IEBrowser.h"
#include "PropertyWindow.h"
#include <commctrl.h>
#include "StringFunctions.h"
#include "GuiRoot.h"

#include "GUDButtonListener.h"
#include "ModeSelectionListener.h"
#include "DeleteListener.h"
#include "CameraButtonListener.h"
#include "RotateButtonListener.h"

Ray testRay;
static int cursorid = 0;
static int cursorOvrid = 0;
static int currentcursorid = 0;
static G3D::TextureRef cursor = NULL;
static G3D::TextureRef cursorOvr = NULL;
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
	

	std::string tempPath = ((std::string)getenv("temp")) + "/"+g_PlaceholderName;
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
	IEBrowser* webBrowser = new IEBrowser(_hwndToolbox);
	webBrowser->navigateSyncURL(L"http://androdome.com/res/ClientToolbox.php");
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
				if(selectedInstance->getParent() != NULL)
					selectedInstance->getParent()->removeChild(selectedInstance);
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
	
    // Called before Application::run() beings
	cameraController.setFrame(Vector3(0,2,10));
	_dataModel = new DataModelInstance();
	_dataModel->setParent(NULL);
	_dataModel->name = "undefined";
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
	

	
	test = makePart();
	test->setParent(_dataModel->getWorkspace());
	test->color = Color3(.5F,1,.5F);
	test->setSize(Vector3(4,1,2));
	test->setPosition(Vector3(-10,1,0));
	test = makePart();
	test->setParent(_dataModel->getWorkspace());
	test->color = Color3(.5F,1,.5F);
	test->setSize(Vector3(4,1,2));
	test->setPosition(Vector3(10,1,0));

	test = makePart();
	test->setParent(_dataModel->getWorkspace());
	test->color = Color3::gray();
	test->setSize(Vector3(4,1,2));
	test->setPosition(Vector3(7,2,0));

	test = makePart();
	test->setParent(_dataModel->getWorkspace());
	test->color = Color3::gray();
	test->setSize(Vector3(4,1,2));
	test->setPosition(Vector3(-7,2,0));

	test = makePart();
	test->setParent(_dataModel->getWorkspace());
	test->color = Color3::gray();
	test->setSize(Vector3(4,1,2));
	test->setPosition(Vector3(4,3,0));

	test = makePart();
	test->setParent(_dataModel->getWorkspace());
	test->color = Color3::gray();
	test->setSize(Vector3(4,1,2));
	test->setPosition(Vector3(-5,3,0));

	test = makePart();
	test->setParent(_dataModel->getWorkspace());
	test->color = Color3::gray();
	test->setSize(Vector3(4,1,2));
	test->setPosition(Vector3(1,4,0));

	test = makePart();
	test->setParent(_dataModel->getWorkspace());
	test->color = Color3::gray();
	test->setSize(Vector3(4,1,2));
	test->setPosition(Vector3(-3,4,0));

	test = makePart();
	test->setParent(_dataModel->getWorkspace());
	test->color = Color3::gray();
	test->setSize(Vector3(4,1,2));
	test->setPosition(Vector3(-2,5,0));
	

	

	test = makePart();
	test->setParent(_dataModel->getWorkspace());
	test->color = Color3::gray();
	test->setSize(Vector3(4,1,2));
	test->setPosition(Vector3(0,6,0));

	test = makePart();
	test->setParent(_dataModel->getWorkspace());
	test->color = Color3::gray();
	test->setSize(Vector3(4,1,2));
	test->setPosition(Vector3(2,7,0));
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




void Application::onLogic() {
    // Add non-simulation game logic and AI code here

		


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
	_dataModel->mouseButton1Down = (GetKeyState(VK_LBUTTON) & 0x100) != 0;

	if (GetHoldKeyState(VK_LBUTTON)) {
		if (_dragging) {
			PartInstance* part = NULL;
			if(g_selectedInstances.size() > 0)
				part = (PartInstance*) g_selectedInstances.at(0);
		Ray dragRay = cameraController.getCamera()->worldRay(_dataModel->mousex, _dataModel->mousey, renderDevice->getViewport());
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
		}
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

void Application::makeFlag(Vector3 &vec, RenderDevice* &rd)
{

	Vector3 up = Vector3(vec.x, vec.y+3, vec.z);
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

void Application::setMode(int mode)
{
	_mode = mode;
}
int Application::getMode()
{
	return _mode;
}


void Application::drawOutline(Vector3 from, Vector3 to, RenderDevice* rd, LightingParameters lighting, Vector3 size, Vector3 pos, CoordinateFrame c)
{

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
	else if(_mode == RESIZE)
	{
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
		}
		rd->setAmbientLightColor(lighting.ambient);
		rd->setLight(0, GLight::directional(lighting.lightDirection, lighting.lightColor));
	}
	
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
			_window->setMouseVisible(true);
			//rd->window()->setInputCaptureCount(0);
		}
		else
		{
			mouseOnScreen = true;
			//SetCursor(NULL);
			_window->setMouseVisible(false);
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

	renderDevice->setLight(0, GLight::directional(lighting.lightDirection, lighting.lightColor));
	renderDevice->setAmbientLightColor(lighting.ambient);
	
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

	if(g_selectedInstances.size() > 0)
	{
		for(size_t i = 0; i < g_selectedInstances.size(); i++)
		{
			if(PartInstance* part = dynamic_cast<PartInstance*>(g_selectedInstances.at(i)))
			{
			Vector3 size = part->getSize();
			Vector3 pos = part->getPosition();
			drawOutline(Vector3(0+size.x/2, 0+size.y/2, 0+size.z/2) ,Vector3(0-size.x/2,0-size.y/2,0-size.z/2), rd, lighting, Vector3(size.x/2, size.y/2, size.z/2), Vector3(pos.x, pos.y, pos.z), part->getCFrameRenderBased());
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
		rd->pushState();
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
			glBindTexture( GL_TEXTURE_2D, currentcursorid);

			
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

			glDisable( GL_TEXTURE_2D );
			}

			rd->afterPrimitive();
		rd->popState();
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
}
void Application::onKeyUp(int key)
{

}

void Application::onMouseLeftPressed(HWND hwnd,int x,int y)
{
	//Removed set focus 


	//std::cout << "Click: " << x << "," << y << std::endl;

	bool onGUI = _dataModel->getGuiRoot()->mouseInGUI(renderDevice, x, y);
	
	
	if(!onGUI)
	{
		Instance * selectedInstance = NULL;
		testRay = cameraController.getCamera()->worldRay(_dataModel->mousex, _dataModel->mousey, renderDevice->getViewport());
		float nearest=std::numeric_limits<float>::infinity();
		Vector3 camPos = cameraController.getCamera()->getCoordinateFrame().translation;
		std::vector<Instance*> instances = _dataModel->getWorkspace()->getAllChildren();
        bool objFound = false;
		for(size_t i = 0; i < instances.size(); i++)
		{
			if(PartInstance* test = dynamic_cast<PartInstance*>(instances.at(i)))
			{
				float time = testRay.intersectionTime(test->getBox());
				
				if (time != inf()) 
				{
					objFound = true;
					if (nearest>time)
					{
						nearest=time;
						//bool found = false;
						selectedInstance = test;
						/*for(size_t i = 0; i < g_selectedInstances.size(); i++)
						{
							if(g_selectedInstances.at(i) == test)
							{
								found = true;
								//ShowWindow(_propWindow->_hwndProp, SW_SHOW);
								//SetActiveWindow(_propWindow->_hwndProp);
								//SetForegroundWindow(_propWindow->_hwndProp);
								break;
							}
						}
						if(!found)
						{
							selectedInstance = test;
							//if(!GetHoldKeyState(VK_RCONTROL) && !GetHoldKeyState(VK_LCONTROL))
								//g_selectedInstances.clear();
							//if(std::find(g_selectedInstances.begin(), g_selectedInstances.end(),test)==g_selectedInstances.end())
								//g_selectedInstances.push_back(test);
						}
						//selectInstance(test, _propWindow);
						//_message = "Dragging = true.";
						//_messageTime = System::time();
						//_dragging = true;*/
					}
				}
			}		
		}
		if(!objFound)
			selectInstance(_dataModel,_propWindow);
		else 
		{
			while(selectedInstance->getParent() != g_dataModel->getWorkspace())
			{
				selectedInstance = selectedInstance->getParent();
			}
			selectInstance(selectedInstance, _propWindow);
		}
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
	//_message = "Dragging = false.";
	//_messageTime = System::time();

}

void Application::onMouseRightPressed(int x,int y)
{
}
void Application::onMouseRightUp(int x,int y)
{
}
void Application::onMouseMoved(int x,int y)
{
	oldMouse = _dataModel->getMousePos();
	_dataModel->mousex = x;
	_dataModel->mousey = y;

}
void Application::onMouseWheel(int x,int y,short delta)
{
	if (mouseOnScreen==true)
	if (cameraController.onMouseWheel(x, y, delta))
	{
		AudioPlayer::playSound(cameraSound);
	}
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
	cursor = Texture::fromFile(GetFileInPath("/content/images/ArrowCursor.png"));
	cursorOvr = Texture::fromFile(GetFileInPath("/content/images/DragCursor.png"));
	Globals::surface = Texture::fromFile(GetFileInPath("/content/images/surfacebr.png"));
	Globals::surfaceId = Globals::surface->getOpenGLID();
	cameraSound = GetFileInPath("/content/sounds/SWITCH3.wav");
	clickSound = GetFileInPath("/content/sounds/switch.wav");
	dingSound = GetFileInPath("/content/sounds/electronicpingshort.wav");
    sky = Sky::create(NULL, ExePath() + "/content/sky/");
	cursorid = cursor->openGLID();
	currentcursorid = cursorid;
	cursorOvrid = cursorOvr->openGLID();
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