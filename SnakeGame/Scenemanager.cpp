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
	while (!game.GetWindow()->isDone())
	{
		switch (myStates)
		{
		case GameStates::MainMenu:
			
				menu.Update(game.GetWindow());
				menu.Render(game.GetWindow());
				ChangeScene();
			break;
		case GameStates::Game:
				//GAME LOOP
				game.HandleInput();
				game.Update();
				game.Render();
				ChangeScene();
			break;
		case GameStates::GameOver:
			break;
		default:
			break;
		}
	}
}

void Scenemanager::ChangeScene()
{
	if (myStates == GameStates::MainMenu)
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num1))
		{
			game.GetWindow()->SetIsDone(true);
		}
	}
	if (myStates == GameStates::MainMenu)
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
		{

			myStates = GameStates::Game;
		}
	}
	if (myStates == GameStates::Game)
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
		{
			myStates = GameStates::MainMenu;
		}
	}

}

Game* Scenemanager::GetGame()
{
	return &game;
}

