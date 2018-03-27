#pragma once


//#define DEBUG_TIME
//#define DEBUG_RAND
//#define DEBUG_GAME
//#define DEBUG_ENDGAME
//#define DEBUG_LOGIC
#ifdef DEBUG_GAME
#define DEBUG_ENDGAME
#endif


#include <iostream>
#include <conio.h>
#include <fileManagement.h>
#include <string>
#include <cstdint>
#include <algorithm>
#include <random>


#ifdef DEBUG_TIME
#include <chrono>
using tPoint = std::chrono::high_resolution_clock::time_point;
using cl = std::chrono::high_resolution_clock;
using micros = std::chrono::microseconds;
#else
#include <time.h>
#endif

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


#define basicDeck ( 1,1,1,1,2,2,2,2,3,3,3,3,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 )


const int timeRand = (int)time(0);


constexpr uint64 printTimeEveryIterations = 10000;



#include "deck-hand.h"
#include "logic.h"
#include "randomizer.h"