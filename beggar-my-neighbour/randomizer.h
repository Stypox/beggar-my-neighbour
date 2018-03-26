#pragma once
#include "deck-hand.h"
#include "settings.h"

bool getFromFile(Deck &deckA, Deck &deckB);

void randomizeFromDeck(Deck &deckA, Deck &deckB, uint8 deckFrom[nrCards]);

void randomize(Deck &deckA, Deck &deckB);