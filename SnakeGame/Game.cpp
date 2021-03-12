#include "Game.h"
#include "Grid.h"


Game::Game()
	:m_window("Game Window", { 800,600 })
{}

Game::~Game()
{}

void Game::HandleInput()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		snake.ChangeDirection(Direction::Right);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		snake.ChangeDirection(Direction::Left);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		snake.ChangeDirection(Direction::Up);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		snake.ChangeDirection(Direction::Down);
	}


}

void Game::Update()
{
	m_window.Update();

	snake.Update(clock.restart().asSeconds());


}

void Game::Render()
{
	m_window.BeginDraw();  //CLEAR

	//DRAW GRID
	Grid snakeGrid(sf::Vector2f(120, 0), sf::Vector2f(600, 600), sf::Vector2f(20, 20));
	for (auto& i : snakeGrid.GetGrid())
	{
		m_window.Draw(i);
	}


	snake.Render(m_window);


	m_window.EndDraw();
}

Window* Game::GetWindow()
{
	return &m_window;
}
