#include <iostream>
#include <SDL_image.h>
#include "ResourceManager.h"
#include "GameManager.h"

using namespace std;

ResourceManager& ResourceManager::getInstance()
{
	static ResourceManager instance;

	return instance;
}

SDL_Texture* ResourceManager::getTexture(const char* filePath)
{
	auto search = textures.find(filePath);

	if (search == textures.end())
	{
		SDL_Surface* surface = IMG_Load(filePath);

		if (surface == nullptr)
		{
			cout << "Failed to load image\n";
			return nullptr;
		}

		SDL_Texture* texture = SDL_CreateTextureFromSurface(GameManager::renderer, surface);
		SDL_FreeSurface(surface);
		textures.insert({ filePath, texture });
	}

	return textures[filePath];
}

SDL_Texture* ResourceManager::getTexture(const char* filePath, const int fontSize, const string text, const SDL_Color color)
{
	TTF_Font* font = TTF_OpenFont(filePath, fontSize);

	if (font == nullptr)
	{
		cout << "Failed to load font\n";
		return nullptr;
	}

	SDL_Surface* surface = TTF_RenderText_Solid(font, text.c_str(), color);
	TTF_CloseFont(font);
	SDL_Texture* texture = SDL_CreateTextureFromSurface(GameManager::renderer, surface);
	SDL_FreeSurface(surface);

	return texture;
}