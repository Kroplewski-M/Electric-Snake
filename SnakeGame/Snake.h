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
	void Update(float DT);
	void Render(Window& window);
	void Grow(std::vector<Snake*>& m_snakeVector);
	void ChangeDirection(Direction newDirection);
	std::vector<SnakeSegment> GetSegments();
private:
	std::vector<SnakeSegment>m_SegmentPos;
	sf::Vector2f snakeSegmentSize{ 20,20 };
	Direction m_direction{ Direction::Right };
	Direction m_direction_queue{ Direction::none };
};



