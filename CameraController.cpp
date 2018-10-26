#include "CameraController.h"
#include "win32Defines.h"
#include <iostream>
#include "PartInstance.h"
#include "Demo.h"
#include "AudioPlayer.h"



CameraController::CameraController() :
yaw(0), 
pitch(0),
moveRate(1.0f),
forwards(false),
backwards(false),
left(false),
right(false),
zoom(14.f),
rightButtonHolding(false),
focusPosition(Vector3(0,0,0)) {}

GCamera* CameraController::getCamera()
{
	return &g3dCamera;
}

void CameraController::lookAt(const Vector3& position) {
    const Vector3 look = (position - g3dCamera.getCoordinateFrame().translation);
    yaw   = aTan2(look.x, -look.z);
	
    pitch = -aTan2(look.y, distance(look.x, look.z));
	CoordinateFrame frame = g3dCamera.getCoordinateFrame().translation;
	frame.rotation = Matrix3::fromEulerAnglesZYX(0, -yaw, -pitch);
	g3dCamera.setCoordinateFrame(frame);
}

void CameraController::setFrame(const CoordinateFrame& cf) {
	Vector3 look = cf.getLookVector();
	g3dCamera.setCoordinateFrame(cf);
	lookAt(cf.translation + look);
	focusPosition=cf.translation+cf.lookVector()*zoom;
}

CoordinateFrame CameraController::getCoordinateFrame() {
	CoordinateFrame cf;
	cf.translation=translation;
	cf.rotation = Matrix3::fromEulerAnglesZYX(0, -yaw, -pitch);
	return cf;
}

void CameraController::refreshZoom(const CoordinateFrame& frame)
{
	CoordinateFrame zoomFrame = focusPosition-frame.lookVector()*zoom;
	zoomFrame.lookAt(focusPosition);
	setFrame(zoomFrame);
}

void CameraController::pan(CoordinateFrame* frame,float spdX, float spdY)
{
		yaw+=spdX;
		pitch+=spdY;

		if (pitch>1.4f) pitch=1.4f;
		if (pitch<-1.4f) pitch=-1.4f;
		frame->translation = Vector3(sin(-yaw)*zoom*cos(pitch),sin(pitch)*zoom,cos(-yaw)*zoom*cos(pitch))+focusPosition;
		frame->lookAt(focusPosition);
}
bool CameraController::onMouseWheel(int x, int y, short delta)
{
	Zoom(delta);
	return true;
}
void CameraController::Zoom(short delta)
{
	CoordinateFrame frame = g3dCamera.getCoordinateFrame();

	if (delta>0) { // Mouse wheel up
		CoordinateFrame zoomFrame = frame+frame.lookVector()*(zoom/5);
		zoom=(zoomFrame.translation-focusPosition).magnitude();
		if (zoom>CAM_ZOOM_MIN)
		{
			setFrame(zoomFrame);
		}
		else
		{
			zoom=CAM_ZOOM_MIN;
			refreshZoom(frame);
		}
	}
	else {
		CoordinateFrame zoomFrame = frame-frame.lookVector()*(zoom/5);
		zoom=(zoomFrame.translation-focusPosition).magnitude();
		if (zoom<CAM_ZOOM_MAX)
		{
			setFrame(zoomFrame);
		}
		else
		{
			zoom=CAM_ZOOM_MAX;
			refreshZoom(frame);
		}
	}
}

void CameraController::panLeft()
{
	CoordinateFrame frame = g3dCamera.getCoordinateFrame();
	pan(&frame,toRadians(-45),0);
	setFrame(frame);
	
}
void CameraController::panRight()
{
	CoordinateFrame frame = g3dCamera.getCoordinateFrame();
	pan(&frame,toRadians(45),0);
	setFrame(frame);
}

void CameraController::tiltUp()
{

	CoordinateFrame frame = CoordinateFrame(g3dCamera.getCoordinateFrame().rotation, g3dCamera.getCoordinateFrame().translation);
	pan(&frame,0,toRadians(25));
	setFrame(frame);
}
void CameraController::tiltDown()
{
	CoordinateFrame frame = CoordinateFrame(g3dCamera.getCoordinateFrame().rotation, g3dCamera.getCoordinateFrame().translation);
	pan(&frame,0,toRadians(-25));
	setFrame(frame);
}

void CameraController::centerCamera(Instance* selection)
{
	CoordinateFrame frame = CoordinateFrame(g3dCamera.getCoordinateFrame().translation);
	if(selection == NULL)
	{
		lookAt(Vector3(0,0,0));
		focusPosition=Vector3(0,0,0);
	}
	else
	{
		Vector3 partPos = ((PartInstance*)selection)->getPosition()/2;
		lookAt(partPos);
		focusPosition=partPos;
		zoom=((partPos-frame.translation).magnitude());
	}
}

void CameraController::update(Demo* demo)
{
	float offsetSize = 0.05F;

	Vector3 cameraPos = g3dCamera.getCoordinateFrame().translation;
	CoordinateFrame frame = g3dCamera.getCoordinateFrame();
	bool moving=false;
	if(GetHoldKeyState('U')) {
		forwards = true;
		moving=true;
	}
	if(GetHoldKeyState('J')) {
		backwards = true;
		moving=true;
	}
	if(GetHoldKeyState('H')) {
		left = true;
		moving=true;
	}
	if(GetHoldKeyState('K')) {
		right = true;
		moving=true;
	}
	
	if(forwards) {
		forwards = false;
		frame.translation += frame.lookVector()*moveRate;
	}
	else if(backwards) {
		backwards = false;
		frame.translation -= frame.lookVector()*moveRate;
	}
	if(left) {
		left = false;
		frame.translation += frame.leftVector()*moveRate;
	}
	else if(right) {
		right = false;
		frame.translation += frame.rightVector()*moveRate;
	}

	if (moving)
	{
		zoom=7;
		focusPosition=frame.translation+frame.lookVector()*zoom;
	}

	if(rightButtonHolding) {
		Globals::useMousePoint = true;
		Globals::mousepoint = oldDesktopMouse;
		POINT mouse;
		GetCursorPos(&mouse);
		pan(&frame,(mouse.x-oldDesktopMouse.x)/100.f,(mouse.y-oldDesktopMouse.y)/100.f);
		SetCursorPos(oldDesktopMouse.x,oldDesktopMouse.y);
	}
	else
	{
		Globals::useMousePoint = false;
	}

	if(GetHoldKeyState(VK_RSHIFT) || GetHoldKeyState(VK_LSHIFT)) {
		moveRate = 2;
	}
	else {
		moveRate = 1;
	}

	if(GetHoldKeyState(VK_RBUTTON))
	{
		if (rightButtonHolding==false)
		{
			GetCursorPos(&oldDesktopMouse);
			rightButtonHolding = true;
		}
	}
	else
	{
		rightButtonHolding = false;
	}
	g3dCamera.setCoordinateFrame(frame);
}
