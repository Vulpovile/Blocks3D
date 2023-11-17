#pragma once
#include "Reflection/Reflection.h"
#include "Reflection/ReflectionDataTable.h"
#include "Reflection/ReflectionProperty.h"
#include <G3DAll.h>
#include "SignalTypes.h"


namespace B3D
{
	class DataModelInstance;

	class Instance
	{
	public:
		//Constructors
		Instance(void);
		Instance(const Instance&);
		virtual ~Instance(void);

		//Virtual Functions
		virtual void render(RenderDevice*);
		virtual void renderName(RenderDevice*);
		virtual void update();
		virtual void setParent(Instance*);

		//TODO implement
		virtual Instance* clone() const { return new Instance(*this); }
		virtual void reflectionNotify(ReflectionProperty<void*>* property);
		
		//Functions
		std::vector<Instance*> children; // All children.
		std::string getClassName();
		Instance* findFirstChild(std::string);
		std::vector<Instance* > getChildren();
		std::vector<Instance* > getAllChildren();
		void setName(std::string newName);
		void addChild(Instance*);
		void removeChild(Instance*);
		void clearChildren();
		Instance* getParent();
		DataModelInstance * getParentDataModel(void);

		//Variables
		Reflection::ReflectionProperty<std::string> name;
		bool canDelete;

		virtual bool postMessage(SigMesg msgId, void* lParam, void* wParam);

		protected:
		//Constructor
		//Used specifically to identify an instance class by an instance class,
		//NOT for use outside of Instance and decendants!
		Instance(std::string className);

		//Variables
		Reflection::ReflectionDataTable * dataTable;
		Instance * parent;
		DataModelInstance * parentDataModel;
	};
}
