#include "Snake.h"
#include "Window.h"


Snake::Snake()
{
	m_SegmentPos.emplace_back(SnakeSegment{ 120,0 });

}

Snake::~Snake()
{

}

void Snake::Update(float DT)
{
	DT = DT * 3;

	if (m_SegmentPos[0].x % 20 == 0 && m_SegmentPos[0].y % 20 == 0)
		m_direction = m_direction_queue;


	switch (m_direction)
	{
	case Direction::Up:
		m_SegmentPos[0].y -= snakeSegmentSize.y * DT;
		break;
	case Direction::Down:
		m_SegmentPos[0].y += (1 + (snakeSegmentSize.y * DT));
		break;
	case Direction::Left:
		m_SegmentPos[0].x -= snakeSegmentSize.x * DT;
		break;
	case Direction::Right:
		m_SegmentPos[0].x += (1 + (snakeSegmentSize.x * DT));
		break;
	}

}


void Snake::Render(Window& window)
{
	sf::RectangleShape rectangle(snakeSegmentSize);
	rectangle.setPosition(sf::Vector2f(m_SegmentPos[0].x, m_SegmentPos[0].y));
	rectangle.setFillColor(sf::Color::Red);

	window.Draw(rectangle);
}



void Snake::Grow(std::vector<Snake*>& m_snakeVector)
{

}

void Snake::ChangeDirection(Direction newDirection)
{
	m_direction_queue = newDirection;
}

std::vector<SnakeSegment> Snake::GetSegments()
{
	return m_SegmentPos;
}
