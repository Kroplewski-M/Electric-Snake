#pragma once
#include "window.h"
#include <vector>
#include <cmath>
#include "Consumables.h"
#include "Apple.h"
#include "texture.h"
#include "MainMenu.h"
#include "Battery.h"
#include "AISnake.h"

class Snake;

class Game
{
public:
	Game();
	~Game();

	void HandleInput();
	void Update();
	void Render();
	Window* GetWindow();
	bool ConsumableIsColliding(Snake* m_snake, const sf::Vector2f& pos_);
	sf::Vector2f SetAppleLocation();
	sf::Vector2f SetBatteryLocation();
	void SnakeEats();
	void DrawGrid();
	void MoveSnake();
	void CheckHighScore(int x);
	void BatteryLocationTimer();
	void SetAllAppleLocation();
	void MoveAI(AISnake* AI);
	sf::Vector2f GetClosestApple(sf::Vector2f AISnakeLoc, std::vector<Apple>&AllApples);
	void CheckAllSnakeCollision();
	void RespawnAll();
	bool CheckAllDead();
	void GameOverScreen();
	void FindWinner();
	void SetAllDirection();

private:

	sf::Font ScoreFont;
	sf::Text ScoreText;
	sf::Text HighScoreText;
	sf::Text Tips;

	sf::Text AI1Score;
	sf::Text AI2Score;
	sf::Text AI3Score;
	sf::Text AI4Score;
	sf::Text AI5Score;


	bool SpawnBattery = false;
	int once = 0;
	sf::Clock BatteryClock;

	
	sf::Text CountDownText;
	sf::CircleShape CountDownCircle;
	sf::Texture CountDownTexture;

	Window m_window;

	Snake snake;
	AISnake* AI1 = new AISnake;
	AISnake* AI2 = new AISnake;
	AISnake* AI3 = new AISnake;
	AISnake* AI4 = new AISnake;
	AISnake* AI5 = new AISnake;


	std::vector<AISnake*>AISnakes;
	sf::Vector2f* ClosestAppleLocation = new sf::Vector2f;
	


	Apple apple;
	std::vector<Apple>AllApples;
	Battery battery;
	texture GameBackground;
	Sound SnakeEatSound;
	Sound SnakeElectrifiedSound;
	sf::Texture AppleTex;
	sf::Texture BatteryTex;

	sf::Text GameOverText;
	sf::Text WinnerText;
	sf::Text WinningPlayer;
	sf::Text PlayAgainText;
	sf::Text QuitText;
	sf::RectangleShape RestartButton;
	sf::RectangleShape QuitButton;
	
	int TopScore = 0;
	std::string Winner;

	bool GameIsFinished = false;
};

