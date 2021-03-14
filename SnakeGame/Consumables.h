#pragma once
#include <SFML/Graphics.hpp>



class Window;
class Grid;
class Snake;

class Consumables
{
public:
	Consumables();
	~Consumables();
	void Update();
	void Render(Window& m_window);
	void Destroy();
	void SetIsAlive(bool isAlive);
	bool GetIsAlive();
	void ToggleIsDead();
	sf::Vector2f GetLocation();
	sf::Vector2f SetSpawnLocation(sf::Vector2f loc);
private:
	sf::CircleShape consumable;
	sf::Vector2f m_pos;
	bool m_isAlive = true;

};

