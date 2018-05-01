#include <G3DAll.h>
#pragma once

class Instance
{
public:
	Instance(void);
	virtual ~Instance(void);
	std::string name;
	
	std::vector<Instance*> children; // All children.
	std::string getClassName();
	Instance* findFirstChild(std::string);
	std::vector<Instance* > getChildren();
	std::vector<Instance* > getAllChildren();
	void setParent(Instance*);
	void addChild(Instance*);
	void removeChild(Instance*);
	Instance* getParent();
protected:
	std::string className;
	Instance* parent;  // Another pointer.
};
