#include <iostream>
#include <SDL.h>
#include "UIManager.h"
#include "Text.h"
#include "GameManager.h"

using namespace std;

// Our text objects
Text playerSum;
Text dealerSum;
Text playerMoney;
Text dealerMoney;
Text hitButton;
Text standButton;

void UIManager::init()
{
	// Init data for our text objects

	constexpr unsigned numTexts{ 6 }; // Number of text objects we want to create

	const pair<float, float> textPositions[numTexts] 
	{
		{300.0f, 400.0f}, 
		{300.0f, 75.0f},
		{50.0f, 400.0f},
		{50.0f, 75.0f},
		{1100.0f, 350.0f},
		{1090.0f, 500.0f}
	};

	const pair<float, float> textSizes[numTexts]
	{
		{100.0f, 50.0f},
		{100.0f, 50.0f},
		{100.0f, 50.0f},
		{100.0f, 50.0f},
		{75.0f, 75.0f},
		{100.0f, 100.0f}
	};

	const unsigned fontSizes[numTexts]
	{
		24,
		24,
		24,
		24,
		24,
		24
	};

	// All elements of this array are equal, but we might want to specify different colors for different text objects
	const SDL_Color textColors[numTexts]
	{
		{255, 255, 255, SDL_ALPHA_OPAQUE},
		{255, 255, 255, SDL_ALPHA_OPAQUE},
		{255, 255, 255, SDL_ALPHA_OPAQUE},
		{255, 255, 255, SDL_ALPHA_OPAQUE},
		{255, 255, 255, SDL_ALPHA_OPAQUE},
		{255, 255, 255, SDL_ALPHA_OPAQUE}
	};

	const string textContents[numTexts]
	{
		"Sum: ",
		"Sum: ",
		"$5.00",
		"$5.00",
		"Hit",
		"Stand"
	};

	playerSum =
	{
		textPositions[0].first,
		textPositions[0].second,
		textSizes[0].first,
		textSizes[0].second,
		fontSizes[0],
		textColors[0],
		textContents[0]
	};

	dealerSum =
	{
		textPositions[1].first,
		textPositions[1].second,
		textSizes[1].first,
		textSizes[1].second,
		fontSizes[1],
		textColors[1],
		textContents[1]
	};

	playerMoney =
	{
		textPositions[2].first,
		textPositions[2].second,
		textSizes[2].first,
		textSizes[2].second,
		fontSizes[2],
		textColors[2],
		textContents[2]
	};

	dealerMoney =
	{
		textPositions[3].first,
		textPositions[3].second,
		textSizes[3].first,
		textSizes[3].second,
		fontSizes[3],
		textColors[3],
		textContents[3]
	};

	hitButton =
	{
		textPositions[4].first,
		textPositions[4].second,
		textSizes[4].first,
		textSizes[4].second,
		fontSizes[4],
		textColors[4],
		textContents[4]
	};

	standButton =
	{
		textPositions[5].first,
		textPositions[5].second,
		textSizes[5].first,
		textSizes[5].second,
		fontSizes[5],
		textColors[5],
		textContents[5]
	};
}

void UIManager::handleEvents(GameManager& gameManager, SDL_Event& event)
{
	switch (event.type)
	{
	case SDL_MOUSEBUTTONDOWN:

		// Check if we pressed on button (in our case there are hit and stand)

		int mouseX = event.button.x;
		int mouseY = event.button.y;
		
		// Checking first if we clicked on hit button

		auto [hitX, hitY] = hitButton.getPosition(); // Use structed binding as convenient way of decomposition

		auto [hitWidth, hitHeight] = hitButton.getSize();

		if (mouseX >= hitX && mouseX <= hitX + hitWidth && mouseY >= hitY && mouseY <= hitY + hitHeight)
		{
			gameManager.givePlayerCard();
		}

		// Now checking if we clicked on stand button

		auto [standX, standY] = standButton.getPosition();

		auto [standWidth, standHeight] = standButton.getSize();

		if (mouseX >= standX && mouseX <= standX + standWidth && mouseY >= standY && mouseY <= standY + standHeight)
		{
			gameManager.giveDealerCard();
		}

		break;
	}
}

void UIManager::update()
{
	playerSum.update();
	dealerSum.update();
	playerMoney.update();
	dealerMoney.update();
	hitButton.update();
	standButton.update();
}

void UIManager::render()
{
	playerSum.render();
	dealerSum.render();
	playerMoney.render();
	dealerMoney.render();
	hitButton.render();
	standButton.render();
}