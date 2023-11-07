#include "DataModelV3/SoundInstance.h"
#include "DataModelV3/DataModelInstance.h"

using namespace B3D;

SoundInstance::SoundInstance()
{
	name = "Sound";

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
	parentDataModel->getSoundService()->playSound(this);
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