#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include "GameManager.h"
#include "Card.h"
#include "ResourceManager.h"
#include "UIManager.h"

using namespace std;

void initDeck();
void shuffleDeck();
int calculateSum(vector<Card>& cards);

vector<Card> deck;

vector<Card> playerCards;
vector<Card> dealerCards;

SDL_Renderer* GameManager::renderer = nullptr;

void GameManager::init(const char* title, int xPos, int yPos, int width, int height)
{
	if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
	{
		cout << "Subsystems initialized\n";

		//Create a window
		window = SDL_CreateWindow(title, xPos, yPos, width, height, SDL_WINDOW_OPENGL);

		if (window)
			cout << "Window created\n";

		// Create a renderer
		renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

		if (renderer)
		{
			SDL_SetRenderDrawColor(renderer, 0, 127, 0, SDL_ALPHA_OPAQUE);
			cout << "Renderer created\n";
		}

		initDeck();
		shuffleDeck();

		// Call each function twice because we have two cards at the start for the player and the dealer
		givePlayerCard();
		givePlayerCard();
		giveDealerCard();
		giveDealerCard();

		isRunning = true;
	}
	else
		isRunning = false;
}

void GameManager::handleEvents(UIManager& uiManager)
{
	SDL_Event event;

	SDL_PollEvent(&event);

	uiManager.handleEvents(*this, event);

	switch (event.type)
	{
	case SDL_QUIT:
		isRunning = false;
		break;
	}
}

void GameManager::update()
{
	// Update the deck
	for (auto& card : deck)
		card.update();

	// Update player hand and dealer hand

	for (auto& card : playerCards)
		card.update();

	for (auto& card : dealerCards)
		card.update();
}

void GameManager::render()
{
	// Render the deck
	for (auto& card : deck)
		card.render();

	// Render player hand and dealer hand

	for (auto& card : playerCards)
		card.render();

	for (auto& card : dealerCards)
		card.render();
}

void GameManager::cleanup()
{
	// Since we use C-based SDL2 library, we need to use corresponding functions to cleanup memory, instead of using delete operator
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();

	cout << "Game cleaned\n";
}

void GameManager::givePlayerCard()
{
	// There are possible max 9 cards in hand wihtout going over 21
	const pair<float, float> playerPositions[]
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

	static unsigned count = 0; // Count how many cards we created

	// Here we use move semantics because after pop_back() the card will be destroyed from the deck

	Card* playerCard = &deck.back();
	playerCard->setPosition(playerPositions[count].first, playerPositions[count].second);
	playerCard->flip();
	playerCards.push_back(move(*playerCard));
	deck.pop_back();

	++count;

	//calculateSum(playerCards);
}

void GameManager::giveDealerCard()
{
	const pair<float, float> dealerPositions[]
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

	static unsigned count = 0;

	Card* dealerCard = &deck.back();
	dealerCard->setPosition(dealerPositions[count].first, dealerPositions[count].second);

	// The second card must be face down
	if (count != 1)
		dealerCard->flip();

	dealerCards.push_back(move(*dealerCard));
	deck.pop_back();

	++count;

	//calculateSum(dealerCards);
}

void initDeck()
{
	const float deskX{ 1070.0f };
	const float deskY{ 75.0f };

	const float cardWidth{ 140.0f };
	const float cardHeight{ 190.0f };

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

			if (i != 9)
				cardValue = i + 2; // Card values from 2 to 10, where 10 is represented by 't'
			else
				cardValue = 10; // Jack, Queen, King and Ace (temprorary) are all worth 10 points

			deck.push_back({ deskX, deskY, cardWidth, cardHeight, texturePath, cardValue,});
		}
	}
}	

void shuffleDeck()
{
	random_device rd;
	mt19937 g{ rd() };

	shuffle(deck.begin(), deck.end(), g);
}

//int calculateSum(vector<Card>& cards)
//{
//	static int playerSum = 0;
//	static int dealerSum = 0;
//
//	if (cards == playerCards)
//	{
//		playerSum += playerCards.back().getValue();
//
//		return playerSum;
//	}
//	else
//	{
//		dealerSum += dealerCards.back().getValue();
//
//		return dealerSum;
//	}
//}

