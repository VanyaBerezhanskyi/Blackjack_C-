#pragma once

#include <string>
#include <unordered_map>
#include <SDL.h>
#include <SDL_ttf.h>

using namespace std;

// ResourceManager is a singleton class that manages resources
class ResourceManager
{
public:
	static ResourceManager& getInstance();

	// For images
	SDL_Texture* getTexture(const char* texturePath);		

	// For fonts
	SDL_Texture* getTexture(const char* texturePath, const int fontSize, const string text, const SDL_Color color);

private:
	// We don't want to create an instance of ResourceManager
	ResourceManager() = default;

	// We use this map to not load the same texture multiple times
	unordered_map<string, SDL_Texture*> textures;
};