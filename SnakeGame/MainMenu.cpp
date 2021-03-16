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

	QuitButton.setSize({ 100,50 });
	QuitButton.setPosition({ 350,300 });
	QuitButton.setFillColor(sf::Color::Red);
	
}

MainMenu::~MainMenu()
{

}

void MainMenu::Update(Game* game, Window* window)
{
	if (game->GetWindow()->getMouseLocation().x > StartButton.getPosition().x && game->GetWindow()->getMouseLocation().x < StartButton.getPosition().x + StartButton.getSize().x &&
		game->GetWindow()->getMouseLocation().y > StartButton.getPosition().y && game->GetWindow()->getMouseLocation().y < StartButton.getPosition().y + StartButton.getSize().y)
	{
		StartButton.setOutlineThickness(1);
		StartButton.setOutlineColor(sf::Color::White);

	}
	else
	{
		StartButton.setOutlineThickness(0);
	}

	if (game->GetWindow()->getMouseLocation().x > QuitButton.getPosition().x && game->GetWindow()->getMouseLocation().x < QuitButton.getPosition().x + QuitButton.getSize().x &&
		game->GetWindow()->getMouseLocation().y > QuitButton.getPosition().y && game->GetWindow()->getMouseLocation().y < QuitButton.getPosition().y + QuitButton.getSize().y)
	{
		QuitButton.setOutlineThickness(1);
		QuitButton.setOutlineColor(sf::Color::White);

	}
	else
	{
		QuitButton.setOutlineThickness(0);
	}


	window->Update();
}

void MainMenu::Render(Window* window)
{
	window->BeginDraw();

	
	window->Draw(QuitButton);
	window->Draw(StartButton);
	window->EndDraw();

}

sf::RectangleShape MainMenu::GetStartButton()
{
	return StartButton;
}

sf::RectangleShape MainMenu::GetQuitButton()
{
	return QuitButton;
}

