#include "CameraController.h"
#include "win32Defines.h"
#include <iostream>
#include "PhysicalInstance.h"
#include "Demo.h"
#include "AudioPlayer.h"

CameraController::CameraController(){
	yaw=0;
	pitch=0;
	moveRate=0.5f;
	forwards=false;
	backwards=false;
	left=false;
	right=false;
	rightButtonHolding=false;

}

GCamera* CameraController::getCamera()
{
	return &g3dCamera;
}

void CameraController::lookAt(const Vector3& position) {
	//g3dCamera.lookAt(position,g3dCamera.getCoordinateFrame().upVector());
	
    const Vector3 look = (position - g3dCamera.getCoordinateFrame().translation);
    yaw   = aTan2(look.x, -look.z);
	
    pitch = -aTan2(look.y, distance(look.x, look.z));
	std::cout << distance(look.x, look.z) << "pitch:" << pitch << std::endl;
	CoordinateFrame frame = g3dCamera.getCoordinateFrame().translation;
	frame.rotation = Matrix3::fromEulerAnglesZYX(0, -yaw, -pitch);
	g3dCamera.setCoordinateFrame(frame);
}

void CameraController::setFrame(const CoordinateFrame& cf) {
	Vector3 look = cf.getLookVector();
	g3dCamera.setCoordinateFrame(cf);
	lookAt(cf.translation + look);
}

CoordinateFrame CameraController::getCoordinateFrame() {
	CoordinateFrame cf;
	cf.translation=translation;
	cf.rotation = Matrix3::fromEulerAnglesZYX(0, -yaw, -pitch);
	return cf;
}

void CameraController::pan(int spdX, int spdY)
{

}
bool CameraController::onMouseWheel(int x, int y, short delta)
{
	CoordinateFrame frame = g3dCamera.getCoordinateFrame();
	if (delta>0) { // Mouse wheel up
		g3dCamera.setCoordinateFrame(g3dCamera.getCoordinateFrame() + frame.lookVector()*2);
	}
	else {
		g3dCamera.setCoordinateFrame(g3dCamera.getCoordinateFrame() - frame.lookVector()*2);
	}
	return true;
}

void CameraController::panLeft()
{
	CoordinateFrame frame = g3dCamera.getCoordinateFrame();
	float y = frame.translation.y;
	CoordinateFrame frame2 = CoordinateFrame(frame.rotation, frame.translation + frame.lookVector()*25);
	Vector3 focus = Vector3(0,0,0); //frame.translation+frame.lookVector()*25;
	frame2 = frame2 * Matrix3::fromEulerAnglesXYZ(0,toRadians(-45),0);
	frame2 = frame2 - frame2.lookVector()*25;
	Vector3 cameraPos = Vector3(frame2.translation.x, y, frame2.translation.z);
	CoordinateFrame newFrame = CoordinateFrame(frame2.rotation, Vector3(frame2.translation.x, y, frame2.translation.z));
	newFrame.lookAt(focus,frame2.upVector());
	setFrame(CoordinateFrame(focus));
}
void CameraController::panRight()
{
	CoordinateFrame frame = g3dCamera.getCoordinateFrame();
	float y = frame.translation.y;
	CoordinateFrame frame2 = CoordinateFrame(frame.rotation, frame.translation + frame.lookVector()*25);
	Vector3 focus = frame.translation+frame.lookVector()*25;
	frame2 = frame2 * Matrix3::fromEulerAnglesXYZ(0,toRadians(45),0);
	frame2 = frame2 - frame2.lookVector()*25;
	Vector3 cameraPos = Vector3(frame2.translation.x, y, frame2.translation.z);
	CoordinateFrame newFrame = CoordinateFrame(frame2.rotation, Vector3(frame2.translation.x, y, frame2.translation.z));
	newFrame.lookAt(focus);
	setFrame(newFrame);
}

void CameraController::tiltUp()
{
	CoordinateFrame frame = CoordinateFrame(g3dCamera.getCoordinateFrame().rotation, g3dCamera.getCoordinateFrame().translation);
	Vector3 camerapoint = frame.translation;

	Vector3 focalPoint = camerapoint + frame.lookVector() * 25;
	float distance = pow(pow((double)focalPoint.x - (double)camerapoint.x, 2) + pow((double)camerapoint.y - (double)camerapoint.y, 2) + pow((double)focalPoint.z - (double)camerapoint.z, 2), 0.5);
	float x = distance * cos(22.5 * G3D::pi() / 180) + focalPoint.x;
    float z = distance * sin(22.5 * G3D::pi() / 180) + focalPoint.z;
	camerapoint = Vector3(camerapoint.x, camerapoint.y+2, camerapoint.z);
	
	CoordinateFrame newFrame = CoordinateFrame(camerapoint);
	newFrame.lookAt(focalPoint);
	Vector3 cameraPos = camerapoint;
	frame = newFrame;
	setFrame(newFrame);
}
void CameraController::tiltDown()
{
}

void CameraController::centerCamera(Instance* selection)
{
	CoordinateFrame frame = CoordinateFrame(g3dCamera.getCoordinateFrame().translation);
	if(selection == NULL)
		lookAt(Vector3(0,0,0));
	else
		lookAt(((PhysicalInstance*)selection)->getPosition()/2);
}

void CameraController::update(Demo* demo)
{
	float offsetSize = 0.05F;

	Vector3 cameraPos = g3dCamera.getCoordinateFrame().translation;
	CoordinateFrame frame = g3dCamera.getCoordinateFrame();

	if(GetHoldKeyState('U')) {
		forwards = true;
	}
	if(GetHoldKeyState('J')) {
		backwards = true;
	}
	if(GetHoldKeyState('H')) {
		left = true;
	}
	if(GetHoldKeyState('K')) {
		right = true;
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


	if(rightButtonHolding) {
		POINT mouse;
		GetCursorPos(&mouse);

		yaw+=(mouse.x-oldDesktopMouse.x)/100.f;
		pitch+=(mouse.y-oldDesktopMouse.y)/100.f;
		
		SetCursorPos(oldDesktopMouse.x,oldDesktopMouse.y);
		frame.rotation = Matrix3::fromEulerAnglesZYX(0, -yaw, -pitch);
	}

	if(GetHoldKeyState(VK_RSHIFT) || GetHoldKeyState(VK_LSHIFT)) {
		moveRate = 1;
	}
	else {
		moveRate = 0.5;
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
