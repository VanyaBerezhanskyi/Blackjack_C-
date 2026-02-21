#pragma once

#include "SDL.h"

class UIManager
{
public:
	UIManager() = default;

	void init();
	void handleEvents(SDL_Event& event);
	void update();
	void render();
};