#pragma once

#include <string>
#include "SDL_ttf.h"

using namespace std;

class Text
{
public:
	Text() = default;
	Text(float x, float y, float width, float height, unsigned fontSize, SDL_Color c, string s);
	~Text();

	Text(const Text&) = default;
	Text& operator=(const Text&) = default;

	Text(Text&& other) noexcept;
	Text& operator=(Text&& other) noexcept;

	void update();
	void render();

	void setText(const string newText);

	pair<float, float> getPosition() const;
	pair<float, float> getSize() const;

private:
	string text;

	SDL_FRect destRect{};

	SDL_Texture* texture{ nullptr };

	SDL_Color color{};

	float xPos{};
	float yPos{};

	unsigned fontSize{};

	static bool isTTFInitialized;
};