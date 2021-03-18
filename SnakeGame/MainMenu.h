#pragma once
#include <SFML/Graphics.hpp>
#include "Window.h"
#include "Game.h";

class Game;

class MainMenu
{	
public:
	MainMenu();
	~MainMenu();
	void Update(Game* game, Window* window);
	void Render(Window* window);
	sf::RectangleShape GetStartButton();
	sf::RectangleShape GetQuitButton();
	void PulseTitle();


private:
	sf::Font MainMenuFont;
	sf::RectangleShape StartButton;
	sf::RectangleShape QuitButton;
	sf::RectangleShape Backgound;
	sf::Texture BackgoundText;
	sf::Text Title;
	sf::Text Start;
	sf::Text Quit;

};

