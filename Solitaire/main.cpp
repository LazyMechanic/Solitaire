#include <ctime>

#include "game.h"
#include <iostream>

int main(int argc, char** argv)
{
	srand(time(0));
	// Set starting parameters
	if (argc > 1) {
		Config::playerName = std::string(argv[1]);
		Config::playerScore = std::atoi(argv[2]);
		Timer::SetConstTimer(std::atoi(argv[3]) * 1000);
	}
	else {
		return 1;
	}
	// Main cycle
	Game game;
	if (game.Init()) {
		game.Run();
	}

	return 0;
}