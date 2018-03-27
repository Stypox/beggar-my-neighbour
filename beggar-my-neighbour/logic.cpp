#pragma once
#include "settings.h"
#include "logic.h"

Game::Game() : rounds(0) {
	randomize(deckA, deckB);
}

void Game::mutateRandom() {
	uint8 randA = cardsRand(halfCards),
		randB = cardsRand(halfCards);
	deckA.cards[randA] = deckB.originalCards[randB];
	deckB.cards[randB] = deckA.originalCards[randA];
	deckA.originalCards[randA] = deckA.cards[randA];
	deckB.originalCards[randB] = deckB.cards[randB];
}
void Game::operator=(Game game) {
	deckA(game.deckA.originalCards);
	deckB(game.deckB.originalCards);
	rounds = 0;

	mutateRandom();
}

void Game::play() {
	bool turn = turnA;
	while (1) {
		++rounds;
		if (turn) {
			hand.add(deckA.first());
			deckA.shift();
		}
		else {
			hand.add(deckB.first());
			deckB.shift();
		}

		hand.test();

		if (hand.ended()) {
			turn = !turn;
			if (turn)
				deckA.append(hand.get());
			else
				deckB.append(hand.get());

			hand.clear();

			if (deckA.isOriginal() || deckB.isOriginal()) {
				File output(outputFilePath);

				uint8 * originalA = deckA.getOriginal();
				uint8 * originalB = deckB.getOriginal();
				if (!output.append("\r\n")) {
					while (1) {
						for (uint8 currentCard = 0; currentCard < halfCards; ++currentCard)
							std::cout << deckA[currentCard];
						for (uint8 currentCard = 0; currentCard < halfCards; ++currentCard)
							std::cout << deckB[currentCard];
						std::cout << "\n";
					}
				}
				for (uint8 currentCard = 0; currentCard < halfCards; ++currentCard)
					output.appendWord(std::to_string(deckA[currentCard]));
				for (uint8 currentCard = 0; currentCard < halfCards; ++currentCard)
					output.appendWord(std::to_string(deckB[currentCard]));
				
			}
		}
		else if (hand.shouldTurn())
			turn = !turn;

		if ((turn != turnB && deckA.isEmpty()) || (turn != turnA && deckB.isEmpty())) break;
	}
	hand.clear();
}

bool Game::operator>(Game game) const  {
	return rounds > game.rounds;
}
bool Game::operator<(Game game) const  {
	return rounds < game.rounds;
}

Game::operator uint64() const {
	return rounds;
}
