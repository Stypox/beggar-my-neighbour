#pragma once

#include "settings.h"
#include "deck-hand.h"


bool isSpecial(uint8 card) {
	return card == one || card == two || card == three || card == four;
}



Deck::Deck() {
	for (uint8 currentCard = 0; currentCard < nrCards; ++currentCard) {
		cards[currentCard] = empty;
		originalCards[currentCard] = empty;
	}
}
Deck::Deck(uint8 Cards[nrCards]) {
	for (uint8 currentCard = 0; currentCard < nrCards; ++currentCard) {
		cards[currentCard] = Cards[currentCard];
		originalCards[currentCard] = Cards[currentCard];
	}
}
void Deck::operator()(uint8 Cards[nrCards]) {
	for (uint8 currentCard = 0; currentCard < nrCards; ++currentCard) {
		cards[currentCard] = Cards[currentCard];
		originalCards[currentCard] = Cards[currentCard];
	}
}

void Deck::shift() {
	for (uint8 currentCard = 0; currentCard < nrCards - 1 && cards[currentCard] != empty; ++currentCard) {
		cards[currentCard] = cards[currentCard + 1];
	}
	cards[nrCards - 1] = empty; //TEST could be useless
}
void Deck::append(uint8 cardsToAdd[]) {
	for (uint8 currentCard = 0, toAdd = 0; currentCard < nrCards && cardsToAdd[toAdd] != empty; ++currentCard) {
		if (cards[currentCard] == empty) {
			cards[currentCard] = cardsToAdd[toAdd];
			++toAdd;
		}
	}
}

bool Deck::notEmpty() {
	return *cards != empty;
}
bool Deck::isOriginal() {
	for (uint8 currentCard = 0; currentCard < nrCards; ++currentCard) {
		if (originalCards[currentCard] != cards[currentCard]) return false;
	}
	return true;
}

uint8 * Deck::get() {
	return cards;
}
uint8 * Deck::getOriginal() {
	return originalCards;
}
uint8 Deck::operator[](uint8 Position) {
	return cards[Position];
}
uint8 Deck::first() {
	return *cards;
}

void Deck::print() {
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
}






void Hand::testOne() {
#ifdef DEBUG_LOGIC
	std::cout << (int)currentPosition << " ";
	switch (cards[currentPosition]) {
	case one:
		std::cout << "one";
		break;
	case two:
		std::cout << "two";
		break;
	case three:
		std::cout << "thr";
		break;
	case four:
		std::cout << "fou";
		break;
	default:
		std::cout << "cle";
		break;
	}
#endif
	switch (cards[currentPosition]) {
	case one:
		ShouldTurn = true;
		++currentPosition;
		toCall = 1;
		break;
	case two:
		ShouldTurn = true;
		++currentPosition;
		toCall = 2;
		break;
	case three:
		ShouldTurn = true;
		++currentPosition;
		toCall = 3;
		break;
	case four:
		ShouldTurn = true;
		++currentPosition;
		toCall = 4;
		break;
	default:
		Ended = true;
		ShouldTurn = true;
		break;
	}
}
void Hand::testTwo() {
#ifdef DEBUG_LOGIC
	std::cout << (int)currentPosition << " ";
	switch (cards[currentPosition]) {
	case one:
		std::cout << "one";
		break;
	case two:
		std::cout << "two";
		break;
	case three:
		std::cout << "thr";
		break;
	case four:
		std::cout << "fou";
		break;
	default:
		std::cout << "cle";
		break;
	}
#endif
	switch (cards[currentPosition]) {
	case one:
		ShouldTurn = true;
		++currentPosition;
		toCall = 1;
		break;
	case two:
		ShouldTurn = true;
		++currentPosition;
		toCall = 2;
		break;
	case three:
		ShouldTurn = true;
		++currentPosition;
		toCall = 3;
		break;
	case four:
		ShouldTurn = true;
		++currentPosition;
		toCall = 4;
		break;
	default:
		ShouldTurn = false;
		++currentPosition;
		toCall = 1;
		break;
	}
}
void Hand::testThree() {
#ifdef DEBUG_LOGIC
	std::cout << (int)currentPosition << " ";
	switch (cards[currentPosition]) {
	case one:
		std::cout << "one";
		break;
	case two:
		std::cout << "two";
		break;
	case three:
		std::cout << "thr";
		break;
	case four:
		std::cout << "fou";
		break;
	default:
		std::cout << "cle";
		break;
	}
#endif
	switch (cards[currentPosition]) {
	case one:
		ShouldTurn = true;
		++currentPosition;
		toCall = 1;
		break;
	case two:
		ShouldTurn = true;
		++currentPosition;
		toCall = 2;
		break;
	case three:
		ShouldTurn = true;
		++currentPosition;
		toCall = 3;
		break;
	case four:
		ShouldTurn = true;
		++currentPosition;
		toCall = 4;
		break;
	default:
		ShouldTurn = false;
		++currentPosition;
		toCall = 2;
		break;
	}
}
void Hand::testFour() {
#ifdef DEBUG_LOGIC
	std::cout << (int)currentPosition << " ";
	switch (cards[currentPosition]) {
	case one:
		std::cout << "one";
		break;
	case two:
		std::cout << "two";
		break;
	case three:
		std::cout << "thr";
		break;
	case four:
		std::cout << "fou";
		break;
	default:
		std::cout << "cle";
		break;
	}
#endif
	switch (cards[currentPosition]) {
	case one:
		ShouldTurn = true;
		++currentPosition;
		toCall = 1;
		break;
	case two:
		ShouldTurn = true;
		++currentPosition;
		toCall = 2;
		break;
	case three:
		ShouldTurn = true;
		++currentPosition;
		toCall = 3;
		break;
	case four:
		ShouldTurn = true;
		++currentPosition;
		toCall = 4;
		break;
	default:
		ShouldTurn = false;
		++currentPosition;
		toCall = 3;
		break;
	}
}

