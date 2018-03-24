#include <iostream>
#include <string>
#include <conio.h>
#include <fileManagement.h>

#define DEBUG

using Tstr = std::string;
using int8 = int8_t;
using int16 = int16_t;
using int32 = int32_t;
using int64 = int64_t;
using uint8 = uint8_t;
using uint16 = uint16_t;
using uint32 = uint32_t;
using uint64 = uint64_t;


constexpr const char * inputFilePath = "input.txt";
constexpr uint8 nrCards = 40;
constexpr uint8 empty = 0, one = 1, two = 2, three = 3;



bool isSpecial(uint8);
class TableHand {
private:
	bool justPutSpecial;
	bool ShouldTurn;
	bool Ended;
	uint8 cards[nrCards];

	void testOne(uint8 from) {
		if (from >= nrCards) {
			Ended = true;
			ShouldTurn = true;
			return;
		}

		switch (cards[from]) {
		case empty:
			Ended = false;
			ShouldTurn = justPutSpecial;
			break;
		case one:
			justPutSpecial = true;
			testOne(from + 1);
			break;
		case two:
			justPutSpecial = true;
			testTwo(from + 1);
			break;
		case three:
			justPutSpecial = true;
			testThree(from + 1);
			break;
		default:
			Ended = true;
			ShouldTurn = true;
			break;
		}
	}
	void testTwo(uint8 from) {
		if (from >= nrCards) {
			Ended = true;
			ShouldTurn = true;
			return;
		}

		switch (cards[from]) {
		case empty:
			Ended = false;
			ShouldTurn = justPutSpecial;
			break;
		case one:
			justPutSpecial = true;
			testOne(from + 1);
			break;
		case two:
			justPutSpecial = true;
			testTwo(from + 1);
			break;
		case three:
			justPutSpecial = true;
			testThree(from + 1);
			break;
		default:
			justPutSpecial = false;
			testOne(from + 1);
			break;
		}
	}
	void testThree(uint8 from) {
		if (from >= nrCards) {
			Ended = true;
			ShouldTurn = true;
			return;
		}

		switch (cards[from]) {
		case empty:
			Ended = false;
			ShouldTurn = true;
			break;
		case one:
			justPutSpecial = true;
			testOne(from + 1);
			break;
		case two:
			justPutSpecial = true;
			testTwo(from + 1);
			break;
		case three:
			justPutSpecial = true;
			testThree(from + 1);
			break;
		default:
			justPutSpecial = false;
			testTwo(from + 1);
			break;
		}
	}
public:
	TableHand() {
		for (uint8 currentCard = 0; currentCard < nrCards; ++currentCard) {
			cards[currentCard] = empty;
		}
	}

	void add(uint8 card) {
		for (uint8 currentCard = 0; currentCard < nrCards - 1; ++currentCard) {
			if (cards[currentCard] == empty) {
				cards[currentCard] = card;
				break;
			}
		}
	}
	void clear() {
		for (uint8 currentCard = 0; currentCard < nrCards - 1 && cards[currentCard] != empty; ++currentCard) {
			cards[currentCard] = empty;
		}
		Ended = false;
	}
	uint8 * get() {
		uint8 * newCards = new uint8[nrCards];
		for (uint8 currentCard = 0; currentCard < nrCards; ++currentCard) {
			newCards[currentCard] = cards[currentCard];
		}
		return newCards;
	}
	bool shouldTurn() {
		return ShouldTurn;
	}
	bool ended() {
		return Ended;
	}
	bool isClear() {
		return cards[0] == empty;
	}
	void test() {
		justPutSpecial = true;
		for (uint8 currentCard = 0; currentCard < nrCards; ++currentCard) {
			switch (cards[currentCard]) {
			case empty:
				Ended = false;
				ShouldTurn = true;
				return;
			case one:
				testOne(currentCard + 1);
				return;
			case two:
				testTwo(currentCard + 1);
				return;
			case three:
				testThree(currentCard + 1);
				return;
			}
		}
		Ended = true;
		ShouldTurn = true;
	}

	void print(bool winner, bool beginner) {
		std::cout << "           ";
		bool lastSpecial = 0;
		uint8 counter = 0;
		while (cards[counter] != empty && counter < nrCards) {
			if (isSpecial(cards[counter])) {
				if (counter != 0) {
					std::cout << " ";
				}
				std::cout << (int)cards[counter];

				lastSpecial = 1;
			}
			else {
				if (lastSpecial) {
					std::cout << " ";
					lastSpecial = 0;
				}
				std::cout << '~';
			}
			++counter;
		}

		if (beginner) {
			if (winner) {
				std::cout << "\rp1-p1-";
			}
			else {
				std::cout << "\rp1-p2-";
			}
		}
		else {
			if (winner) {
				std::cout << "\rp2-p1-";
			}
			else {
				std::cout << "\rp2-p2-";
			}
		}
		std::cout << (int)counter << "\n";
	}
};
class Hand {
private:
	uint8 originalCards[nrCards];
	uint8 cards[nrCards];
public:
	Hand() = delete;
	Hand(uint8 Cards[nrCards]) {
		for (uint8 currentCard = 0; currentCard < nrCards; ++currentCard) {
			cards[currentCard] = Cards[currentCard];
			originalCards[currentCard] = Cards[currentCard];
		}
	}

