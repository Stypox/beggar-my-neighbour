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

bool Deck::isEmpty() {
	return *cards == empty;
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
	case empty:
		std::cout << "emp\n";
		ShouldTurn = IsLastSeenSpecial;
		IsLastSeenSpecial = false;
		toCall = 1;
		break;
	case one:
		std::cout << "one    ";
		IsLastSeenSpecial = true;
		++currentPosition;
		testOne();
		break;
	case two:
		std::cout << "two    ";
		IsLastSeenSpecial = true;
		++currentPosition;
		testTwo();
		break;
	case three:
		std::cout << "thr    ";
		IsLastSeenSpecial = true;
		++currentPosition;
		testThree();
		break;
	case four:
		std::cout << "fou    ";
		IsLastSeenSpecial = true;
		++currentPosition;
		testFour();
		break;
	default:
		std::cout << "cle    ";
		Ended = true;
		ShouldTurn = true;
		break;
	}
}
void Hand::testTwo() {
	std::cout << (int)currentPosition << " ";
	switch (cards[currentPosition]) {
	case empty:
		std::cout << "emp";
		ShouldTurn = IsLastSeenSpecial;
		IsLastSeenSpecial = false;
		toCall = 2;
		break;
	case one:
		std::cout << "one    ";
		IsLastSeenSpecial = true;
		++currentPosition;
		testOne();
		break;
	case two:
		std::cout << "two    ";
		IsLastSeenSpecial = true;
		++currentPosition;
		testTwo();
		break;
	case three:
		std::cout << "thr    ";
		IsLastSeenSpecial = true;
		++currentPosition;
		testThree();
		break;
	case four:
		std::cout << "fou    ";
		IsLastSeenSpecial = true;
		++currentPosition;
		testFour();
		break;
	default:
		std::cout << "cle    ";
		IsLastSeenSpecial = false;
		++currentPosition;
		testOne();
		break;
	}
}
void Hand::testThree() {
	std::cout << (int)currentPosition << " ";
	switch (cards[currentPosition]) {
	case empty:
		std::cout << "emp";
		ShouldTurn = IsLastSeenSpecial;
		IsLastSeenSpecial = false;
		toCall = 3;
		break;
	case one:
		std::cout << "one    ";
		IsLastSeenSpecial = true;
		++currentPosition;
		testOne();
		break;
	case two:
		std::cout << "two    ";
		IsLastSeenSpecial = true;
		++currentPosition;
		testTwo();
		break;
	case three:
		std::cout << "thr    ";
		IsLastSeenSpecial = true;
		++currentPosition;
		testThree();
		break;
	case four:
		std::cout << "fou    ";
		IsLastSeenSpecial = true;
		++currentPosition;
		testFour();
		break;
	default:
		std::cout << "cle    ";
		IsLastSeenSpecial = false;
		++currentPosition;
		testTwo();
		break;
	}
}
void Hand::testFour() {
	std::cout << (int)currentPosition << " ";
	switch (cards[currentPosition]) {
	case empty:
		std::cout << "emp";
		ShouldTurn = true;
		IsLastSeenSpecial = false;
		toCall = 4;
		break;
	case one:
		std::cout << "one    ";
		IsLastSeenSpecial = true;
		++currentPosition;
		testOne();
		break;
	case two:
		std::cout << "two    ";
		IsLastSeenSpecial = true;
		++currentPosition;
		testTwo();
		break;
	case three:
		std::cout << "thr    ";
		IsLastSeenSpecial = true;
		++currentPosition;
		testThree();
		break;
	case four:
		std::cout << "fou    ";
		IsLastSeenSpecial = true;
		++currentPosition;
		testFour();
		break;
	default:
		std::cout << "cle    ";
		IsLastSeenSpecial = false;
		++currentPosition;
		testOne();
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
		IsLastSeenSpecial = true;
		for (; currentPosition < nrCards; ++currentPosition) {
			std::cout << (int)currentPosition << " ";

			switch (cards[currentPosition]) {
			case empty:
				std::cout << "emp";
				Ended = false;
				ShouldTurn = true;
				std::cout << "\n";
				return;
			case one:
				std::cout << "one    ";
				++currentPosition;
				testOne();
				std::cout << "\n";
				return;
			case two:
				std::cout << "two    ";
				++currentPosition;
				testTwo();
				std::cout << "\n";
				return;
			case three:
				std::cout << "thr    ";
				++currentPosition;
				testThree();
				std::cout << "\n";
				return;
			case four:
				std::cout << "fou    ";
				++currentPosition;
				testFour();
				std::cout << "\n";
				return;
			default:
				std::cout << "cle    ";
			}
		}
		std::cout << "\n";
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