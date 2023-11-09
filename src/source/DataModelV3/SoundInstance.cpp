#include "DataModelV3/SoundInstance.h"
#include "DataModelV3/DataModelInstance.h"

using namespace B3D;
using namespace Reflection;

SoundInstance::SoundInstance(void) : Instance("Sound")
{
	name = "Sound";
	soundVolume = Reflection::ReflectionProperty<float>("SoundVolume", 0.5F, TYPE_FLOAT, this->dataTable);
	soundId = Reflection::ReflectionProperty<std::string>("SoundID", "", TYPE_STRING, this->dataTable);
	playOnRemove = Reflection::ReflectionProperty<bool>("PlayOnRemove", false, TYPE_BOOLEAN, this->dataTable);
	looped = Reflection::ReflectionProperty<bool>("Looped", false, TYPE_BOOLEAN, this->dataTable);
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
	return soundVolume.getValue();
}

bool SoundInstance::isPlayedOnRemove()
{
	return playOnRemove.getValue();
}

std::string SoundInstance::getSoundId()
{
	return soundId.getValue();
}

bool SoundInstance::isLooped()
{
	return looped.getValue();
}

// Setters
void SoundInstance::setSoundId(std::string newSoundId)
{
	soundId = newSoundId;
}