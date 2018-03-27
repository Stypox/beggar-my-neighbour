#include "settings.h"

int pressToReturn(int returnValue = 0) {
	std::cout << "\n\n\n";
	std::cout << "main() return value: " << returnValue << "\n";
	std::cout << "Press any key to continue...";
	while (!_kbhit()) {}
	return returnValue;
}

int main() {
	Game game1;

#ifdef DEBUG_TIME
	tPoint tStart = clk::now();
	uint64 nrIterations = 1;
#endif
	while (1) {
		game1.resetOriginal();
		game1.mutateRandom();
		game1.play();

	#ifdef DEBUG_TIME
		if (nrIterations % printTimeEveryIterations == 0) {
			tPoint tNow = clk::now();
			std::cout << std::chrono::duration_cast<micros>(tNow - tStart).count() / nrIterations << "\n";
		}
		++nrIterations;
	#endif

	}

	return pressToReturn();
}