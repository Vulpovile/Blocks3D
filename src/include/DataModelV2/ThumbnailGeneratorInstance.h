#pragma once
#include "instance.h"

class ThumbnailGeneratorInstance :
	public Instance
{
public:
	// Constructor / Destructor
	ThumbnailGeneratorInstance(void);
	~ThumbnailGeneratorInstance(void);

	// Functions
	std::string click(std::string fileType, int cx, int cy, bool hideSky);
};
