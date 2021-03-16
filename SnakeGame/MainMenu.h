#pragma once
#include <SFML/Graphics.hpp>
#include "Window.h"




class MainMenu
{	
public:
	MainMenu();
	~MainMenu();
	void Update(Window* window);
	void Render(Window* window);
	sf::RectangleShape GetButton(int i);
private:
	const static int numberOfButtons = 2;
	sf::Font font;
	sf::RectangleShape button;
	std::vector<sf::RectangleShape>buttons;
};

