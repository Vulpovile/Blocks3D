#include "DataModelV3/InputService.h"
#include "DataModelV3/SignalService.h"
#include "DataModelV3/DataModelInstance.h"
#include "win32Defines.h"

using namespace B3D;

InputService::InputService(void) : Instance()
{
	name = "Mouse";
}

InputService::~InputService(void)
{
}

//Poll state
int InputService::pollKeyState(unsigned char keyCode){
	return GetHoldKeyState(keyCode);
}
int InputService::pollMouseX(){
	return mouseX;
}
int InputService::pollMouseY(){
	return mouseY;
}
int InputService::pollMouseButton(unsigned char button){
	return GetHoldKeyState(button);
}
bool InputService::pollFocus(){
	return hasFocus;
}


//Update Input
void InputService::updateMouse(int x, int y){
	mouseX = x;
	mouseY = y;
}
void InputService::updateFocus(bool focus){
	hasFocus = focus;
}

//Signal
void InputService::signalKeyState(unsigned char keyCode, bool isDown){
	SignalService * signalService = this->parentDataModel->getSignalService();
	signalService->postMessage(MSG_KEY_STATE, (void*)keyCode, (void*)isDown);
}
void InputService::signalMouseButtonState(unsigned char button, bool isDown){
	SignalService * signalService = this->parentDataModel->getSignalService();
	signalService->postMessage(MSG_MOUSE_BUTTON_STATE, (void*)button, (void*)isDown);
}
void InputService::signalMouseWheelState(int step){
	SignalService * signalService = this->parentDataModel->getSignalService();
	signalService->postMessage(MSG_MOUSE_WHEEL_STEP, (void*)step, NULL);
}

//Targeting and mouse actions
//TODO camera instance