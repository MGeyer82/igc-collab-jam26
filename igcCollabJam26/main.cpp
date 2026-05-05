#include "Game.h"

int main()
{
	Game game;

	while (game.getRunStatus())
	{
		game.update();
		game.render();
	}

	return 0;
}