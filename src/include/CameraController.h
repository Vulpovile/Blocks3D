#pragma once

#include <G3DAll.h>
#include "Instance.h"
#include "Globals.h"
#include <string>

#define CAM_ZOOM_MIN 0.1f
#define CAM_ZOOM_MAX 100.f

class Application;

class CameraController {
	public:
		CameraController();
		G3D::CoordinateFrame getCoordinateFrame();

		void setFrame(const CoordinateFrame& cf);
		void lookAt(const Vector3& position);
		void refreshZoom(const CoordinateFrame& frame);
		void pan(CoordinateFrame* frame,float spdX,float spdY);
		void panLock(CoordinateFrame* frame,float spdX,float spdY);
		void update(Application* app);
		void centerCamera(Instance* selection);
		void panLeft();
		void panRight();
		void tiltUp();
		void tiltDown();
		void Zoom(short delta);
		bool onMouseWheel(int x, int y, short delta);
		GCamera* getCamera();
	private:
		Vector3 translation;
		Vector3	focusPosition;
		float	yaw;
		float	pitch;
		float	moveRate;
		float	zoom;
		bool	forwards;
		bool	backwards;
		bool	left;
		bool	right;
		bool	rightButtonHolding;
		POINT	oldDesktopMouse;
		GCamera	g3dCamera;
		std::string cameraSound;
};