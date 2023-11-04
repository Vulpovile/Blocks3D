#include "DataModelV3/Instance.h"

using namespace B3D;

Instance::Instance(std::string className)
{
	this->parent = NULL;
	this->dataTable = new Reflection::ReflectionDataTable(this, className);
	this->name = Reflection::ReflectionProperty<std::string>(new std::string("Default Game Instance"), Reflection::TYPE_STRING, dataTable);
}

Instance::Instance(void)
{
	Instance::Instance("BaseInstance");
}

Instance::~Instance(void)
{
	for(size_t i = 0; i < children.size(); i++)
	{
		delete children.at(i);
	}
	delete dataTable;
}

Instance::Instance(const Instance &oinst)
{
	//CLONE WITH REFLECTION!!!
}

//Perhaps should be separated
void Instance::render(RenderDevice* rd)
{
	for(size_t i = 0; i < children.size(); i++)
	{
		children[i]->render(rd);
	}
}

void Instance::renderName(RenderDevice* rd)
{
	for(size_t i = 0; i < children.size(); i++)
	{
		children[i]->renderName(rd);
	}
}

void Instance::update()
{
}

void Instance::setName(std::string newName)
{
	*name.value = newName;
}

std::string Instance::getClassName()
{
	return dataTable->getClassName();
}

std::vector<Instance* > Instance::getChildren()
{
	return children;
}

std::vector<Instance* > Instance::getAllChildren()
{
	if(!children.empty())
	{
		std::vector<Instance* > totalchildren = children;
		for(size_t i = 0; i < children.size(); i++)
		{
			std::vector<Instance* > subchildren = children.at(i)->getAllChildren();
			if(!subchildren.empty())
				totalchildren.insert(totalchildren.end(), subchildren.begin(), subchildren.end());
		}
		return totalchildren;
	}
	return children;
}

void Instance::setParent(Instance* newParent)
{
	if(parent != NULL)
	{
		parent->removeChild(this);
	}
	parent = newParent;
	if(newParent != NULL)
	{
		newParent->addChild(this);
	}
}

Instance* Instance::getParent()
{
	return parent;
}

void Instance::addChild(Instance* newChild)
{
	children.push_back(newChild);
}

void Instance::clearChildren()
{
	for (size_t i = 0; i < children.size(); i++)
	{
		delete children.at(i);
	} 
	children.clear();
}
void Instance::removeChild(Instance* oldChild)
{
	for(size_t i = 0; i < children.size(); i++)
	{
		if(children.at(i) == oldChild)
		{
			children.erase(children.begin() + i);
		}
	}
}

Instance* Instance::findFirstChild(std::string searchName)
{
	for(size_t i = 0; i < children.size(); i++)
	{
		if(children.at(i)->name.value->compare(searchName) == 0)
		{
			return children.at(i);
		}
	}
	return NULL;
}