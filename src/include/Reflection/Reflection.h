#pragma once
#include "ErrorFunctions.h"
//BE WARNED, IF YOU TOUCH REFLECTION YOUR BUILD WILL TAKE AGES

namespace B3D{
	namespace Reflection{
		//I do not like this... Structs?
		class EnumMeta	{
		public:
			EnumMeta(int maxLength, const char ** nameValues)
			{
				this->maxLength = maxLength;
				this->nameValues = nameValues;
			}
			int maxLength;
			const char ** nameValues;
		};

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