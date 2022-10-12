#include "DataModelV2/SoundInstance.h"
#include "Globals.h"

SoundInstance::SoundInstance()
{
	name = "Sound";
	className = "Sound";

	soundVolume = 0.5;
	soundId = "";
	playOnRemove = false;
	looped = false;
}

SoundInstance::~SoundInstance(void)
{
	if(isPlayedOnRemove())
		play();
}

// Functions
void SoundInstance::play()
{
	g_dataModel->getSoundService()->playSound(this);
}

// Getters
float SoundInstance::getSoundVolume()
{
	return soundVolume;
}

bool SoundInstance::isPlayedOnRemove()
{
	return playOnRemove;
}

std::string SoundInstance::getSoundId()
{
	return soundId;
}

bool SoundInstance::isLooped()
{
	return looped;
}

// Setters
void SoundInstance::setSoundId(std::string newSoundId)
{
	soundId = newSoundId;
}