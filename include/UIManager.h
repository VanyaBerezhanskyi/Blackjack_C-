#pragma once

class GameManager; // Here we declare only type name "GameManager"

class UIManager
{
public:
	UIManager() = default;

	void init();
	void handleEvents(GameManager& gameManager, SDL_Event& event);
	void update();
	void render();
};