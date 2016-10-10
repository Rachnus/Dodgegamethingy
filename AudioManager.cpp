#include "AudioManager.h"
#include <iostream>


AudioManager::AudioManager()
{
	Initialize();
}


AudioManager::~AudioManager()
{
}

void AudioManager::Initialize()
{

	if (!music.openFromFile("music/theme.ogg"))
	{
		std::cout << "Error: Could not load theme.wav" << std::endl;
	}

	music.setLoop(true);
	music.setVolume(20);
}

void AudioManager::PlaySound()
{
	music.play();
}

void AudioManager::StopSound()
{
	music.stop();
}