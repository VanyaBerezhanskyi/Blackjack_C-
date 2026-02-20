#include "SDL.h"	
#include "GameManager.h"
#include "UIManager.h"

int main(int argc, char* argv[])
{
	const int width{ 1280 };
	const int height{ 720 };

	const Uint32 frameTime{ 1 / 60 * 1000}; // Use 60 frames per second and convert to ms

	GameManager gameManager;

	gameManager.init("Blackjack", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height);

	while (gameManager.running())
	{
		// Clap frames to 60 per second and here we use Uint32 because this type is returned by SDL_GetTicks()
		Uint32 startTime = SDL_GetTicks();

		gameManager.handleEvents();

		gameManager.update();

		gameManager.render();

		Uint32 elapsedTime = SDL_GetTicks() - startTime;

		if (elapsedTime < frameTime)
			SDL_Delay(frameTime -  elapsedTime);
	}

	gameManager.cleanup();

	return 0;
}