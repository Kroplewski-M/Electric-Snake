#pragma once
#include "window.h"
#include <vector>
#include "Snake.h"
#include "Consumables.h"
#include "Apple.h"
#include "texture.h"
#include "MainMenu.h"
#include "Battery.h"

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
	bool ConsumableIsColliding(Snake& m_snake, const sf::Vector2f& pos_);
	sf::Vector2f SetAppleLocation();
	sf::Vector2f SetBatteryLocation();
	void SnakeEats();
	void DrawGrid();
	void MoveSnake();
	void CheckHighScore(int x);
	void BatteryLocationTimer();
	void SetAllAppleLocation();
private:

	sf::Font ScoreFont;
	sf::Text ScoreText;
	sf::Text HighScoreText;
	sf::Text Tips;

	bool SpawnBattery = false;
	int once = 0;
	sf::Clock BatteryClock;

	
	sf::Text CountDownText;
	sf::CircleShape CountDownCircle;
	sf::Texture CountDownTexture;

	Window m_window;

	Snake snake;


	Apple apple;
	std::vector<Apple>AllApples;
	Battery battery;
	texture GameBackground;
	Sound SnakeEatSound;
	Sound SnakeElectrifiedSound;
	sf::Texture AppleTex;
	sf::Texture BatteryTex;
	
};