	bool isEmpty() {
		return cards[0] == empty;
	}
	void shift() {
		for (uint8 currentCard = 0; currentCard < nrCards - 1 && cards[currentCard] != empty; ++currentCard) {
			cards[currentCard] = cards[currentCard + 1];
		}
		cards[nrCards - 1] = empty;
	}
	void append(uint8 cardsToAdd[]) {
		for (uint8 currentCard = 0, toAdd = 0; currentCard < nrCards && cardsToAdd[toAdd] != empty; ++currentCard) {
			if (cards[currentCard] == empty) {
				cards[currentCard] = cardsToAdd[toAdd];
				++toAdd;
			}
		}
	}
	uint8 operator[] (uint8 pos) {
		return cards[pos];
	}
	bool isOriginal() {
		for (uint8 currentCard = 0; currentCard < nrCards; ++currentCard) {
			if (originalCards[currentCard] != cards[currentCard]) return false;
		}
		return true;
	}

	void print() {
		uint8 counter = 0;
		bool lastSpecial = 0;
		while (cards[counter] != empty && counter < nrCards) {
			if (isSpecial(cards[counter])) {
				if (counter != 0) {
					std::cout << " ";
				}
				std::cout << (int)cards[counter];
				lastSpecial = 1;
			}
			else {
				if (lastSpecial) {
					std::cout << " ";
					lastSpecial = 0;
				}
				std::cout << '~';
			}
			++counter;
		}
	}
};



uint8 * getFileInput() {
	File input(inputFilePath);
	input.open();


	uint16 tempCard;
	uint8 * cards = new uint8[nrCards];
	for (uint8 currentCard = 0; currentCard < nrCards; ++currentCard) {
		input >> tempCard;
		cards[currentCard] = (uint8)tempCard;
	}
	

	input.close();
	return cards;
}
void divideCards(uint8 * cards, uint8 cardsDx[], uint8 cardsSx[]) {
	for (uint8 currentCard = 0; currentCard < nrCards / 2; ++currentCard) {
		cardsDx[currentCard] = cards[currentCard];
		cardsSx[currentCard + (uint8)ceil(nrCards / 2.0)] = empty;
	}


	for (uint8 currentCard = nrCards / 2; currentCard < nrCards; ++currentCard) {
		cardsSx[currentCard - nrCards + nrCards / 2] = cards[currentCard];
		cardsDx[currentCard] = empty;
	}
}
bool isSpecial(uint8 card) {
	return (card == one) || (card == two) || (card == three);
}

int pressToReturn(int returnValue = 0) {
	std::cout << "\n\n\n";
	std::cout << "main() return value: " << returnValue << "\n";
	std::cout << "Press any key to continue...";
	while (!_kbhit()) {}
	return returnValue;
}


int main() {
	uint8 * cards = getFileInput();
	uint8 P1c[nrCards], P2c[nrCards];
	divideCards(cards, P1c, P2c);
	Hand p1(P1c), p2(P2c);


#ifdef DEBUG
	std::cout << "                                          ";
	p1.print();
	std::cout << "  -  ";
	p2.print();
	std::cout << "\n";
#endif


	TableHand hand;
	bool turn = 1;
	bool beginner = turn;
	uint64 rounds = 0, hands = 0;
	while (!p1.isEmpty() && !p2.isEmpty()) {
		if (turn) {
			hand.add(p1[0]);
			p1.shift();
		}
		else {
			hand.add(p2[0]);
			p2.shift();
		}

		hand.test();

		if (hand.shouldTurn()) {
			turn = !turn;
		}
		if (hand.ended()) {
			if (turn) {
				p1.append(hand.get());
			}
			else {
				p2.append(hand.get());
			}

		#ifdef DEBUG
			std::cout << "                                          ";
			p1.print();
			std::cout << "  -  ";
			p2.print();
			std::cout << "\r";
			hand.print(turn, beginner);
		#endif

			hand.clear();
			beginner = turn;
			++hands;

			if (p1.isOriginal()) {
				++rounds; //TODO infiniy series identification
				return pressToReturn(1);
			}
		}
		++rounds;
	}


	if (!hand.isClear()) {
		turn = !turn;

		if (turn) {
			p1.append(hand.get());
		}
		else {
			p2.append(hand.get());
		}
	}

#ifdef DEBUG
	std::cout << "                                          ";
	p1.print();
	std::cout << "  -  ";
	p2.print();
	std::cout << "\r";
	hand.print(turn, beginner);
	std::cout << "\n";
#endif
	if (turn) {
		std::cout << "\n\n\nPlayer ONE won after ";
	}
	else {
		std::cout << "\n\n\nPlayer TWO won after ";
	}
	std::cout << rounds << " rounds and " << hands + 1 << " hands;";
	
	return pressToReturn();
}