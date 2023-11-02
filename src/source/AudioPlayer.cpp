#include "AudioPlayer.h"
#include <Windows.h>
#include <Mmsystem.h>
#define NUM_SOUNDS 32
static bool initiated = false;

AudioPlayer::AudioPlayer(void)
{
	
}

AudioPlayer::~AudioPlayer(void)
{
}

void AudioPlayer::init()
{
	initiated = true;
}

void AudioPlayer::playSound(std::string fileString)
{
	//TODO probably use something a bit better
	PlaySound(fileString.c_str(), NULL, SND_FILENAME | SND_ASYNC);
}
