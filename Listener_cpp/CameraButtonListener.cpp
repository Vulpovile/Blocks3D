#include "Listener/CameraButtonListener.h"
#include "Globals.h"
#include "AudioPlayer.h"
#include "Application.h"

void CameraButtonListener::onButton1MouseClick(BaseButtonInstance* button)
{
	AudioPlayer::playSound(cameraSound);
	CoordinateFrame frame = g_usableApp->cameraController.getCamera()->getCoordinateFrame();
	if(button->name == "CenterCam" && g_dataModel->getSelectionService()->getSelection().size() > 0)
		g_usableApp->cameraController.centerCamera(g_dataModel->getSelectionService()->getSelection()[0]);
	else if(button->name == "ZoomIn")
		g_usableApp->cameraController.Zoom(1);
	else if(button->name == "ZoomOut")
		g_usableApp->cameraController.Zoom(-1);
	else if(button->name == "PanRight")
		g_usableApp->cameraController.panRight();
	else if(button->name == "PanLeft")
		g_usableApp->cameraController.panLeft();
	else if(button->name == "TiltUp")
		g_usableApp->cameraController.tiltUp();
	else if(button->name == "TiltDown")
		g_usableApp->cameraController.tiltDown();
}