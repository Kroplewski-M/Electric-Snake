#include "Snake.h"
#include "Window.h"


Snake::Snake()
	:rectangle(snakeSegmentSize)
{
	rectangle.setFillColor(sf::Color::Red);
	//rectangle.setOutlineThickness(2);
	//rectangle.setOutlineColor(sf::Color::White);
	m_SegmentPos.emplace_back(SnakeSegment{ 160,0 });
	m_SegmentPos.emplace_back(SnakeSegment{ 140,0 });
	m_SegmentPos.emplace_back(SnakeSegment{ 120,0 });

}

Snake::~Snake()
{

}

void Snake::Update(float DT)
{
	while (clock.getElapsedTime().asMilliseconds() < 150);
	clock.restart();
	

	if (m_SegmentPos[0].x % 20 == 0 && m_SegmentPos[0].y % 20 == 0)
		m_direction = m_direction_queue;


	switch (m_direction)
	{
	case Direction::Up:
		std::reverse(m_SegmentPos.begin(), m_SegmentPos.end());
		m_SegmentPos.push_back(m_SegmentPos[m_SegmentPos.size() - 1]);
		std::reverse(m_SegmentPos.begin(), m_SegmentPos.end());
		m_SegmentPos[0].y -= 20 ;
		m_SegmentPos.pop_back();
		break;
	case Direction::Down:
		std::reverse(m_SegmentPos.begin(), m_SegmentPos.end());
		m_SegmentPos.push_back(m_SegmentPos[m_SegmentPos.size() - 1]);
		std::reverse(m_SegmentPos.begin(), m_SegmentPos.end());
		m_SegmentPos[0].y += 20 ;
		m_SegmentPos.pop_back();
		break;
	case Direction::Left:
		std::reverse(m_SegmentPos.begin(), m_SegmentPos.end());
		m_SegmentPos.push_back(m_SegmentPos[m_SegmentPos.size() - 1]);
		std::reverse(m_SegmentPos.begin(), m_SegmentPos.end());
		m_SegmentPos[0].x -= 20 ;
		m_SegmentPos.pop_back();
		break;
	case Direction::Right:
		std::reverse(m_SegmentPos.begin(), m_SegmentPos.end());
		m_SegmentPos.push_back(m_SegmentPos[m_SegmentPos.size() - 1]);
		std::reverse(m_SegmentPos.begin(), m_SegmentPos.end());
		m_SegmentPos[0].x += 20 ;
		m_SegmentPos.pop_back();
		break;
	}
	Grow();

}


void Snake::Render(Window& window)
{

	for (const auto& i: m_SegmentPos)
	{
		rectangle.setPosition(sf::Vector2f(i.x, i.y));
		window.Draw(rectangle);
	}
		
}



void Snake::Grow()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::H))
	{

		if (m_direction == Direction::Up)
		{
			m_SegmentPos.emplace_back(SnakeSegment{ m_SegmentPos[0].x  ,m_SegmentPos[0].y + 20 });
		}
		if (m_direction == Direction::Down)
		{
			m_SegmentPos.emplace_back(SnakeSegment{ m_SegmentPos[0].x,m_SegmentPos[0].y - 20});
		}
		if (m_direction == Direction::Left)
		{
			m_SegmentPos.emplace_back(SnakeSegment{ m_SegmentPos[0].x + 20 ,m_SegmentPos[0].y });
		}
		if (m_direction == Direction::Right)
		{
			m_SegmentPos.emplace_back(SnakeSegment{ m_SegmentPos[0].x - 20 ,m_SegmentPos[0].y });
		}
	}
}

void Snake::ChangeDirection(Direction newDirection)
{
	m_direction_queue = newDirection;
}

void Snake::Dead()
{
	
}

bool Snake::CheckCollision()
{

	return true;
}

std::vector<SnakeSegment> Snake::GetSegments()
{
	return m_SegmentPos;
}
