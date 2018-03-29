#pragma once
#include "settings.h"
#include "randomizer.h"

uint8 cardsRand(uint8 max) {
	static std::mt19937 generatorRand((int)time(0));
	std::uniform_int_distribution<short> distributionRand(0, max - 1);
	return (uint8)distributionRand(generatorRand);
}