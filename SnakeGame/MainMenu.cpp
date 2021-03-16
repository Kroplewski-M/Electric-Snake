#include "MainMenu.h"
#include <iostream>

MainMenu::MainMenu()
{
	if (!font.loadFromFile("SnakeFont.otf"))
	{
		std::cout << "font not loaded";
	}
	StartButton.setSize({100,50});
	StartButton.setPosition({ 350,200 });
	StartButton.setFillColor(sf::Color::Red);
	
}

MainMenu::~MainMenu()
{

}

void MainMenu::Update(Window* window)
{
	
	window->Update();
}

void MainMenu::Render(Window* window)
{
	window->BeginDraw();

	

	window->Draw(StartButton);
	window->EndDraw();

}

sf::RectangleShape MainMenu::GetStartButton()
{
	return StartButton;
}