Hand::Hand() : currentPosition(0), toCall(0), ShouldTurn(false), Ended(false) {
	for (uint8 currentCard = 0; currentCard < nrCards; ++currentCard) {
		cards[currentCard] = empty;
	}
}

void Hand::add(uint8 card) {
	cards[currentPosition] = card;
}
void Hand::test() {
#ifdef DEBUG_LOGIC
	switch (toCall) {
	case 0:
		std::cout << "case0    ";
		break;
	case 1:
		std::cout << "case1    ";
		break;
	case 2:
		std::cout << "case2    ";
		break;
	case 3:
		std::cout << "case3    ";
		break;
	case 4:
		std::cout << "case4    ";
		break;
	}
#endif

	switch (toCall) {
	case 0:
		ShouldTurn = true;
		
	#ifdef DEBUG_LOGIC
		std::cout << (int)currentPosition << " ";
		switch (cards[currentPosition]) {
		case one:
			std::cout << "one";
			break;
		case two:
			std::cout << "two";
			break;
		case three:
			std::cout << "thr";
			break;
		case four:
			std::cout << "fou";
			break;
		default:
			std::cout << "cle";
			break;
		}
	#endif
		switch (cards[currentPosition]) {
		case one:
			++currentPosition;
			toCall = 1;
			break;
		case two:
			++currentPosition;
			toCall = 2;
			break;
		case three:
			++currentPosition;
			toCall = 3;
			break;
		case four:
			++currentPosition;
			toCall = 4;
			break;
		default:
			++currentPosition;
			break;
		}

		break;
	case 1:
		testOne();
		break;
	case 2:
		testTwo();
		break;
	case 3:
		testThree();
		break;
	case 4:
		testFour();
		break;
	}

#ifdef DEBUG_LOGIC
	std::cout << "\n";
#endif

}
void Hand::clear() {
	for (uint8 currentCard = 0; currentCard < nrCards; ++currentCard) {
		cards[currentCard] = empty;
	}
	Ended = false;
	toCall = 0;
	currentPosition = 0;
}

bool Hand::shouldTurn() {
	return ShouldTurn;
}
bool Hand::ended() {
	return Ended;
}
bool Hand::isClear() {
	return *cards == empty;
}

uint8 * Hand::get() {
	return cards;
}

void Hand::print() {
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
}
void Hand::print(bool winner, bool beginner) {
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