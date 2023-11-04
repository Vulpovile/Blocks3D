#pragma once
#include <iostream>
#include <string>
#include <map>
#include "ReflectionProperty.h"
namespace B3D{
	class Instance;

	namespace Reflection{
		class ReflectionDataTable
		{
		public:
			ReflectionDataTable(Instance * parentInstance, std::string className);
			ReflectionDataTable::ReflectionDataTable(void);
			~ReflectionDataTable(void);

			std::string ReflectionDataTable::getClassName(void);

			void mapProperty(std::string key, ReflectionProperty<void*>* prop);
		private:
			//Perhaps not stored here?
			std::string className;
			std::map<std::string, ReflectionProperty<void*>*> propertyTable;
			Instance * parentInstance;
		};
	}
}
