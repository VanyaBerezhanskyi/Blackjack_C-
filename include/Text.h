#pragma once

#include <string>
#include "SDL_ttf.h"

using namespace std;

struct Position
{
	float x{};
	float y{};
};

class Text
{
public:
	Text() = default;
	Text(float x, float y, int width, int height, int fontSize, string text, SDL_Color color);
	~Text();

	Text(const Text&) = default;
	Text& operator=(const Text&) = default;

	Text(Text&& other) noexcept;
	Text& operator=(Text&& other) noexcept;

	void update();
	void render();

	void setText(const string newText);

	Position getPosition() const;
	pair<float, float> getSize() const;

private:
	string text;

	SDL_FRect destRect{};

	SDL_Texture* texture{ nullptr };

	Position position{};

	SDL_Color color{};

	int fontSize{};

	static bool isTTFInitialized;
};