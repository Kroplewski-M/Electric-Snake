#pragma once
#include <SFML/Graphics.hpp>


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
	std::vector<SnakeSegment> GetSegments();
	Direction GetDirection();
private:
	bool isDead = false;
	sf::Clock clock;
	std::vector<SnakeSegment>m_SegmentPos;
	sf::Vector2f snakeSegmentSize{ 20,20 };
	sf::RectangleShape rectangle;
	Direction m_direction{ Direction::Right };
	Direction m_direction_queue{ Direction::none };
};



