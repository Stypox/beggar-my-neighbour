#include "settings.h"

int pressToReturn(int returnValue = 0) {
	std::cout << "\n\n\n";
	std::cout << "main() return value: " << returnValue << "\n";
	std::cout << "Press any key to continue...";
	while (!_kbhit()) {}
	return returnValue;
}

int main() {
	Evolution ev;
	ev.test();
	ev.sort();

#ifdef DEBUG_TIME
	tPoint tStart = clk::now();
	uint64 nrIterations = 1;
#endif

	while (1) {
	ev.evolve();
	ev.test();
	ev.sort();

	#ifdef DEBUG_TIME
		if (nrIterations % printTimeEveryIterations == 0) {
			tPoint tNow = clk::now();
		#ifdef DEBUG_EVOLUTION_RESULT
		#ifndef DEBUG_EVOLUTION_LOGIC
			std::cout << ev.getBestResult() << " | ";
		#endif
		#endif
			std::cout << std::chrono::duration_cast<micros>(tNow - tStart).count() / nrIterations << "\n";
		}
		++nrIterations;
	#endif
	}

	return pressToReturn();
}