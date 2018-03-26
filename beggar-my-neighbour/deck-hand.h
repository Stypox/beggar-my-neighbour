#pragma once
#include "settings.h"


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

	bool notEmpty();
	bool isOriginal();

	uint8 * get();
	uint8 * getOriginal();
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

	bool ShouldTurn, Ended;

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