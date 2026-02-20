#include <iostream>
#include "Text.h"
#include "ResourceManager.h"
#include "GameManager.h"

using namespace std;

bool Text::isTTFInitialized = false;

Text::Text(float x, float y, int width, int height, int fontSize, string text, SDL_Color color)
	: fontSize{ fontSize }, text{ text }, color{ color }
{
	// We defined isTTFInitialized to avoid extra calls to TTF_Init()

	if (!isTTFInitialized && TTF_Init() == -1)
		cout << "Failed to initialize SDL_ttf\n";
	else
		isTTFInitialized = true;

	position.x = x;
	position.y = y;

	destRect.x = x;
	destRect.y = y;

	destRect.w = width;
	destRect.h = height;

	texture = ResourceManager::getInstance().getTexture("assets/fonts/Marlboro.ttf", fontSize, text, color);
}

Text::~Text()
{
	SDL_DestroyTexture(texture);
}

Text::Text(Text&& other) noexcept
	: text{ move(other.text) }, destRect{ other.destRect }, texture{ other.texture },
	position{ other.position }, color{ other.color }, fontSize{ other.fontSize }
{
	other.texture = nullptr;
}

Text& Text::operator=(Text&& other) noexcept
{
	if (this != &other)
	{
		text = move(other.text);
		destRect = other.destRect;
		texture = other.texture;
		position = other.position;
		color = other.color;
		fontSize = other.fontSize;

		other.texture = nullptr;
	}

	return *this;
}

void Text::update()
{
}

void Text::render()
{
	SDL_RenderCopyF(GameManager::renderer, texture, nullptr, &destRect);
}

void Text::setText(const string newText)
{
	text = newText;

	// Destroy the old texture before creating a new one
	SDL_DestroyTexture(texture);

	texture = ResourceManager::getInstance().getTexture("assets/fonts/Marlboro.ttf", fontSize, text, color);
}

Position Text::getPosition() const
{
	return position;
}

pair<float, float> Text::getSize() const
{
	return { destRect.w, destRect.h };
}