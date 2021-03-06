#include "Consumables.h"
#include "Window.h"
#include "Snake.h"



Consumables::Consumables()
{
	consumable.setSize({ 20,20 });
}

Consumables::~Consumables()
{

}

void Consumables::Update()
{
	consumable.setPosition(m_pos);
	
}

void Consumables::Render(Window& window)
{
	if (m_isAlive)
	{	
		window.Draw(consumable);
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

void Consumables::SetTexture(sf::Texture& tex)
{
	consumable.setTexture(&tex);
}

