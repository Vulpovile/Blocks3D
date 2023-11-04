#pragma once
#include <iostream>
#include <string>
#include <map>
#include "ReflectionProperty.h"
namespace B3D{
	namespace Instance{
		class Instance;
	}
	namespace Reflection{
		class ReflectionDataTable
		{
		public:
			ReflectionDataTable(Instance::Instance * parentInstance, std::string className);
			ReflectionDataTable::ReflectionDataTable(void);
			~ReflectionDataTable(void);

			std::string ReflectionDataTable::getClassName(void);
		private:
			//Perhaps not stored here?
			std::string className;
			std::map<std::string, B3D::Reflection::ReflectionProperty<void*>*> propertyTable;
			Instance::Instance * parentInstance;
		};
	}
}
