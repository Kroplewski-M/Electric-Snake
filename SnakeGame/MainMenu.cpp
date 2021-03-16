#include "MainMenu.h"
#include <iostream>

MainMenu::MainMenu()
{
	if (!font.loadFromFile("SnakeFont.otf"))
	{
		std::cout << "font not loaded";
	}
	button.setSize({200,100});
	button.setPosition({ 290,200 });
	button.setFillColor(sf::Color::Red);
	buttons.push_back(button);
	
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
	window->Draw(buttons[0]);
	window->EndDraw();

}

sf::RectangleShape MainMenu::GetButton(int i)
{
	return buttons[i];
}
