#pragma once

#include <string>
#include "SDL.h"
#include "SDL_mixer.h"

using namespace std;

enum class Type
{
	Music,
	Effect
};

class Sound
{
public:
	Sound() = default;
	Sound(string filePath, Type type);
	~Sound();

	void playSound();
	void stopSound();

	void setVolume(int volume);

private:
	Type type;

	Mix_Music* music{ nullptr };
	Mix_Chunk* effect{ nullptr };
};