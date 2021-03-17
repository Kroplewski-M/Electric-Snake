#include "Scenemanager.h"

Scenemanager::Scenemanager()
	:game(), menu(),MainMenuMusic("MainMenuMusic.wav")
{
	MainMenuMusic.PlaySound();
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
			menu.Update(&game,game.GetWindow());
			menu.Render(game.GetWindow());
			ChangeScene();
			break;
		case GameStates::Game:
			MainMenuMusic.SetVolume(5);
			game.HandleInput();
			game.Update();
			game.Render();
			ChangeScene();
			break;
		case GameStates::GameOver:
			break;
		case GameStates::QuitGame:
			game.GetWindow()->SetIsDone(true);
		default:
			break;
		}
	}
}

void Scenemanager::ChangeScene()
{


	if (myStates == GameStates::MainMenu)
	{
		if (game.GetWindow()->getMouseLocation().x > menu.GetStartButton().getPosition().x 
			&& game.GetWindow()->getMouseLocation().x < menu.GetStartButton().getPosition().x + menu.GetStartButton().getSize().x &&
			game.GetWindow()->getMouseLocation().y > menu.GetStartButton().getPosition().y 
			&& game.GetWindow()->getMouseLocation().y < menu.GetStartButton().getPosition().y + menu.GetStartButton().getSize().y)
		{
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
			{
				myStates = GameStates::Game;
			}

		}
	}
	if (myStates == GameStates::MainMenu)
	{
		if (game.GetWindow()->getMouseLocation().x > menu.GetQuitButton().getPosition().x && game.GetWindow()->getMouseLocation().x < menu.GetQuitButton().getPosition().x + menu.GetQuitButton().getSize().x &&
			game.GetWindow()->getMouseLocation().y > menu.GetQuitButton().getPosition().y && game.GetWindow()->getMouseLocation().y < menu.GetQuitButton().getPosition().y + menu.GetQuitButton().getSize().y)
		{
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
			{
				myStates = GameStates::QuitGame;
			}

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

