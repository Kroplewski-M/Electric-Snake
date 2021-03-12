#include <SFML/Graphics.hpp>
#include "Game.h"



int main()
{
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