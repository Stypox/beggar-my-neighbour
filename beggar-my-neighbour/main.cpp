#include "settings.h"
#include "deck-hand.h"
#include "randomizer.h"

int pressToReturn(int returnValue = 0) {
	std::cout << "\n\n\n";
	std::cout << "main() return value: " << returnValue << "\n";
	std::cout << "Press any key to continue...";
	while (!_kbhit()) {}
	return returnValue;
}

int main() {
	Deck playerA, playerB;
	if (!getFromFile(playerA, playerB)) {
		randomize(playerA, playerB);
	}
	File output(outputFilePath);
	if (output.exists()) {
		output.open();
	}
	else {
		output.create();
	}
	

#ifdef DEBUG_GAME
	std::cout << "Player A: ";
	playerA.print();
	std::cout << "\nPlayer B: ";
	playerB.print();
	std::cout << "\n\n";
#endif
#ifdef DEBUG_TIME
	uint64 nrIterations = 0;
	tPoint pStart = cl::now();
#endif


	Hand hand;
	while (1) {
	loopContinue:

		bool turn = 1;
	#ifdef DEBUG_ENDGAME
		bool handBeginner = turn;
		uint64 rounds = 0, hands = 0;
	#endif
		while (playerA.notEmpty() && playerB.notEmpty()) {
			if (turn) {
				hand.add(playerA.first());
				playerA.shift();
			}
			else {
				hand.add(playerB.first());
				playerB.shift();
			}

			hand.test();

			if (hand.ended()) {
				turn = !turn;
				if (turn) {
					playerA.append(hand.get());
				}
				else {
					playerB.append(hand.get());
				}
				
			#ifdef DEBUG_GAME
				if (handBeginner) {
					if (turn) {
						std::cout << "\nHandBeginner: Player A;    Winner: Player A;";
					}
					else {
						std::cout << "\nHandBeginner: Player A;    Winner: Player B;";
					}
				}
				else {
					if (turn) {
						std::cout << "\nHandBeginner: Player B;    Winner: Player A;";
					}
					else {
						std::cout << "\nHandBeginner: Player B;    Winner: Player B;";
					}
				}
				std::cout << "\nHand: ";
				hand.print();
				std::cout << "\nPlayer A: ";
				playerA.print();
				std::cout << "\nPlayer B: ";
				playerB.print();
				std::cout << "\n\n";
				handBeginner = turn;
				++hands;
			#endif
				hand.clear();

				if (playerA.isOriginal()) {
				#ifdef DEBUG_GAME
					std::cout << "Infinite series found after ";
					std::cout << rounds << " rounds and " << hands + 1 << " hand" << ((hands == 0) ? "" : "s") << ".\n\n\n";
				#endif

					output.append(std::string("\r\n"));
					uint8 * originalPlayerA = playerA.getOriginal();
					uint8 * originalPlayerB = playerB.getOriginal();
					for (uint8 currentCard = 0; currentCard < halfCards; ++currentCard) {
						output.appendWord(std::to_string(originalPlayerA[currentCard]));
					}
					for (uint8 currentCard = 0; currentCard < halfCards; ++currentCard) {
						output.appendWord(std::to_string(originalPlayerB[currentCard]));
					}

					randomize(playerA, playerB);

					goto loopContinue;
				}
			}
			else if (hand.shouldTurn()) {
				turn = !turn;
			}
		#ifdef DEBUG_GAME
			++rounds;
		#endif
		}
		
		if (playerA.notEmpty()) {
			playerA.append(hand.get());
		#ifdef DEBUG_GAME
			if (handBeginner) {
				std::cout << "\nHandBeginner: Player A;    Winner: Player A;";
			}
			else {
				std::cout << "\nHandBeginner: Player B;    Winner: Player A;";
			}
			std::cout << "\nHand: ";
			hand.print();
		#endif
		#ifdef DEBUG_ENDGAME
			std::cout << "\nPlayer A: ";
			playerA.print();
			std::cout << "\nPlayer A won after ";
			std::cout << rounds << " round" << ((rounds == 1) ? "" : "s") << " and " << hands + 1 << " hand" << ((hands == 0) ? "" : "s") << ".\n\n\n\n";
		#endif
			randomizeFromDeck(playerA, playerB, playerA.get());
		}
		else {
			playerB.append(hand.get());
		#ifdef DEBUG_GAME
			std::cout << "\n";
			if (handBeginner) {
				std::cout << "HandBeginner: Player A;    Winner: Player B;";
			}
			else {
				std::cout << "HandBeginner: Player B;    Winner: Player B;";
			}
			std::cout << "\nHand: ";
			hand.print();
		#endif
		#ifdef DEBUG_ENDGAME
			std::cout << "\nPlayer B: ";
			playerB.print();
			std::cout << "\nPlayer B won after ";
			std::cout << rounds << " round" << ((rounds == 1) ? "" : "s") << " and " << hands + 1 << " hand" << ((hands == 0) ? "" : "s") << ".\n\n\n\n";
		#endif
			randomizeFromDeck(playerA, playerB, playerB.get());
		}

		if (!hand.isClear()) {
			hand.clear();
		}

	#ifdef DEBUG_TIME
		if ((nrIterations % printTimeEveryIterations) == 0) {
			tPoint pNow = cl::now();
			uint64 microsSinceStart = std::chrono::duration_cast<micros>(pNow - pStart).count();
			std::cout << "\n" << (double)microsSinceStart / ((double)nrIterations + 1.0);
		}
		++nrIterations;
	#endif
	}

	return pressToReturn();
}