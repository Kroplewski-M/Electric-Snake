#include <SFML/Graphics.hpp>
#include "Game.h"



int main()
{
	srand((time(0u)));
	Game game;
	while (!game.GetWindow()->isDone())
	{
		//GAME LOOP
		game.HandleInput();
		game.Update();
		game.Render();

	}

	return 0;
}