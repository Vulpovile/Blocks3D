//Should potentially make a "Service" class
#pragma once
#include "Instance.h"

namespace B3D{
	class InputService : public Instance{
		InputService(void);
		InputService~(void);
		pollKeyState(int key);
	}
}