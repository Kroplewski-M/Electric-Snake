#pragma once
#include <SFML/Audio.hpp>


class Sound
{
public:
	Sound(std::string loc);
	~Sound();
	void PlaySound();
private:
	sf::SoundBuffer soundbuffer;
	sf::Sound sound;


};

