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
	game1.play();
	std::cout << game1;

	return pressToReturn();
}