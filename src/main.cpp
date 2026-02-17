#include "SDL.h"	
#include "GameManager.h"
#include "UIManager.h"

int main(int argc, char* argv[])
{
	const unsigned width{ 1280 };
	const unsigned height{ 720 };

	GameManager gameManager;
	UIManager uiManager;

	gameManager.init("Blackjack", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height);
	uiManager.init();

	while (gameManager.running())
	{
		gameManager.handleEvents(uiManager);

		gameManager.update();
		uiManager.update();

		SDL_RenderClear(GameManager::renderer);
		gameManager.render();
		uiManager.render();
		SDL_RenderPresent(GameManager::renderer);
	}

	gameManager.cleanup();

	return 0;
}