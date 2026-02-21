#include <iostream>
#include "Sound.h"

Sound::Sound(string filePath, Type type)
	: type(type)
{
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 1024) == -1)
	{
		cout << "Audio library coul not be initialized! SDL_mixer error: " << Mix_GetError() << endl;
	}

	if (type == Type::Music)
	{
		music = Mix_LoadMUS(filePath.c_str());

		if (music == nullptr)
		{
			cout << "Failed to load background music! SDL_mixer error: " << Mix_GetError() << endl;
		}
	}
	else if (type == Type::Effect)
	{
		effect = Mix_LoadWAV(filePath.c_str());

		if (effect == nullptr)
		{
			cout << "Failed to load effect! SDL_mixer error: " << Mix_GetError() << endl;
		}
	}
}

Sound::~Sound()
{
	if (music)
		Mix_FreeMusic(music);
	else if (effect)
		Mix_FreeChunk(effect);
}

void Sound::playSound()
{
	if (type == Type::Music)
	{
		if (music != nullptr)
			Mix_PlayMusic(music, -1);
	}
	else if (type == Type::Effect)
	{
		if (effect != nullptr)
			Mix_PlayChannel(-1, effect, 0);
	}
}

void Sound::stopSound()
{
	if (type == Type::Music)
		Mix_HaltMusic();
	else if (type == Type::Effect)
		Mix_HaltChannel(-1);
}

void Sound::setVolume(int volume)
{
	if (type == Type::Music)
		Mix_VolumeMusic(volume);
	else if (type == Type::Effect)
		Mix_VolumeChunk(effect, volume);
}