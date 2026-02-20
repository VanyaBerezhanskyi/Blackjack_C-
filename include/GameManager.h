#pragma once

#include <SDL.h>
#include <set>

using namespace std;

class UIManager; // Here we declare only type name "UIManager"

enum class GameResult
{
	playerWin,
	playerLose,
	draw
};

class GameManager
{
public:
	GameManager() = default;

	static SDL_Renderer* renderer;

	void init(const char* title, int x, int y, int width, int height);
	void handleEvents();
	void update();
	void render();
	void cleanup();

	bool running() const { return isRunning; }

	void onHitPressed();
	void onStandPressed();

private:
	SDL_Window* window{ nullptr };

	bool isRunning{};
};