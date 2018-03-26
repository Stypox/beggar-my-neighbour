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


	uint8 * cardsA = new uint8[nrCards],
		*cardsB = new uint8[nrCards];
	for (uint8 currentCard = 0; currentCard < halfCards; ++currentCard) {
		input >> cardsA[currentCard];
		cardsB[currentCard + halfCards] = empty;
	}
	for (uint8 currentCard = halfCards; currentCard < nrCards; ++currentCard) {
		input >> cardsB[currentCard - halfCards];
		cardsA[currentCard] = empty;
	}

	if (input.failErr()) return false;

	deckA(cardsA);
	deckB(cardsB);
	delete(cardsA);
	delete(cardsB);
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

	uint8 * cardsA = new uint8[nrCards],
		*cardsB = new uint8[nrCards];
	uint8 currentCard = 0;
	for (; currentCard < halfCards; ++currentCard) {
		cardsA[currentCard] = deckFrom[currentCard];
		cardsB[currentCard + halfCards] = empty;
	}
	for (; currentCard < nrCards; ++currentCard) {
		cardsB[currentCard - halfCards] = deckFrom[currentCard];
		cardsA[currentCard] = empty;
	}

	deckA(cardsA);
	deckB(cardsB);
	delete(cardsA);
	delete(cardsB);
}

void randomize(Deck &deckA, Deck &deckB) {
	uint8 deck[nrCards];
	for (uint8 currentCard = 0; currentCard < nrCards; ++currentCard) {
		deck[currentCard] = basicDeck[currentCard];
	}
	randomizeFromDeck(deckA, deckB, deck);
}
