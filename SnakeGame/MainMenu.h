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
	sf::RectangleShape GetStartButton();
private:
	sf::Font font;
	sf::RectangleShape StartButton;

};

