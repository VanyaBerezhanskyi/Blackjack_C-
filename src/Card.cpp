#include "Card.h"
#include "ResourceManager.h"
#include "GameManager.h"

Card::Card(float x, float y, float width, float height, string texturePath, int cardValue)
{
	xPos = x;
	yPos = y;
	destRect.x = xPos;
	destRect.y = yPos;

	destRect.w = width;
	destRect.h = height;

	face = ResourceManager::getInstance().getTexture(texturePath.c_str());
	back = ResourceManager::getInstance().getTexture("assets/textures/cards/cardBack.png");

	this->cardValue = cardValue;
}

Card::~Card()
{
	SDL_DestroyTexture(face);
	SDL_DestroyTexture(back);
}

Card::Card(Card&& other) noexcept
	: xPos{ other.xPos }, yPos{ other.yPos }, face{ other.face }, back{ other.back }, destRect{ other.destRect },
	cardValue{ other.cardValue }, isFaceUp{ other.isFaceUp }
{
	other.face = nullptr;
	other.back = nullptr;
}

Card& Card::operator=(Card&& other) noexcept
{
	if (this != &other)
	{
		xPos = other.xPos;
		yPos = other.yPos;
		face = other.face;
		back = other.back;
		destRect = other.destRect;
		cardValue = other.cardValue;
		isFaceUp = other.isFaceUp;

		other.face = nullptr;
		other.back = nullptr;
	}

	return *this;
}

void Card::update()
{
	// Moving our card to the target position

	const float moveSpeed{ 1 };
	const float e{ 0.5f }; // Here we account the error because of peculiarities of floating-point numbers

	if (fabs(destRect.x - xPos) > e || fabs(destRect.y - yPos) > e)
	{
		float dx = fabs(destRect.x - xPos); 
		float dy = fabs(destRect.y - yPos);

		float distance = sqrt(dx * dx + dy * dy);

		// Projections of speed by x and y directions
		float speedX = moveSpeed * (dx / distance);
		float speedY = moveSpeed * (dy / distance);

		if (xPos < destRect.x)
			destRect.x -= speedX;
		else if (xPos > destRect.x)
			destRect.x += speedX;

		if (yPos < destRect.y)
			destRect.y -= speedY;
		else if (yPos > destRect.y)
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
	xPos = x;
	yPos = y;
}