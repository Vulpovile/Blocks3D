#pragma once
#include <iostream>
#include <string.h>
class AudioPlayer
{
public:
	AudioPlayer(void);
	~AudioPlayer(void);

	static void init();
	static void playSound(std::string);
};
