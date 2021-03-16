#include <SFML/Graphics.hpp>
#include "Game.h"
#include "Scenemanager.h"

int main()
{
	srand((time(0u)));
	
	Scenemanager myScenes;

	while (!myScenes.GetGame()->GetWindow()->isDone())
	{
		myScenes.Update();
		//myScenes.ChangeScene();

	}



	//Game game;


	//while (!game.GetWindow()->isDone())
	//{
	//	//GAME LOOP
	//	game.HandleInput();
	//	game.Update();
	//	game.Render();

	//}

	return 0;
}
