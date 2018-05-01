#include <G3DAll.h>
#pragma once

class Instance
{
public:
	Instance(void);
	virtual ~Instance(void);
	std::string name;
	Instance* parent;  // Another pointer.
	std::vector<Instance*> children; // All children.
	std::string getClassName();
protected:
	std::string className;
};
