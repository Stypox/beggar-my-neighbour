#pragma once
#include "deck-hand.h"

#include <iostream>

using int8 = int8_t;
using int16 = int16_t;
using int32 = int32_t;
using int64 = int64_t;
using uint8 = uint8_t;
using uint16 = uint16_t;
using uint32 = uint32_t;
using uint64 = uint64_t;

bool isSpecial(uint8 card) {
	return card == one || card == two || card == three || card == four;
}



Deck::Deck() {}
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
	std::cout << (int)currentPosition << " ";
	switch (cards[currentPosition]) {
	case one:
		std::cout << "one";
		ShouldTurn = true;
		IsLastSeenSpecial = false;
		++currentPosition;
		toCall = 1;
		break;
	case two:
		std::cout << "two";
		ShouldTurn = true;
		IsLastSeenSpecial = false;
		++currentPosition;
		toCall = 2;
		break;
	case three:
		std::cout << "thr";
		ShouldTurn = true;
		IsLastSeenSpecial = false;
		++currentPosition;
		toCall = 3;
		break;
	case four:
		std::cout << "fou";
		ShouldTurn = true;
		IsLastSeenSpecial = false;
		++currentPosition;
		toCall = 4;
		break;
	default:
		std::cout << "cle";
		Ended = true;
		ShouldTurn = true;
		break;
	}
}
void Hand::testTwo() {
	std::cout << (int)currentPosition << " ";
	switch (cards[currentPosition]) {
	case one:
		std::cout << "one";
		ShouldTurn = true;
		IsLastSeenSpecial = false;
		++currentPosition;
		toCall = 1;
		break;
	case two:
		std::cout << "two";
		ShouldTurn = true;
		IsLastSeenSpecial = false;
		++currentPosition;
		toCall = 2;
		break;
	case three:
		std::cout << "thr";
		ShouldTurn = true;
		IsLastSeenSpecial = false;
		++currentPosition;
		toCall = 3;
		break;
	case four:
		std::cout << "fou";
		ShouldTurn = true;
		IsLastSeenSpecial = false;
		++currentPosition;
		toCall = 4;
		break;
	default:
		std::cout << "cle";
		ShouldTurn = false;
		IsLastSeenSpecial = false;
		++currentPosition;
		toCall = 1;
		break;
	}
}
void Hand::testThree() {
	std::cout << (int)currentPosition << " ";
	switch (cards[currentPosition]) {
	case one:
		std::cout << "one";
		ShouldTurn = true;
		IsLastSeenSpecial = false;
		++currentPosition;
		toCall = 1;
		break;
	case two:
		std::cout << "two";
		ShouldTurn = true;
		IsLastSeenSpecial = false;
		++currentPosition;
		toCall = 2;
		break;
	case three:
		std::cout << "thr";
		ShouldTurn = true;
		IsLastSeenSpecial = false;
		++currentPosition;
		toCall = 3;
		break;
	case four:
		std::cout << "fou";
		ShouldTurn = true;
		IsLastSeenSpecial = false;
		++currentPosition;
		toCall = 4;
		break;
	default:
		std::cout << "cle";
		ShouldTurn = false;
		IsLastSeenSpecial = false;
		++currentPosition;
		toCall = 2;
		break;
	}
}
void Hand::testFour() {
	std::cout << (int)currentPosition << " ";
	switch (cards[currentPosition]) {
	case one:
		std::cout << "one";
		ShouldTurn = true;
		IsLastSeenSpecial = false;
		++currentPosition;
		toCall = 1;
		break;
	case two:
		std::cout << "two";
		ShouldTurn = true;
		IsLastSeenSpecial = false;
		++currentPosition;
		toCall = 2;
		break;
	case three:
		std::cout << "thr";
		ShouldTurn = true;
		IsLastSeenSpecial = false;
		++currentPosition;
		toCall = 3;
		break;
	case four:
		std::cout << "fou";
		ShouldTurn = true;
		IsLastSeenSpecial = false;
		++currentPosition;
		toCall = 4;
		break;
	default:
		std::cout << "cle";
		ShouldTurn = false;
		IsLastSeenSpecial = false;
		++currentPosition;
		toCall = 3;
		break;
	}
}

Hand::Hand() : currentPosition(0), toCall(0), IsLastSeenSpecial(0), ShouldTurn(0), Ended(0) {
	for (uint8 currentCard = 0; currentCard < nrCards; ++currentCard) {
		cards[currentCard] = empty;
	}
}

void Hand::add(uint8 card) {
	for (int currentCard = 0; currentCard < nrCards; ++currentCard) {
		if (cards[currentCard] == empty) {
			cards[currentCard] = card;
			break;
		}
	}
}
void Hand::test() {
	switch (toCall) {
	case 0:
		std::cout << "case0    ";
		ShouldTurn = true;
		for (; currentPosition < nrCards; ++currentPosition) {
			std::cout << (int)currentPosition << " ";

			switch (cards[currentPosition]) {
			case one:
				std::cout << "one\n";
				IsLastSeenSpecial = false;
				++currentPosition;
				toCall = 1;
				return;
			case two:
				std::cout << "two\n";
				IsLastSeenSpecial = false;
				++currentPosition;
				toCall = 2;
				return;
			case three:
				std::cout << "thr\n";
				IsLastSeenSpecial = false;
				++currentPosition;
				toCall = 3;
				return;
			case four:
				std::cout << "fou\n";
				IsLastSeenSpecial = false;
				++currentPosition;
				toCall = 4;
				return;
			default:
				std::cout << "cle\n";
				++currentPosition;
				return;
			}
		}
		break;
	case 1:
		std::cout << "case1    ";
		testOne();
		std::cout << "\n";
		break;
	case 2:
		std::cout << "case2    ";
		testTwo();
		std::cout << "\n";
		break;
	case 3:
		std::cout << "case3    ";
		testThree();
		std::cout << "\n";
		break;
	case 4:
		std::cout << "case4    ";
		testFour();
		std::cout << "\n";
		break;
	}
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