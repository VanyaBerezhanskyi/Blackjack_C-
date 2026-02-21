#include <string>
#include "AudioManager.h"
#include "Sound.h"
#include "Events.h"

using namespace std;

const string filePaths[] =
{
	"assets/audio/card_hit.ogg",
	"assets/audio/background_music.mp3"
};

Sound cardHit(filePaths[0], Type::Effect);
Sound backgroundMusic(filePaths[1], Type::Music);

void AudioManager::init()
{
	backgroundMusic.playSound();

	const int musicVolume{ 20 };
	backgroundMusic.setVolume(musicVolume);
}

void AudioManager::handleEvents(SDL_Event& event)
{
	if (event.type == HIT_BUTTON_PRESSED || event.type == STAND_BUTTON_PRESSED)
	{
		cardHit.playSound();
	}
}

void AudioManager::update()
{
}
