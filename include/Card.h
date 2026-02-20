#pragma once

#include <string>
#include <SDL.h>

using namespace std;

struct Position
{
	float x{};
	float y{};
};

class Card
{
public:
	Card() = default;
	Card(float x, float y, int width, int height, string texturePath, int cardValue, bool isAce);
	~Card();
	
	Card(const Card&) = default;
	Card& operator=(const Card&) = default;

	Card(Card&& other) noexcept;
	Card& operator=(Card&& other) noexcept;

	void update();
	void render();

	void setPosition(const float x, const float y);

	int getValue() const;

	void flip() { isFaceUp = !isFaceUp; }
	bool faceUp() { return isFaceUp; }

	bool ace() { return isAce; }

private:
	SDL_FRect destRect{};

	SDL_Texture* face{ nullptr };
	SDL_Texture* back{ nullptr };

	Position position{};

	int cardValue{};

	bool isFaceUp{ false };
	bool isAce{ false };
};
