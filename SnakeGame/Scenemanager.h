#pragma once
#include "Game.h"
#include "MainMenu.h";

enum class GameStates
{
	MainMenu,
	Game,
	GameOver
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
	
};

