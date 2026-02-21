#pragma once

#include "SDL.h"

class AudioManager
{
public:
	AudioManager() = default;

	void init();
	void handleEvents(SDL_Event& event);
	void update();
};