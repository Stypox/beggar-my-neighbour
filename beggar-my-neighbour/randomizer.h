#pragma once
#include "settings.h"
#include "deck-hand.h"
#include "logic.h"

uint8 cardsRand(uint8 max);

bool getFromFile(Deck &deckA, Deck &deckB);

void randomizeFromDeck(Deck &deckA, Deck &deckB, uint8 deckFrom[nrCards]);

void randomizeFromDeck(Deck &deckA, Deck &deckB, uint8 deckFrom[nrCards], bool winner);

void randomize(Deck &deckA, Deck &deckB);