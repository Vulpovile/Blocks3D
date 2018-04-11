#pragma once

class Instance
{
public:
	Instance(void);
	~Instance(void);
	std::string name;
	int getType();
	Instance* parent;  // Another pointer.
	static const int BASE_INSTANCE;
	static const int PHYSICAL_INSTANCE;
};
