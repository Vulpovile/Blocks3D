#pragma once
#include <G3DAll.h>

class Instance
{
public:
	static Instance* Instance::Create(std::string classname)
	{

	}
	Instance(void);
	Instance(const Instance &);
	~Instance(void);
	std::vector<Instance*>* getChildren();
protected:
	std::vector<Instance*> children;
	Instance * parent;
}