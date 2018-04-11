#pragma once

class Instance
{
public:
	Instance(void);
	~Instance(void);
	std::string name;
	Instance* parent;  // Another pointer.
	std::string className;
};
