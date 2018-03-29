#pragma once
#include "settings.h"
#include "evolution.h"

Evolution::Evolution() {
	for (uint16 currentGame = 0; currentGame < nrGames; ++currentGame) {
		gamesOrder[currentGame] = currentGame;
	}
}

void Evolution::test() {
	for (uint16 currentGame = noMutateGames; currentGame < nrGames; ++currentGame) {
		games[gamesOrder[currentGame]].play();
	}

#ifdef DEBUG_EVOLUTION_LOGIC
	std::cout << "Played games rounds: ";
	for (uint16 currentGame = 0; currentGame < nrGames; ++currentGame) {
		if (currentGame % 16 == 0) std::cout << "\n";
		std::cout << games[currentGame] << " ";
	}
	std::cout << "\n\n";
#endif
}

void Evolution::sort() {
	uint16 buffer;
	bool loopActive = 1;
	while (loopActive) {
		loopActive = 0;
		for (uint16 currentGame = 0; currentGame < nrGames - 1; ++currentGame) {
			if (games[gamesOrder[currentGame]] < games[gamesOrder[currentGame + 1]]) {
				buffer = gamesOrder[currentGame];
				gamesOrder[currentGame] = gamesOrder[currentGame + 1];
				gamesOrder[currentGame + 1] = buffer;

				loopActive = 1;
			}
		}
	}
	bestResult = games[gamesOrder[0]];

#ifdef DEBUG_EVOLUTION_LOGIC
	std::cout << "Sorted games rounds: ";
	for (uint16 currentGame = 0; currentGame < nrGames; ++currentGame) {
		if (currentGame % 16 == 0) std::cout << "\n";
		std::cout << games[gamesOrder[currentGame]] << " ";
	}
	std::cout << "\n\n";
#endif
}

void Evolution::evolve() {
	for (uint16 currentGame = noMutateGames; currentGame < survivingGames; ++currentGame) {
		games[gamesOrder[currentGame]].resetOriginal();
	}
	for (uint16 currentGame = survivingGames; currentGame < nrGames - randGames; ++currentGame) {
		games[gamesOrder[currentGame]] = games[gamesOrder[currentGame - survivingGames]];
	}
	for (uint16 currentGame = noMutateGames; currentGame < nrGames - randGames; ++currentGame) {
		games[gamesOrder[currentGame]].mutateRandom();
	}
	for (uint16 currentGame = nrGames - randGames; currentGame < nrGames; ++currentGame) {
		games[gamesOrder[currentGame]].randomize();
	}

#ifdef DEBUG_EVOLUTION_LOGIC
#ifdef DEBUG_GAME
	std::cout << "Evolved games: ";
	for (uint16 currentGame = 0; currentGame < nrGames; ++currentGame) {
		std::cout << "\n";
		games[currentGame].print();
	}
	std::cout << "\n\n";
#endif
#endif
}

uint64 Evolution::getBestResult() {
	return bestResult;
}
