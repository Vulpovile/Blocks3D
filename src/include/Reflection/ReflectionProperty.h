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
			T value;
			ReflectionType type;
			ReflectionProperty(std::string key, T * valuePtr, ReflectionType type, ReflectionDataTable * containerTable, void* extData = NULL, bool archivable = true, bool locked = false, bool propertyHidden = false);
			ReflectionProperty(std::string key, T defaultValue, ReflectionType type, ReflectionDataTable * containerTable, void* extData = NULL, bool archivable = true, bool locked = false, bool propertyHidden = false);
			ReflectionProperty(void);
			~ReflectionProperty(void);
			
			T getValue();
			T getValueClone();
			T* getValuePtr();

			void setValue(T);

			void dispose();

			//Too many
			#include "ReflectionProperty_op_overload.h"


		private:
			std::string propertyName;
			bool archivable;
			bool locked;
			bool propertyHidden;
			void* extData;
			ReflectionDataTable * containerTable;
		};
	}
}

//***really*** wanted to avoid implementing this inside of the header
#include "ReflectionProperty_impl.h"