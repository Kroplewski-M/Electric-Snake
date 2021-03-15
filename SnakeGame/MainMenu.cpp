#include "MainMenu.h"
#include <iostream>

MainMenu::MainMenu()
{
	if (!font.loadFromFile("SnakeFont.otf"))
	{
		std::cout << "font not loaded";
	}

	
}

MainMenu::~MainMenu()
{

}
