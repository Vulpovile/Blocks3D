#include "DataModelV3/InputService.h"
#include "DataModelV3/SignalService.h"
#include "DataModelV3/DataModelInstance.h"
#include "win32Defines.h"

using namespace B3D;

ControllerService::ControllerService(void) : Instance()
{
	name = "ControllerService";
}

ControllerService::~ControllerService(void)
{
}

//Poll state
int ControllerService::pollKeyState(unsigned char keyCode){
	return GetHoldKeyState(keyCode);
}
int ControllerService::pollMouseX(){
	return mouseX;
}
int ControllerService::pollMouseY(){
	return mouseY;
}
int ControllerService::pollMouseButton(unsigned char button){
	return GetHoldKeyState(button);
}
bool ControllerService::pollFocus(){
	return hasFocus;
}


//Update Input
void ControllerService::updateMouse(int x, int y){
	mouseX = x;
	mouseY = y;
}
void ControllerService::updateFocus(bool focus){
	hasFocus = focus;
}

//Signal
void ControllerService::signalKeyState(unsigned char keyCode, bool isDown){
	SignalService * signalService = this->parentDataModel->getSignalService();
	signalService->postMessage(MSG_KEY_STATE, (void*)keyCode, (void*)isDown);
}
void ControllerService::signalMouseButtonState(unsigned char button, bool isDown){
	SignalService * signalService = this->parentDataModel->getSignalService();
	signalService->postMessage(MSG_MOUSE_BUTTON_STATE, (void*)button, (void*)isDown);
}
void ControllerService::signalMouseWheelState(int step){
	SignalService * signalService = this->parentDataModel->getSignalService();
	signalService->postMessage(MSG_MOUSE_WHEEL_STEP, (void*)step, NULL);
}

//Targeting and mouse actions
//TODO camera instance