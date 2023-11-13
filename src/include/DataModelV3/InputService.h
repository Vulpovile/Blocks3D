//Should potentially make a "Service" class
#pragma once
#include "Instance.h"

namespace B3D{
	class InputService : public Instance{
	public:
		InputService(void);
		InputService~(void);
		bool pollKeyState(char keyChar);
		int pollMouseX();
		int pollMouseY();
		bool pollMouseButton(int button);
	private:
		int mouseX, mouseY;

	}
}