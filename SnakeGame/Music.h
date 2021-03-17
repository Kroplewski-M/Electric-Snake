#pragma once
#include <SFML/Audio.hpp>	
#include <SFML/Audio/Music.hpp>

class Music
{
public:
	Music(std::string loc);
	~Music();
	void PlaySound();
	void SetLoop(bool x);
	void SetVolume(int volume);
private:
	sf::Music music;
	std::string location;

};

