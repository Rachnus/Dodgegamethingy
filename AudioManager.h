#pragma once
#include <SFML/Audio.hpp>
#include <SFML/Main.hpp>
class AudioManager
{
public:
	AudioManager();
	~AudioManager();

	sf::Music music;
	
	void Initialize();
	void PlaySound();
	void StopSound();
};

