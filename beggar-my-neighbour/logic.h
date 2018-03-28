#pragma once
#include "settings.h"


bool isSpecial(uint8 card);


class Game {
private:
	Deck deckA;
	Deck deckB;
	
	Hand hand;

	uint64 rounds;
public:
	Game();

	void resetOriginal();
	void mutateRandom();
	void operator=(Game &game);

	void play();

	bool operator>(Game game) const;
	bool operator<(Game game) const;
	operator uint64() const;
};