#include "MainMenu.h"
#include <iostream>

MainMenu::MainMenu()
{
	//LOADS NESSESSARY FILES 
	if (!MainMenuFont.loadFromFile("MainMenuFont.otf"))
	{
	}

	if (!BackgoundText.loadFromFile("SnakeMainMenu.png"));
	{
	}
	//SETS ALL BUTTONS AND TEXT
	StartButton.setSize({100,50});
	StartButton.setPosition({ 350,200 });
	StartButton.setFillColor(sf::Color::Red);

	QuitButton.setSize({ 100,50 });
	QuitButton.setPosition({ 350,300 });
	QuitButton.setFillColor(sf::Color::Red);
	

	Backgound.setSize({ 800,600 });
	Backgound.setPosition({ 0,0 });
	Backgound.setTexture(&BackgoundText);

	Title.setFont(MainMenuFont);
	Title.setPosition({ 160, 100 });
	Title.setColor(sf::Color({255, 140, 0 , 255}));
	Title.setCharacterSize(60);
	Title.setString("ELECTRIC SNAKE");

	Start.setFont(MainMenuFont);
	Start.setPosition(StartButton.getPosition());
	Start.setColor(sf::Color::White);
	Start.setCharacterSize(35);
	Start.setString("Start");


	Quit.setFont(MainMenuFont);
	Quit.setPosition(sf::Vector2f(QuitButton.getPosition().x + 12, QuitButton.getPosition().y));
	Quit.setColor(sf::Color::White);
	Quit.setCharacterSize(35);
	Quit.setString("Quit");

	
}

MainMenu::~MainMenu()
{

}

void MainMenu::Update(Game* game, Window* window)
{
	//HIGHLIGHTS BUTTON IF MOUSE IS OVER IT
	if (game->GetWindow()->getMouseLocation().x > StartButton.getPosition().x && game->GetWindow()->getMouseLocation().x < StartButton.getPosition().x + StartButton.getSize().x &&
		game->GetWindow()->getMouseLocation().y > StartButton.getPosition().y && game->GetWindow()->getMouseLocation().y < StartButton.getPosition().y + StartButton.getSize().y)
	{
		StartButton.setOutlineThickness(2);
		StartButton.setOutlineColor(sf::Color::White);

	}
	else
	{
		StartButton.setOutlineThickness(0);
	}

	if (game->GetWindow()->getMouseLocation().x > QuitButton.getPosition().x && game->GetWindow()->getMouseLocation().x < QuitButton.getPosition().x + QuitButton.getSize().x &&
		game->GetWindow()->getMouseLocation().y > QuitButton.getPosition().y && game->GetWindow()->getMouseLocation().y < QuitButton.getPosition().y + QuitButton.getSize().y)
	{
		QuitButton.setOutlineThickness(2);
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
	//RENDER THE MAIN MENU
	window->BeginDraw();
	window->Draw(Backgound);
	window->Draw(Title);
	window->Draw(QuitButton);
	window->Draw(StartButton);
	window->Draw(Start);
	window->Draw(Quit);

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

void MainMenu::PulseTitle()
{
	
}


