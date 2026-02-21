#include <iostream>
#include <SDL.h>
#include "UIManager.h"
#include "Text.h"
#include "Events.h"
#include "Messenger.h"

using namespace std;

// Our text objects
// And here we might create for example a vector for our text objects, but I want to have access to specific objects
Text playerSum;
Text dealerSum;
Text playerBet;
Text playerCash;
Text hitButton;
Text standButton;
Text finishText;

void setPlayerSum(const string sum) { playerSum.setText(sum); }
void setDealerSum(const string sum) { dealerSum.setText(sum); }

void setPlayerBet(const string bet) { playerBet.setText(bet); }
void setPlayerCash(const string cash) { playerCash.setText(cash); }

void setFinishText(const string t) { finishText.setText(t); }

void UIManager::init()
{
	// Init data for our text objects

	constexpr int numTexts{ 7 }; // Number of text objects we want to create

	const Position textPositions[numTexts] 
	{
		{350.0f, 420.0f}, 
		{350.0f, 120.0f},
		{90.0f, 350.0f},
		{90.0f, 630.0f},
		{1040.0f, 350.0f},
		{1040.0f, 500.0f},
		{90.0f, 50.0f}
	};

	const pair<int, int> textSizes[numTexts]
	{
		{80, 50},
		{80, 50},
		{80, 50},
		{165, 50},
		{220, 90},
		{220, 90},
		{165, 90}
	};

	const int fontSizes[numTexts]
	{
		34,
		34,
		28,
		26,
		32,
		32,
		48
	};

	// All elements of this array are equal, but we might want to specify different colors for different text objects
	const SDL_Color textColors[numTexts]
	{
		{255, 255, 255, SDL_ALPHA_OPAQUE},
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
		"$",
		"Cash: ",
		"Hit",
		"Stand",
		""
	};

	playerSum =
	{
		textPositions[0].x,
		textPositions[0].y,
		textSizes[0].first,
		textSizes[0].second,
		fontSizes[0],
		textContents[0],
		textColors[0]
	};

	dealerSum =
	{
		textPositions[1].x,
		textPositions[1].y,
		textSizes[1].first,
		textSizes[1].second,
		fontSizes[1],
		textContents[1],
		textColors[1]
	};

	playerBet =
	{
		textPositions[2].x,
		textPositions[2].y,
		textSizes[2].first,
		textSizes[2].second,
		fontSizes[2],
		textContents[2],
		textColors[2]
	};

	playerCash =
	{
		textPositions[3].x,
		textPositions[3].y,
		textSizes[3].first,
		textSizes[3].second,
		fontSizes[3],
		textContents[3],
		textColors[3]
	};

	hitButton =
	{
		textPositions[4].x,
		textPositions[4].y,
		textSizes[4].first,
		textSizes[4].second,
		fontSizes[4],
		textContents[4],
		textColors[4]
	};

	standButton =
	{
		textPositions[5].x,
		textPositions[5].y,
		textSizes[5].first,
		textSizes[5].second,
		fontSizes[5],
		textContents[5],
		textColors[5]
	};

	finishText =
	{
		textPositions[6].x,
		textPositions[6].y,
		textSizes[6].first,
		textSizes[6].second,
		fontSizes[6],
		textContents[6],
		textColors[6]
	};
}

void UIManager::handleEvents(SDL_Event& event)
{
	switch (event.type)
	{
	case SDL_MOUSEBUTTONDOWN:

		// Check if we clicked on button (in our case there are hit and stand)

		int mouseX = event.button.x;
		int mouseY = event.button.y;

		// Checking first if we clicked on hit button

		// Use structed binding as convenient way of decomposition
		auto [hitX, hitY] = hitButton.getPosition();

		auto [hitWidth, hitHeight] = hitButton.getSize();

		if (mouseX >= hitX && mouseX <= hitX + hitWidth && mouseY >= hitY && mouseY <= hitY + hitHeight)
		{
			Messenger::getInstance().broadcastEvent(HIT_BUTTON_PRESSED);
		}

		// Now checking if we clicked on stand button

		auto [standX, standY] = standButton.getPosition();

		auto [standWidth, standHeight] = standButton.getSize();

		if (mouseX >= standX && mouseX <= standX + standWidth && mouseY >= standY && mouseY <= standY + standHeight)
		{
			Messenger::getInstance().broadcastEvent(STAND_BUTTON_PRESSED);
		}

		break;
	}

	if (event.type == GAME_STARTED)
	{
		// Since here we use void*, we need to cast it to the type we need
		setPlayerBet("$" + to_string(*static_cast<int*>(event.user.data1)));
		setPlayerCash("Cash: $" + to_string(*static_cast<int*>(event.user.data2)));
	}
	else if (event.type == PLAYER_SUM_UPDATED)
	{
		setPlayerSum("Sum: " + to_string(*static_cast<int*>(event.user.data1)));
	}
	else if (event.type == DEALER_SUM_UPDATED)
	{
		setDealerSum("Sum: " + to_string(*static_cast<int*>(event.user.data1)));
	}
	else if (event.type == PLAYER_WIN)
	{
		setFinishText("You win!");
		setPlayerCash("Cash: $" + to_string(*static_cast<int*>(event.user.data1)));
	}
	else if (event.type == PLAYER_LOSE)
	{
		setFinishText("You lose!");
		setPlayerCash("Cash: $" + to_string(*static_cast<int*>(event.user.data1)));
	}
	else if (event.type == DRAW)
	{
		setFinishText("Draw!");
	}
	else if (event.type == ROUND_ENDED)
	{
		setFinishText("");
	}
}

void UIManager::update()
{
	playerSum.update();
	dealerSum.update();
	playerBet.update();
	playerCash.update();
	hitButton.update();
	standButton.update();
	finishText.update();
}

void UIManager::render()
{
	playerSum.render();
	dealerSum.render();
	playerBet.render();
	playerCash.render();
	hitButton.render();
	standButton.render();
	finishText.render();
}