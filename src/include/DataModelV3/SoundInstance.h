#pragma once
#include "Instance.h"
namespace B3D{
	class SoundInstance : public Instance
	{
	public:
		SoundInstance(void);
		~SoundInstance(void);
		
		// Getters
		float getSoundVolume();
		std::string getSoundId();
		bool isPlayedOnRemove();
		bool isLooped();

		// Setters
		void setSoundVolume(float newVolume);
		void setSoundId(std::string newSoundId);
		void setIsPlayedOnRemove(bool isPlayed);
		void setIsLooped(bool isLooped);

		// Functions
		void play();
	private:
		float soundVolume;
		std::string soundId;
		bool playOnRemove;
		bool looped;
	};
}