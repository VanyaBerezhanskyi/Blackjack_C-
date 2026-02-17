#pragma once

#include <unordered_map>
#include <string>
#include <SDL.h>
#include <SDL_ttf.h>

using namespace std;

// ResourceManager is a singleton class that manages resources
class ResourceManager
{
public:
	static ResourceManager& getInstance();

	SDL_Texture* getTexture(const char* filePath);													// For images
	SDL_Texture* getTexture(const char* filePath, unsigned fontSize, string text, SDL_Color color); // For fonts

private:
	ResourceManager() = default; // We don't want to create an instance of ResourceManager

	unordered_map<string, SDL_Texture*> textures; // We use this map to not load the same texture multiple times
};