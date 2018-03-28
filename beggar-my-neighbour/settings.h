#pragma once


#define DEBUG_TIME
//#define DEBUG_RAND
//#define DEBUG_GAME
//#define DEBUG_BEGEND
//#define DEBUG_LOGIC
#define DEBUG_EVOLUTION

#ifdef DEBUG_GAME
#define DEBUG_BEGEND
#endif


#ifdef DEBUG_TIME
#include <chrono>
using tPoint = std::chrono::high_resolution_clock::time_point;
using clk = std::chrono::high_resolution_clock;
using micros = std::chrono::microseconds;
#else
#include <time.h>
#endif


#include <iostream>
#include <conio.h>
#include <fileManagement.h>
#include <string>
#include <cstdint>
#include <algorithm>
#include <random>


using int8 = int8_t;
using int16 = int16_t;
using int32 = int32_t;
using int64 = int64_t;
using uint8 = uint8_t;
using uint16 = uint16_t;
using uint32 = uint32_t;
using uint64 = uint64_t;


constexpr const char * inputFilePath = "input.txt";
constexpr const char * outputFilePath = "output.txt";


constexpr uint8
nrCards = 52,
halfCards = 26,

empty = 255,
one = 1,
two = 2,
three = 3,
four = 4,

nrOne = 4,
nrTwo = 4,
nrThree = 4,
nrFour = 4;

constexpr bool 
turnA = 1,
turnB = 0;

#define basicDeck { 1,1,1,1,2,2,2,2,3,3,3,3,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 }


constexpr uint8
nrGames = 200,
survivingGames = 98,
randGames = nrGames - (survivingGames * 2);

#define basicOrder { 0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,51,52,53,54,55,56,57,58,59,60,61,62,63,64,65,66,67,68,69,70,71,72,73,74,75,76,77,78,79,80,81,82,83,84,85,86,87,88,89,90,91,92,93,94,95,96,97,98,99,100,101,102,103,104,105,106,107,108,109,110,111,112,113,114,115,116,117,118,119,120,121,122,123,124,125,126,127,128,129,130,131,132,133,134,135,136,137,138,139,140,141,142,143,144,145,146,147,148,149,150,151,152,153,154,155,156,157,158,159,160,161,162,163,164,165,166,167,168,169,170,171,172,173,174,175,176,177,178,179,180,181,182,183,184,185,186,187,188,189,190,191,192,193,194,195,196,197,198,199}


#ifdef DEBUG_TIME
constexpr uint64 printTimeEveryIterations = 10000;
#endif




#include "deck-hand.h"
#include "logic.h"
#include "randomizer.h"