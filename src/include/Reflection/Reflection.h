#pragma once
#include "ErrorFunctions.h"

namespace B3D{
	namespace Reflection{
		enum ReflectionType {
			TYPE_INT = 0,
			TYPE_FLOAT = 1,
			TYPE_STRING = 2,
			TYPE_VECTOR3 = 3,
			TYPE_COLOR3 = 4,
			TYPE_CFRAME = 5,
			TYPE_BOOLEAN = 6,
			TYPE_ENUM = 7
		};
	}
}