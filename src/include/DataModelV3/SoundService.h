#pragma once
#include "Instance.h"
#include "SoundInstance.h"
namespace B3D
{
	class SoundService : public Instance
	{
	public:
		SoundService(void);
		~SoundService(void);

		float getMusicVolume();
		void playSound(Instance* sound);
	private:
		float musicVolume;
	};
}