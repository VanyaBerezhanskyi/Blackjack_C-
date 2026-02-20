#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include "GameManager.h"
#include "Card.h"
#include "Hand.h"
#include "ResourceManager.h"
#include "UIManager.h"

using namespace std;

void initDeck();
void shuffleDeck();
void dealCards();
void endRound(GameResult gr);
void restartGame();

// Additional managers
UIManager uiManager;

const float deskX{ 1070.0f };
const float deskY{ 75.0f };

vector<Card> deck;

// There are possible max 9 cards in hand wihtout going over 21
const Position playerCardsPositions[]
{
	{535.0f, 400.0f},
	{570.0f, 400.0f},
	{605.0f, 400.0f},
	{640.0f, 400.0f},
	{675.0f, 400.0f},
	{710.0f, 400.0f},
	{745.0f, 400.0f},
	{780.0f, 400.0f},
	{815.0f, 400.0f},
};

const Position dealerCardsPositions[]
{
	{535.0f, 75.0f},
	{570.0f, 75.0f},
	{605.0f, 75.0f},
	{640.0f, 75.0f},
	{675.0f, 75.0f},
	{710.0f, 75.0f},
	{745.0f, 75.0f},
	{780.0f, 75.0f},
	{815.0f, 75.0f},
};

Hand player;
Hand dealer;

// Counts how many cards we created for the player and the dealer
int playerCount{};
int dealerCount{};

int playerSum{};
int dealerSum{};

// At the start assume the player has 500 dollars
int playerCash{500};

// Assume all time we have the same bet 5 dollars
int playerBet{ 5 };

// Register our custom events
Uint32 ROUND_END = SDL_RegisterEvents(1);
Uint32 CARDS_RETURN = SDL_RegisterEvents(1);
Uint32 GAME_END = SDL_RegisterEvents(1);

SDL_Renderer* GameManager::renderer{ nullptr };

void GameManager::init(const char* title, int x, int y, int width, int height)
{
	if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
	{
		cout << "Subsystems initialized\n";

		//Create a window
		window = SDL_CreateWindow(title, x, y, width, height, SDL_WINDOW_OPENGL);

		if (window)
			cout << "Window created\n";

		// Create a renderer
		renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

		if (renderer)
		{
			SDL_SetRenderDrawColor(renderer, 0, 127, 0, SDL_ALPHA_OPAQUE);

			cout << "Renderer created\n";
		}

		// Init managers

		uiManager.init(this);

		//..............

		initDeck();
		shuffleDeck();
		dealCards();

		uiManager.setPlayerBet(to_string(playerBet));
		uiManager.setPlayerCash(to_string(playerCash));

		isRunning = true;
	}
	else
		isRunning = false;
}

void GameManager::handleEvents()
{
	SDL_Event event;

	SDL_PollEvent(&event);

	// Handle managers

	uiManager.handleEvents(event);

	switch (event.type)
	{
	case SDL_QUIT:
		isRunning = false;
		break;
	}

	if (event.type == ROUND_END)
	{
		restartGame();
	}
	else if (event.type == CARDS_RETURN)
	{
		dealCards();
	}
	else if (event.type == GAME_END)
	{
		isRunning = false;
	}
}

void GameManager::update()
{
	// Update the deck
	for (auto& card : deck)
		card.update();

	player.update();
	dealer.update();

	//Update managers

	uiManager.update();
}

void GameManager::render()
{
	SDL_RenderClear(GameManager::renderer);

	// Render the deck
	for (auto& card : deck)
		card.render();

	player.render();
	dealer.render();

	// Render managers

	uiManager.render();

	SDL_RenderPresent(GameManager::renderer);
}

void GameManager::cleanup()
{
	// Since we use C-based SDL2 library, we need to use corresponding functions to cleanup memory, instead of using delete operator
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();

	cout << "Game cleaned\n";
}

void GameManager::onHitPressed()
{
	player.addCard(deck, playerCardsPositions[playerCount], true);
	++playerCount;

	playerSum = player.calculateSum();
	uiManager.setPlayerSum(to_string(playerSum));

	if (playerSum > 21)
	{
		endRound(GameResult::playerLose);
	}
}

