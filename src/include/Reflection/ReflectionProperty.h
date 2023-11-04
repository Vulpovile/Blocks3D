#pragma once
#include "Reflection.h"
#include <iostream>
#include <string>
#include <typeinfo>

namespace B3D{
	namespace Reflection{
		class ReflectionDataTable;

		template<class T>
		class ReflectionProperty
		{
		public:
			//Could be private?
			std::string key;
			T * value;
			ReflectionType type;
			ReflectionProperty(std::string key, T * value, ReflectionType type, ReflectionDataTable * containerTable);
			ReflectionProperty(void);
			~ReflectionProperty(void);
			void dispose();
		private:
			std::string propertyName;
			bool archivable;
			bool locked;
			bool propertyHidden;
			ReflectionDataTable * containerTable;
		};
	}
}

//***really*** wanted to avoid implementing this inside of the header
#include "ReflectionProperty_imp.h"