#include "Sound.h"

Sound::Sound(std::string loc)
{
	if (!soundbuffer.loadFromFile(loc))
	{
		printf("soundbuffer not loaded");
	}
	sound.setBuffer(soundbuffer);
}

Sound::~Sound()
{

}

void Sound::PlaySound()
{
	sound.play();
}
