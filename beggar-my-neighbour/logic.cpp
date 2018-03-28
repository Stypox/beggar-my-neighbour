#pragma once
#include "settings.h"
#include "logic.h"


bool isSpecial(uint8 card) {
	return card == one || card == two || card == three || card == four;
}


Game::Game() : rounds(0) {
	randomize(deckA, deckB);
#ifdef DEBUG_GAME
	std::cout << "Just generated cards from Game():\n";
	deckA.print();
	std::cout << "  |  ";
	deckB.print();
	std::cout << "\n\n";
#endif
}

void Game::resetOriginal() {
	deckA.resetOriginal();
	deckB.resetOriginal();
#ifdef DEBUG_BEGEND
	std::cout << "Just reset cards from resetOriginal():\n";
	deckA.print();
	std::cout << "  |  ";
	deckB.print();
	std::cout << "\n\n";
#endif
}
void Game::mutateRandom() {
	uint8 randA = cardsRand(halfCards),
		randB = cardsRand(halfCards);

	while (!isSpecial(deckA.cards[randA]) && !isSpecial(deckB.cards[randB])) {
		randA = cardsRand(halfCards);
		randB = cardsRand(halfCards);
	}

	deckA.cards[randA] = deckB.originalCards[randB];
	deckB.cards[randB] = deckA.originalCards[randA];
	deckA.originalCards[randA] = deckA.cards[randA];
	deckB.originalCards[randB] = deckB.cards[randB];
#ifdef DEBUG_BEGEND
	std::cout << "Just mutated cards from mutateRandom(). Seeds: " << (int)randA << " " << (int)randB << "\n";
	deckA.print();
	std::cout << "  |  ";
	deckB.print();
	std::cout << "\n\n";
#endif
}
void Game::operator=(Game game) {
	deckA(game.deckA.originalCards);
	deckB(game.deckB.originalCards);
	rounds = 0;

	mutateRandom();
}

void Game::play() {
	rounds = 0;
	bool turn = turnA;
#ifdef DEBUG_GAME 
	bool handBeginner = turn;
#endif
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

		#ifdef DEBUG_LOGIC
			std::cout << "Hand ended at round " << rounds << ": ";
			hand.print();
		#ifndef DEBUG_GAME
			std::cout << "\n\n";
		#endif
		#endif
		#ifdef DEBUG_GAME
		#ifndef DEBUG_LOGIC
			std::cout << "Hand ended at round " << rounds << ": ";
			hand.print();
		#endif
			std::cout << "\nDeckA" << (handBeginner != turnB ? " BEG" : "    ") << (turn != turnB ? " WIN  " : "      ");
			deckA.print();
			std::cout << "\nDeckB" << (handBeginner != turnA ? " BEG" : "    ") << (turn != turnA ? " WIN  " : "      ");
			deckB.print();
			std::cout << "\n\n";
			handBeginner = turn;
		#endif

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

#ifdef DEBUG_LOGIC
	std::cout << (deckA.isEmpty() ? "B won at round " : "A won at round ") << rounds << ": ";
#ifdef DEBUG_BEGEND
	if (deckA.isEmpty()) deckB.print();
	else deckA.print();
#endif
	std::cout << "   ";
	hand.print();
#ifndef DEBUG_BEGEND
	std::cout << "\n\n\n\n";
#endif
#endif
#ifdef DEBUG_BEGEND
#ifndef DEBUG_LOGIC
	std::cout << (deckA.isEmpty() ? "B won at round " : "A won at round ") << rounds << ": ";
	if (deckA.isEmpty()) deckB.print();
	else deckA.print();
	std::cout << "   ";
	hand.print();
#endif
	std::cout << "\n\n\n\n";
#endif

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