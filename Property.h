#pragma once
#include <G3DAll.h>
class Property
{
public:
	std::string title;
	std::string propName;
	void * prop;
	void *(*getFunc)(void);
	void(*setFunc)(void *);
	void setProperty(void*);
	void * getProperty();
	Property(std::string title, std::string propName, void * prop, void *(*getFunc)(void), void(*setFunc)(void *));
	~Property(void);
};
