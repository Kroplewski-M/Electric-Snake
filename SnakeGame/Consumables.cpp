#include "Consumables.h"
#include "Window.h"
#include "Snake.h"



Consumables::Consumables()
{
}

Consumables::~Consumables()
{

}

void Consumables::Update()
{
		
	
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



bool Consumables::GetIsAlive()
{
	return m_isAlive;
}

void Consumables::ToggleIsDead()
{
	m_isAlive = -m_isAlive;
}

sf::Vector2f Consumables::GetLocation()
{
	return m_pos;
}

sf::Vector2f Consumables::SetSpawnLocation(sf::Vector2f loc)
{
	m_pos = loc;
	return m_pos;
}

