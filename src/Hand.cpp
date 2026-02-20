#include "Hand.h"

void Hand::update()
{
	for (auto& card : cards)
		card.update();
}

void Hand::render()
{
	for (auto& card : cards)
		card.render();
}

void Hand::addCard(vector<Card>& deck, Position p, bool isFaceUp)
{
	Card* card = &deck.back();

	card->setPosition(p.x, p.y);

	if (isFaceUp)
		card->flip();

	cards.push_back(move(*card));

	deck.pop_back();
}

void Hand::removeCards(vector<Card>& deck, Position p)
{
	for (auto& card : cards)
	{
		card.setPosition(p.x, p.y);

		if (card.faceUp())
			card.flip();

		deck.push_back(move(card));
	}

	cards.clear();
}

int Hand::calculateSum()
{
	for (; end < cards.size(); ++end)
	{
		if (cards[end].faceUp())
			sum += cards[end].getValue();

		if (cards[end].ace())
			++numberOfAces;
	}

	if (sum > 21)
	{
		// The value by which we decrease sum, that is, set the ace value from 11 to 1 

		const int dValue{ 11 - 1 };

		while (numberOfAces > 0 && sum > 21)
		{
			sum -= dValue;

			--numberOfAces;
		}
	}

	return sum;
}

void Hand::showCard(int index)
{
	cards[index].flip();

	sum += cards[index].getValue();
}

void Hand::reset()
{
	sum = 0;
	numberOfAces = 0;
	end = 0;

	/*for (auto& card : cards)
	{
		card.flip();
	}*/
}