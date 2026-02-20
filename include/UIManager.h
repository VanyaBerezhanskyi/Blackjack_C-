#pragma once

#include <string>

using namespace std;

class GameManager; // Here we declare only type name "GameManager"

class UIManager
{
public:
	UIManager() = default;

	void init(GameManager* gm);
	void handleEvents(SDL_Event& event);
	void update();
	void render();

	void setPlayerSum(const string sum);
	void setDealerSum(const string sum);

	void setPlayerBet(const string bet);
	void setPlayerCash(const string cash);

	void setFinishText(const string t);

private:
	GameManager* gameManager{ nullptr };
};