#pragma once
#include <SFML/Graphics.hpp>



class Window;

class Consumables
{
public:
	Consumables();
	~Consumables();
	void Update();
	void Render(Window* m_window);
	void Destroy();
	void Spawn();
private:
	sf::Vector2f m_pos;

};

