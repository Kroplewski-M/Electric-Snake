#include "Consumables.h"
#include "Window.h"
#include "Snake.h"

bool IsColliding(Snake& m_snake, const sf::Vector2f& pos_)
{
	for(const SnakeSegment& seg_ : m_snake.GetSegments())
	{
		if (sf::Vector2f(seg_.x, seg_.y) == pos_)
			return true;
	}
	return false;
}

Consumables::Consumables(Snake& snake)
{
	float randX, randY;
	do{
		randX = 120 + (((rand() % 601) % 20) * 20);
		randY = (((rand() % 601) % 20) * 20);
	} while (IsColliding(snake, sf::Vector2f(randX, randY)));
	m_pos = {randX, randY};
}

Consumables::~Consumables()
{

}

void Consumables::Update(Snake& snake)
{
	// if dead and time delay finished
	if (!m_isAlive)
	{
		float randX, randY;
	do{
		randX = 120 + (((rand() % 601) % 20) * 20);
		randY = (((rand() % 601) % 20) * 20);
	} while (IsColliding(snake, sf::Vector2f(randX, randY)));
	
	m_pos = {  randX, randY  };
	m_isAlive = true;
	}
	//reset time delay using rand
	
}

void Consumables::Render(Window& window)
{
	if (m_isAlive)
	{
		sf::CircleShape x(10);
		x.setFillColor(sf::Color::Green);
		x.setPosition(m_pos);
		window.Draw(x);
	}
}

void Consumables::Destroy()
{
	m_isAlive = false;
}

void Consumables::SetIsAlive(bool isAlive)
{
	m_isAlive = isAlive;
}



sf::Vector2f Consumables::GetLocation()
{
	return m_pos;
}