void GameManager::onStandPressed()
{
	// Show the second card of the dealer

	dealer.showCard(1);

	while (dealerSum < 17)
	{
		dealer.addCard(deck, dealerCardsPositions[dealerCount], true);
		++dealerCount;

		dealerSum = dealer.calculateSum();
	}

	uiManager.setDealerSum(to_string(dealerSum));

	if (dealerSum > 21)
	{
		endRound(GameResult::playerWin);
		return;
	}

	if (playerSum > dealerSum)
		endRound(GameResult::playerWin);
	if (playerSum < dealerSum)
		endRound(GameResult::playerLose);
	else if (playerSum == dealerSum)
		endRound(GameResult::draw);
}

void initDeck()
{
	const int cardWidth{ 140 };
	const int cardHeight{ 190 };

	const string cardsNames[13][4] = {
		{"2C", "2D", "2H", "2S"},
		{"3C", "3D", "3H", "3S"},
		{"4C", "4D", "4H", "4S"},
		{"5C", "5D", "5H", "5S"},
		{"6C", "6D", "6H", "6S"},
		{"7C", "7D", "7H", "7S"},
		{"8C", "8D", "8H", "8S"},
		{"9C", "9D", "9H", "9S"},
		{"tC", "tD", "tH", "tS"},
		{"jC", "jD", "jH", "jS"},
		{"qC", "qD", "qH", "qS"},
		{"kC", "kD", "kH", "kS"},
		{"aC", "aD", "aH", "aS"}
	};

	for (int i = 0; i < 13; ++i)
	{
		for (int j = 0; j < 4; ++j)
		{
			string texturePath = "assets/textures/cards/" + cardsNames[i][j] + ".png";

			int cardValue{};

			if (i < 9)
				cardValue = i + 2; // Card values from 2 to 10, where 10 is represented by 't'
			else
				cardValue = 10; // Jack, Queen, King and Ace (temprorary) are all worth 10 points

			// Aces have first index equals 12, that is, they are last in the array
			deck.push_back({ deskX, deskY, cardWidth, cardHeight, texturePath, cardValue, i == 12});
		}
	}
}	

void shuffleDeck()
{
	random_device rd;
	mt19937 g{ rd() };

	shuffle(deck.begin(), deck.end(), g);
}

void dealCards()
{
	// The dealer and the player have 2 cards at the start
	const int numCards{ 2 };

	for (; playerCount < numCards; ++playerCount)
	{
		player.addCard(deck, playerCardsPositions[playerCount], true);
	}

	for (; dealerCount < numCards; ++dealerCount)
	{
		// We hide the second card

		if (dealerCount == 1)
			dealer.addCard(deck, dealerCardsPositions[dealerCount], false);
		else
			dealer.addCard(deck, dealerCardsPositions[dealerCount], true);
	}

	playerSum = player.calculateSum();
	uiManager.setPlayerSum(to_string(playerSum));

	dealerSum = dealer.calculateSum();
	uiManager.setDealerSum(to_string(dealerSum));
}

void endRound(GameResult gr)
{
	switch (gr)
	{
	case GameResult::playerLose:

		uiManager.setFinishText("You lose");

		playerCash -= playerBet;

		if (playerCash < 0)
		{
			SDL_AddTimer
			(3000,
				[](Uint32 interval, void* param)->Uint32
				{
					SDL_Event event;
					event.type = GAME_END;
					SDL_PushEvent(&event);
					return 0;
				},
				nullptr
				);
		}

		break;

	case GameResult::playerWin:

		uiManager.setFinishText("You win");

		playerCash += playerBet;

		break;

	case GameResult::draw:

		uiManager.setFinishText("Draw");

		break;
	}

	uiManager.setPlayerCash(to_string(playerCash));

	SDL_AddTimer
	(3000,
		[](Uint32 interval, void* param)->Uint32
		{
			SDL_Event event;
			event.type = ROUND_END;
			SDL_PushEvent(&event);
			return 0;
		},
		nullptr
		);
}

void restartGame()
{
	player.removeCards(deck, { deskX, deskY });
	dealer.removeCards(deck, { deskX, deskY });

	player.reset();
	dealer.reset();

	shuffleDeck();

	playerCount = 0;
	dealerCount = 0;

	uiManager.setFinishText("");

	SDL_AddTimer
	(2000,
		[](Uint32 interval, void* param)->Uint32
		{
			SDL_Event event;
			event.type = CARDS_RETURN;
			SDL_PushEvent(&event);
			return 0;
		},
		nullptr
	);
}
