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
			TYPE_INT,
			TYPE_FLOAT,
			TYPE_STRING,
			TYPE_VECTOR3,
			TYPE_COLOR3,
			TYPE_COLOR4,
			TYPE_CFRAME,
			TYPE_BOOLEAN,
			TYPE_ENUM,
			LENGTH
		};
	}
}