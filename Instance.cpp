#define WINVER	0x0400
#include <G3DAll.h>
#include "Instance.h"


Instance::Instance(void)
{
	parent = NULL;
	name = "Default Game Instance";
	className = "BaseInstance";
	listicon = 0;
	canDelete = true;
}

Instance::Instance(const Instance &oinst)
{
	
	name = oinst.name;
	className = oinst.className;
	canDelete = oinst.canDelete;
	//setParent(oinst.parent);
}



void Instance::render(RenderDevice* rd)
{
	for(size_t i = 0; i < children.size(); i++)
	{
		children.at(i)->render(rd);
	}
}



PROPGRIDITEM Instance::createPGI(LPSTR catalog, LPSTR propName, LPSTR propDesc, LPARAM curVal, INT type)
{
	PROPGRIDITEM pItem;
	PropGrid_ItemInit(pItem);
	pItem.lpszCatalog=catalog;
	pItem.lpszPropName=propName;
	pItem.lpszPropDesc=propDesc;
	pItem.lpCurValue=curVal;
	pItem.iItemType=type;
	return pItem;
}

void Instance::PropUpdate(LPPROPGRIDITEM &item)
{
	if(strcmp(item->lpszPropName, "Name") == 0)
	{
		name = (LPSTR)item->lpCurValue;
	}
}

std::vector<PROPGRIDITEM> Instance::getProperties()
{
	std::vector<PROPGRIDITEM> properties;
	
	
	properties.push_back(createPGI(
		"Properties",
		"Name",
		"The name of this instance",
		(LPARAM)name.c_str(),
		PIT_EDIT
		));
	return properties;
}



Instance::~Instance(void)
{
	for(size_t i = 0; i < children.size(); i++)
	{
		delete children.at(i);
	}
}

std::string Instance::getClassName()
{
	return className;
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

Instance* Instance::findFirstChild(std::string name)
{
	for(size_t i = 0; i < children.size(); i++)
	{
		if(children.at(i)->name.compare(name) == 0)
		{
			return children.at(i);
		}
	}
	return NULL;
}



