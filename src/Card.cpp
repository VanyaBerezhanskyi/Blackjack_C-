#include "Card.h"
#include "ResourceManager.h"
#include "GameManager.h"

Card::Card(float x, float y, int width, int height, string texturePath, int cardValue, bool isAce)
	: cardValue{ cardValue }, isAce{ isAce }
{
	position.x = x;
	position.y = y;

	destRect.x = x;
	destRect.y = y;

	destRect.w = width;
	destRect.h = height;

	face = ResourceManager::getInstance().getTexture(texturePath.c_str());
	back = ResourceManager::getInstance().getTexture("assets/textures/cards/cardBack.png");
}

Card::~Card()
{
	SDL_DestroyTexture(face);
	SDL_DestroyTexture(back);
}

Card::Card(Card&& other) noexcept
	: destRect{other.destRect}, face{ other.face }, back{ other.back }, position{ other.position },
	cardValue{ other.cardValue }, isFaceUp{ other.isFaceUp }, isAce{ other.isAce }
{
	other.face = nullptr;
	other.back = nullptr;
}

Card& Card::operator=(Card&& other) noexcept
{
	if (this != &other)
	{
		destRect = other.destRect;
		face = other.face;
		back = other.back;
		position = other.position;
		cardValue = other.cardValue;
		isFaceUp = other.isFaceUp;
		isAce = other.isAce;

		other.face = nullptr;
		other.back = nullptr;
	}

	return *this;
}

void Card::update()
{
	// Moving our card to the target position

	const float moveSpeed{ 1.5f };

	// Here we account the error because of peculiarities of floating-point numbers
	const float error{ 1.0f };

	if (fabs(destRect.x - position.x) > error || fabs(destRect.y - position.y) > error)
	{
		float dx = fabs(destRect.x - position.x);
		float dy = fabs(destRect.y - position.y);

		float distance = sqrt(dx * dx + dy * dy);

		// Projections of the speed by x and y directions
		float speedX = moveSpeed * (dx / distance);
		float speedY = moveSpeed * (dy / distance);

		if (position.x < destRect.x)
			destRect.x -= speedX;
		else if (position.x > destRect.x)
			destRect.x += speedX;

		if (position.y < destRect.y)
			destRect.y -= speedY;
		else if (position.y > destRect.y)
			destRect.y += speedY;
	}
}

void Card::render()
{
    if (isFaceUp)
        SDL_RenderCopyF(GameManager::renderer, face, nullptr, &destRect);
    else
        SDL_RenderCopyF(GameManager::renderer, back, nullptr, &destRect);
}

void Card::setPosition(const float x, const float y)
{
	position.x = x;
	position.y = y;
}

int Card::getValue() const
{
	const int maxValue{ 11 };

	if (isAce)
		return maxValue; // By default an ace has 11

	return cardValue;
}