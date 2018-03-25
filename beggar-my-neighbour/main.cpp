#define DEBUG


#include <iostream>
#include <conio.h>
#include <fileManagement.h>
#include "deck-hand.h"

constexpr const char * inputFilePath = "input.txt";


void getFileInput(Deck &deckA, Deck &deckB) {
	File input(inputFilePath);
	input.open();


	uint8 * cardsA = new uint8[nrCards],
		  * cardsB = new uint8[nrCards];
	for (uint8 currentCard = 0; currentCard < halfCards; ++currentCard) {
		input >> cardsA[currentCard];
		cardsB[currentCard + halfCards] = empty;
	}
	for (uint8 currentCard = halfCards; currentCard < nrCards; ++currentCard) {
		input >> cardsB[currentCard - halfCards];
		cardsA[currentCard] = empty;
	}

	deckA(cardsA);
	deckB(cardsB);
}
int pressToReturn(int returnValue = 0) {
	std::cout << "\n\n\n";
	std::cout << "main() return value: " << returnValue << "\n";
	std::cout << "Press any key to continue...";
	while (!_kbhit()) {}
	return returnValue;
}

int main() {
	Deck playerA, playerB;
	getFileInput(playerA, playerB);

#ifdef DEBUG
	std::cout << "Player A: ";
	playerA.print();
	std::cout << "\nPlayer B: ";
	playerB.print();
	std::cout << "\n\n";
#endif

	Hand hand;
	bool turn = 1;
	bool handBeginner = turn;
	uint64 rounds = 0, hands = 0;


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


		#ifdef DEBUG
			std::cout << "\n";
			if (handBeginner) {
				if (turn) {
					std::cout << "HandBeginner: Player A;    Winner: Player A;";
				}
				else {
					std::cout << "HandBeginner: Player A;    Winner: Player B;";
				}
			}
			else {
				if (turn) {
					std::cout << "HandBeginner: Player B;    Winner: Player A;";
				}
				else {
					std::cout << "HandBeginner: Player B;    Winner: Player B;";
				}
			}
			std::cout << "\nHand: ";
			hand.print();
			std::cout << "\nPlayer A: ";
			playerA.print();
			std::cout << "\nPlayer B: ";
			playerB.print();
			std::cout << "\n\n";
		#endif

			hand.clear();
			handBeginner = turn;
			++hands;

			if (playerA.isOriginal()) {
				std::cout << "Infinite series found after ";
				std::cout << rounds << " rounds and " << hands + 1 << " hand" << ((hands == 0) ? "" : "s") << ".\n";
				return pressToReturn(1);
			}
		}
		else if (hand.shouldTurn()) {
			turn = !turn;
		}

		++rounds;
		std::cout << "Turn: " << turn << "\n";
	}

	turn = playerA.notEmpty();

	if (!hand.isClear()) {
		if (turn) {
			playerA.append(hand.get());
		}
		else {
			playerB.append(hand.get());
		}
	}
	
#ifdef DEBUG
	std::cout << "\n";
	if (handBeginner) {
		if (turn) {
			std::cout << "HandBeginner: Player A;    Winner: Player A;";
		}
		else {
			std::cout << "HandBeginner: Player A;    Winner: Player B;";
		}
	}
	else {
		if (turn) {
			std::cout << "HandBeginner: Player B;    Winner: Player A;";
		}
		else {
			std::cout << "HandBeginner: Player B;    Winner: Player B;";
		}
	}
	std::cout << "\nHand: ";
	hand.print();
	if (turn) {
		std::cout << "\nPlayer A: ";
		playerA.print();
	}
	else {
		std::cout << "\nPlayer B: ";
		playerB.print();
	}
	std::cout << "\n\n";
#endif

	if (turn) {
		std::cout << "\n\n\nPlayer A won after ";
	}
	else {
		std::cout << "\n\n\nPlayer B won after ";
	}
	std::cout << rounds << " round" << ((rounds == 1) ? "" : "s") << " and " << hands + 1 << " hand" << ((hands == 0) ? "" : "s") << ".\n";

	return pressToReturn();
}