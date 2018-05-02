#include <G3DAll.h>
#pragma once

class AudioPlayer
{
public:
	AudioPlayer(void);
	~AudioPlayer(void);
	static void playSound(std::string);
	static void init();
};
