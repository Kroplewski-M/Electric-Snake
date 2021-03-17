#include "Music.h"

Music::Music(std::string loc)
	:location(loc)
{

	if (!music.openFromFile(location))
	{
		printf("cant open music");
	}
	music.setVolume(60);
	
}

Music::~Music()
{

}

void Music::PlaySound()
{
	music.play();
}

void Music::SetLoop(bool x)
{
	music.setLoop(x);
}

void Music::SetVolume(int volume)
{
	music.setVolume(volume);
}

