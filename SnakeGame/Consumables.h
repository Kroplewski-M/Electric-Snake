#pragma once
#include <SFML/Graphics.hpp>



class Window;
class Grid;
class Snake;

class Consumables
{
public:
	Consumables(Snake& snake);
	~Consumables();
	void Update(Snake& snake);
	void Render(Window& m_window);
	void Destroy();
	void SetIsAlive(bool isAlive);
	sf::Vector2f GetLocation();
private:
	sf::Vector2f m_pos;
	bool m_isAlive = true;

};

