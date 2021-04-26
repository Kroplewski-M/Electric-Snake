#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
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
	void BecomeElectrified(Window& window);
	void SetIsElectrified(bool electrified);
	void SetTimeStamp(int time);
	int GetCountDown();
	sf::Color GetRandomColor();
	std::vector<SnakeSegment> GetSegments();
	Direction GetDirection();
	void SetOutline(bool x);

private:
	sf::Clock ElectrifiedClock;
	sf::RectangleShape ElectricBox;
	std::vector<sf::RectangleShape>ElectricBody;
	int TimeStamp = 0;
	int score = 0;
	bool IsElectrified = false;
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

	sf::Clock GameClock;
	int CountDown = 90;
	
	int randomSpawnX;
	int randomSpawnY;


	FileHandling HighScoreFile;
};



