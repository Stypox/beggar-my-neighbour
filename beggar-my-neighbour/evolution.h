#pragma once
#include "settings.h"

class Evolution {
private:
	Game games[nrGames];
public:
	Evolution();

	void test();
	void sort();
	void kill();
	void evolve();
};