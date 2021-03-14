#pragma once
#include "window.h"
#include <vector>
#include "Snake.h"
#include "Consumables.h"

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
	bool AppleIsColliding(Snake& m_snake, const sf::Vector2f& pos_);
	sf::Vector2f SetAppleLocation();

private:
	sf::Clock clock;
	long float DT;
	Window m_window;
	Snake snake;
	Consumables apple;

};

