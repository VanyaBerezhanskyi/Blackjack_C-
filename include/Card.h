#pragma once

#include <string>
#include <SDL.h>

using namespace std;

class Card
{
public:
	Card() = default;
	Card(float x, float y, float width, float height, string texturePath, int cardValue);
	~Card();
	
	Card(const Card&) = default;
	Card& operator=(const Card&) = default;

	Card(Card&& other) noexcept;
	Card& operator=(Card&& other) noexcept;

	void update();
	void render();

	void setPosition(const float x, const float y);

	int getValue() const { return cardValue; };

	void flip() { isFaceUp = !isFaceUp; }

private:
	SDL_FRect destRect{};

	SDL_Texture* face{ nullptr };
	SDL_Texture* back{ nullptr };

	float xPos{};
	float yPos{};

	int cardValue{};

	bool isFaceUp{ false };

};
