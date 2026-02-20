#pragma once

#include <vector>
#include "Card.h"

class Hand
{
public:
	Hand() = default;

	void update();
	void render();

	void addCard(vector<Card>& deck, Position p, bool isFaceUp);
	void removeCards(vector<Card>& deck, Position p);

	int calculateSum();
	
	void showCard(int index);

	void reset();

private:
	vector<Card> cards;

	int sum{};

	int numberOfAces{};

	// Index past the last card to remember where we left off to not revisited old elements when calculate the sum
	int end{};
};