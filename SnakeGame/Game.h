#pragma once
#include "window.h"
#include <vector>
#include "Snake.h"
#include "Consumables.h"
#include "Apple.h"
#include "texture.h"
#include "MainMenu.h"

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
	sf::Vector2f SetConsumableLocation();
	void SnakeEats();
	void DrawGrid();
	void MoveSnake();

private:

	sf::Font ScoreFont;
	sf::Text ScoreText;
	sf::Clock clock;
	long float DT;
	Window m_window;
	Snake snake;
	Apple apple;
	texture GameBackground;
};

