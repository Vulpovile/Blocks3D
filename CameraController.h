#pragma once

#include <G3DAll.h>
#include "Instance.h"
#include <string>

class Demo;

class CameraController {
	public:
		CameraController();
		G3D::CoordinateFrame getCoordinateFrame();

		void setFrame(const CoordinateFrame& cf);
		void lookAt(const Vector3& position);
		void pan(int spdX,int spdY);
		void update(Demo* demo);
		void centerCamera(Instance* selection);
		void panLeft();
		void panRight();
		void tiltUp();
		void tiltDown();
		bool onMouseWheel(int x, int y, short delta);
		GCamera* getCamera();
	private:
		Vector3 translation;
		Vector3	focusPosition;
		float	yaw;
		float	pitch;
		float	moveRate;
		bool	forwards;
		bool	backwards;
		bool	left;
		bool	right;
		bool	rightButtonHolding;
		POINT	oldDesktopMouse;
		GCamera	g3dCamera;
		std::string cameraSound;
};