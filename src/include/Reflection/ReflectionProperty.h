#pragma once
#include "Reflection.h"
#include <iostream>
#include <string>
#include <typeinfo>

namespace B3D{
	namespace Reflection{
		class ReflectionDataTable;

		template<typename T>
		class ReflectionProperty
		{
		public:
			T * value;
			ReflectionType type;
			ReflectionProperty(T * value, ReflectionType type, ReflectionDataTable * containerTable, bool archivable = true, bool locked = false, bool propertyHidden = false);
			ReflectionProperty(void);
			~ReflectionProperty(void);
		private:
			std::string propertyName;
			bool archivable;
			bool locked;
			bool propertyHidden;
			ReflectionDataTable * containerTable;
		};
	}
}