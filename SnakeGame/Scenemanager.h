#pragma once
#include "Game.h"
#include "MainMenu.h";
#include "Music.h"

enum class GameStates
{
	MainMenu,
	Game,
	GameOver,
	QuitGame
};

class Scenemanager
{
public:
	Scenemanager();
	~Scenemanager();
	void Update();
	void ChangeScene();
	Game *GetGame();
	
private:
	GameStates myStates = GameStates::MainMenu;
	Game game;
	MainMenu menu;
	Music MainMenuMusic;
	
};

