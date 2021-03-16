#include "Scenemanager.h"

Scenemanager::Scenemanager()
	:game(), menu()
{

}

Scenemanager::~Scenemanager()
{

}

void Scenemanager::Update()
{
	switch (myStates)
	{
	case GameStates::MainMenu:
		while (!game.GetWindow()->isDone())
		{
			menu.Update(game.GetWindow());
			menu.Render(game.GetWindow());
			ChangeScene();
		}
		break;
	case GameStates::Game:

		while (!game.GetWindow()->isDone())
		{
			//GAME LOOP
			ChangeScene();
			game.HandleInput();
			game.Update();
			game.Render();

		}
		break;
	case GameStates::GameOver:
		break;
	default:
		break;
	}
	
}

void Scenemanager::ChangeScene()
{
	
	if (myStates == GameStates::MainMenu)
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
		{
			myStates = GameStates::Game;
		}
	}
	
}

Game* Scenemanager::GetGame()
{
	return &game;
}

