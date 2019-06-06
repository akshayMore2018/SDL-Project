#include "SDL.h"
#include "Game.h"
int main(int argc, char** argv)
{
	Game game;

	bool success = game.initialize();

	if (success)
	{
		game.run();
	}

	game.stop();

	return 0;
}