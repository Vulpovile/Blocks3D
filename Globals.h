#pragma once
#include "DataModelInstance.h"

class Globals
{
public:
    Globals(void);
    ~Globals(void);
    static DataModelInstance* dataModel;
};