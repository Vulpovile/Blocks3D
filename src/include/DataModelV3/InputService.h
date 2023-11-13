//Should potentially make a "Service" class
#pragma once
#include "Instance.h"
#include "PartInstance.h"

namespace B3D{

	struct MousePoint{
		Vector3 position;
		B3D::PartInstance * target;
		MousePoint(Vector3 pos, PartInstance * targ)
		{
			position = pos;
			target = targ;
		}
	};

	class InputService : public Instance{
	public:
		InputService(void);
		~InputService(void);

		//Polling
		int pollKeyState(unsigned char keyCode);
		int pollMouseX();
		int pollMouseY();
		int pollMouseButton(unsigned char button);
		bool pollFocus();


		//Update Input
		void updateMouse(int x, int y);
		void updateFocus(bool focus);

		//Signal
		void signalKeyState(unsigned char keyCode, bool isDown);
		void signalMouseButtonState(unsigned char button, bool isDown);
		void signalMouseWheelState(int step);


	private:
		int mouseX, mouseY;
		Ray lastRay;
		bool hasFocus;
	};
}