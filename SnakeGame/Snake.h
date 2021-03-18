#pragma once
#include <SFML/Graphics.hpp>
#include "Sound.h"
#include "FileHandling.h"

class Window;

struct SnakeSegment
{
	int x, y;
};


enum class Direction
{
	Up,
	Down,
	Left,
	Right,
	none
};


class Snake
{
public:
	Snake();
	~Snake();
	void Update();
	void Render(Window& window);
	void Grow();
	void ChangeDirection(Direction newDirection);
	void Dead();
	bool CheckCollision();
	bool getIsDead();
	void Respawn();
	int GetScore();
	int GetHighScore();
	void SetHighScore(int x);
	std::vector<SnakeSegment> GetSegments();
	Direction GetDirection();



private:
	int score = 0;
	int highScore = 0;
	bool isDead = false;
	sf::Clock clock;
	std::vector<SnakeSegment>m_SegmentPos;
	sf::Vector2f snakeSegmentSize{ 20,20 };
	sf::RectangleShape rectangle;
	Direction m_direction{ Direction::Right };
	Direction m_direction_queue{ Direction::none };
	Sound GameOver;

	sf::Texture* snakeBodyRight = new sf::Texture;
	sf::Texture* snakeTailRight = new sf::Texture;
	sf::Texture* snakeHeadRight = new sf::Texture;


	FileHandling HighScoreFile;
};



