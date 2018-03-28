#pragma once
#include "settings.h"
#include "evolution.h"

Evolution::Evolution() {}

void Evolution::test() {
	for (uint8 currentGame = 0; currentGame < nrGames; ++currentGame) {
		games[currentGame].play();
	}
}

void Evolution::sort() {

}

void Evolution::kill() {}

void Evolution::evolve() {}
