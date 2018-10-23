
#pragma once
#include <G3DAll.h>
#include "Property.h"
class Instance
{
public:
	std::vector<Property> properties;
	Instance(void);
	Instance(const Instance&);
	virtual ~Instance(void);
	std::string name;
	virtual void render(RenderDevice*);
	std::vector<Instance*> children; // All children.
	std::string getClassName();
	Instance* findFirstChild(std::string);
	std::vector<Instance* > getChildren();
	std::vector<Instance* > getAllChildren();
	void setParent(Instance*);
	void addChild(Instance*);
	void removeChild(Instance*);
	Instance* getParent();
	virtual Instance* clone() const { return new Instance(*this); }
protected:
	std::string className;
	Instance* parent;  // Another pointer.
	void initProperties();
};
