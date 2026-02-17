#pragma once

#include <SDL.h>

class UIManager; // Here we declare only type name "UIManager"

class GameManager
{
public:
	GameManager() = default;

	static SDL_Renderer* renderer;

	void init(const char* title, int xPos, int yPos, int width, int height);
	void handleEvents(UIManager& uiManager);
	void update();
	void render();
	void cleanup();

	bool running() const { return isRunning; }

	void givePlayerCard();
	void giveDealerCard();

private:
	SDL_Window* window{ nullptr };

	bool isRunning{};
};