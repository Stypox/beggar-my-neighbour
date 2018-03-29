#pragma once
#include "settings.h"

class Evolution {
private:
	Game games[nrGames];

	uint16 gamesOrder[nrGames];

	uint64 bestResult;
public:
	Evolution();

	void test();
	void sort();
	void evolve();

	uint64 getBestResult();
};