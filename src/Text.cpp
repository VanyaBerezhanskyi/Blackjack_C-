#include <iostream>
#include "Text.h"
#include "ResourceManager.h"
#include "GameManager.h"

using namespace std;

bool Text::isTTFInitialized = false;

Text::Text(float x, float y, float width, float height, unsigned fontSize, SDL_Color c, string s)
{
	// We defined isTTFInitialized to avoid extra calls to TTF_Init()

	if (!isTTFInitialized && TTF_Init() == -1)
		cout << "Failed to initialize SDL_ttf\n";

	isTTFInitialized = true;

	xPos = x;
	yPos = y;
	destRect.x = xPos;
	destRect.y = yPos;

	destRect.w = width;
	destRect.h = height;

	this->fontSize = fontSize;

	color = c;
	text = s;

	texture = ResourceManager::getInstance().getTexture("assets/fonts/Marlboro.ttf", fontSize, text, color);
}

Text::~Text()
{
	SDL_DestroyTexture(texture);
}

Text::Text(Text&& other) noexcept
	: xPos{ other.xPos }, yPos{ other.yPos }, destRect{ other.destRect }, texture{ other.texture },
	color{ other.color }, fontSize{ other.fontSize }, text{ move(other.text) }
{
	other.texture = nullptr;
}

Text& Text::operator=(Text&& other) noexcept
{
	if (this != &other)
	{
		xPos = other.xPos;
		yPos = other.yPos;
		destRect = other.destRect;
		texture = other.texture;
		color = other.color;
		fontSize = other.fontSize;
		text = move(other.text);

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

	SDL_DestroyTexture(texture); // Destroy the old texture before creating a new one

	texture = ResourceManager::getInstance().getTexture("assets/fonts/Marlboro.ttf", fontSize, text, color);
}

pair<float, float> Text::getPosition() const
{
	return { xPos, yPos };
}

pair<float, float> Text::getSize() const
{
	return { destRect.w, destRect.h };
}