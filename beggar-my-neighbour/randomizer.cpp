#pragma once
#include <fileManagement.h>
#include <algorithm>
#include <random>

#include "settings.h"
#include "deck-hand.h"
#include "randomizer.h"

uint8 cardsRand(uint8 n) {
	srand(rand() + timeRand);
	return rand() % n;
}

bool getFromFile(Deck &deckA, Deck &deckB) {
	File input(inputFilePath);
	input.open();


	for (uint8 currentCard = 0; currentCard < halfCards; ++currentCard) {
		input >> deckA.cards[currentCard];
		deckA.originalCards[currentCard] = deckA.cards[currentCard];
	}
	for (uint8 currentCard = halfCards; currentCard < nrCards; ++currentCard) {
		input >> deckB.cards[currentCard - halfCards];
		deckB.originalCards[currentCard] = deckB.cards[currentCard];
		deckA.cards[currentCard] = empty;
		deckB.cards[currentCard] = empty;
	}

	if (input.failErr()) return false;

	return true;
}

void randomizeFromDeck(Deck &deckA, Deck &deckB, uint8 deckFrom[nrCards]) {
#ifdef DEBUG_RAND
	std::cout << "\n";
	for (uint8 currentCard = 0; currentCard < nrCards; ++currentCard) {
		std::cout << (int)deckFrom[currentCard] << " ";
	}
#endif
	std::random_shuffle(deckFrom, deckFrom + nrCards, cardsRand);
#ifdef DEBUG_RAND
	std::cout << "\n";
	for (uint8 currentCard = 0; currentCard < nrCards; ++currentCard) {
		std::cout << (int)deckFrom[currentCard] << " ";
	}
#endif

	uint8 currentCard = 0;
	for (; currentCard < halfCards; ++currentCard) {
		deckA.originalCards[currentCard] = deckFrom[currentCard];
		deckA.cards[currentCard] = deckFrom[currentCard];
	}
	for (; currentCard < nrCards; ++currentCard) {
		deckB.originalCards[currentCard - halfCards] = deckFrom[currentCard];
		deckB.cards[currentCard - halfCards] = deckFrom[currentCard];
		deckA.cards[currentCard] = empty;
		deckB.cards[currentCard] = empty;
	}
}

void randomizeFromDeck(Deck & deckA, Deck & deckB, uint8 deckFrom[nrCards], bool winner) {
#ifdef DEBUG_RAND
	std::cout << "\n";
	for (uint8 currentCard = 0; currentCard < nrCards; ++currentCard) {
		std::cout << (int)deckFrom[currentCard] << " ";
	}
#endif
	//std::random_shuffle(deckFrom, deckFrom + nrCards, cardsRand); TODO! is this good?
#ifdef DEBUG_RAND
	std::cout << "\n";
	for (uint8 currentCard = 0; currentCard < nrCards; ++currentCard) {
		std::cout << (int)deckFrom[currentCard] << " ";
	}
#endif

	uint8 currentCard = 0;
	for (; currentCard < halfCards; ++currentCard) {
		deckA.originalCards[currentCard] = deckFrom[currentCard];
		deckA.cards[currentCard] = deckFrom[currentCard];
	}
	if (winner) {
		for (; currentCard < nrCards; ++currentCard) {
			deckB.originalCards[currentCard - halfCards] = deckFrom[currentCard];
			deckB.cards[currentCard - halfCards] = deckFrom[currentCard];
			deckA.cards[currentCard] = empty;
		}
	}
	else {
		for (; currentCard < nrCards; ++currentCard) {
			deckB.originalCards[currentCard - halfCards] = deckFrom[currentCard];
			deckB.cards[currentCard - halfCards] = deckFrom[currentCard];
			deckB.cards[currentCard] = empty;
		}
	}
}

void randomize(Deck &deckA, Deck &deckB) {
	uint8 deck[nrCards];
	for (uint8 currentCard = 0; currentCard < nrCards; ++currentCard) {
		deck[currentCard] = basicDeck[currentCard];
	}
	randomizeFromDeck(deckA, deckB, deck);
}
