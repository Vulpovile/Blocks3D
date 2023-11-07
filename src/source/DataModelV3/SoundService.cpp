#include "DataModelV3/SoundService.h"
#include "StringFunctions.h"
#include "AudioPlayer.h"

using namespace B3D;
SoundService::SoundService()
{
	Instance::Instance("SoundService");
	name = "SoundService";
	musicVolume = 0.3f;
	canDelete = false;

	// Create stock sounds
	SoundInstance* stockSound = new SoundInstance();
	
	// Victory
	stockSound = new SoundInstance();
	stockSound->setName("Victory");
	stockSound->setSoundId("/content/sounds/victory.wav");
	stockSound->setParent(this);

	// Boing
	stockSound = new SoundInstance();
	stockSound->setName("Boing");
	stockSound->setSoundId("/content/sounds/bass.wav");
	stockSound->setParent(this);

	// Bomb
	stockSound = new SoundInstance();
	stockSound->setName("Bomb");
	stockSound->setSoundId("/content/sounds/collide.wav");
	stockSound->setParent(this);

	// Ping
	stockSound = new SoundInstance();
	stockSound->setName("Ping");
	stockSound->setSoundId("/content/sounds/electronicpingshort.wav");
	stockSound->setParent(this);

	// Break
	stockSound = new SoundInstance();
	stockSound->setName("Break");
	stockSound->setSoundId("/content/sounds/glassbreak.wav");
	stockSound->setParent(this);

	// Splat
	stockSound = new SoundInstance();
	stockSound->setName("Splat");
	stockSound->setSoundId("/content/sounds/splat.wav");
	stockSound->setParent(this);

	// Swoosh
	stockSound = new SoundInstance();
	stockSound->setName("Swoosh");
	stockSound->setSoundId("/content/sounds/swoosh.wav");
	stockSound->setParent(this);

	// Snap
	stockSound = new SoundInstance();
	stockSound->setName("Snap");
	stockSound->setSoundId("/content/sounds/snap.wav");
	stockSound->setParent(this);

	// Page
	stockSound = new SoundInstance();
	stockSound->setName("Page");
	stockSound->setSoundId("/content/sounds/pageturn.wav");
	stockSound->setParent(this);

	// Click
	stockSound = new SoundInstance();
	stockSound->setName("Click");
	stockSound->setSoundId("/content/sounds/switch.wav");
	stockSound->setParent(this);

	// Clock
	stockSound = new SoundInstance();
	stockSound->setName("Clock");
	stockSound->setSoundId("/content/sounds/clickfast.wav");
	stockSound->setParent(this);

	// Step
	stockSound = new SoundInstance();
	stockSound->setName("Step");
	stockSound->setSoundId("/content/sounds/SWITCH3.wav");
	stockSound->setParent(this);

	// StepOn
	stockSound = new SoundInstance();
	stockSound->setName("StepOn");
	stockSound->setSoundId("/content/sounds/flashbulb.wav");
	stockSound->setParent(this);
}

SoundService::~SoundService(void)
{
}

void SoundService::playSound(Instance* sound)
{
	// Try to dynamic_cast it to SoundInstance
	SoundInstance* sndInst = dynamic_cast<SoundInstance*>(sound);
	if(sndInst != NULL)
	{
		std::string soundId = sndInst->getSoundId();
		AudioPlayer::playSound(GetFileInPath(soundId));
	}
}

float SoundService::getMusicVolume()
{
	return musicVolume;
}