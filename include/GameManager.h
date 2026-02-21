#pragma once

#include <SDL.h>

class GameManager
{
public:
	GameManager() = default;

	static SDL_Renderer* renderer;

	void init(const char* title, int x, int y, int width, int height);
	void handleEvents(SDL_Event& event);
	void update();
	void render();
	void cleanup();

	bool running() const { return isRunning; }

private:
	SDL_Window* window{ nullptr };

	bool isRunning{};
};