#pragma once

#include <string>
using Tstr = std::string;
using int8 = int8_t;
using int16 = int16_t;
using int32 = int32_t;
using int64 = int64_t;
using uint8 = uint8_t;
using uint16 = uint16_t;
using uint32 = uint32_t;
using uint64 = uint64_t;

constexpr uint8 nrCards = 40, halfCards = 20; //TODO! set to 52
constexpr uint8 empty = 255, one = 1, two = 2, three = 3, four = 4;

//cards in players' hand
class Deck {
private:
	uint8 originalCards[nrCards];
	uint8 cards[nrCards];

public:
	Deck();
	Deck(uint8 Cards[nrCards]);
	void operator() (uint8 Cards[nrCards]);

	void shift();
	void append(uint8 cardsToAdd[]);

	bool isEmpty();
	bool isOriginal();

	uint8 operator[] (uint8 Position);
	uint8 first();

	void print();
};

//cards on the table
class Hand {
private:
	uint8 cards[nrCards];

	uint8 toCall;
	uint8 currentPosition;

	bool IsLastSeenSpecial, ShouldTurn, Ended;

	void testOne();
	void testTwo();
	void testThree();
	void testFour();

public:
	Hand();

	void add(uint8 card);
	void test();
	void clear();

	bool shouldTurn();
	bool ended();
	bool isClear();

	uint8 * get();

	void print();
	void print(bool winner, bool beginner);
};