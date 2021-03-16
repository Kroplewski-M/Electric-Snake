#include "Game.h"
#include "Grid.h"


Game::Game()
	:m_window("Electric Snake", { 800,600 }),GameBackground(800,600,"Snake Background.png")
{
	apple.SetSpawnLocation(SetConsumableLocation());
	if (!ScoreFont.loadFromFile("SnakeFont.otf"))
	{
		printf("failed to load snake font");
	}
	ScoreText.setFont(ScoreFont);
	ScoreText.setPosition(sf::Vector2f(600, 10));
}

Game::~Game()
{}

void Game::HandleInput()
{
	MoveSnake();

}

void Game::Update()
{
	m_window.Update();

	snake.Update();

	SnakeEats();

	apple.Update();
	
}

void Game::Render()
{
	m_window.BeginDraw();  //CLEAR

	GameBackground.Render(m_window);
	//DRAW GRID
	DrawGrid();


	apple.Render(m_window);
	snake.Render(m_window);

	ScoreText.setString("Score: " + std::to_string(snake.GetScore()));
	m_window.Draw(ScoreText);
	m_window.EndDraw();
}

Window* Game::GetWindow()
{
	return &m_window;
}

bool Game::ConsumableIsColliding(Snake& m_snake, const sf::Vector2f& pos_)
{
	for (const SnakeSegment& seg_ : m_snake.GetSegments())
	{
		if (sf::Vector2f(seg_.x, seg_.y) == pos_)
			return true;
	}
	return false;
}

sf::Vector2f Game::SetConsumableLocation()
{
	float randX, randY;
	do {
		randX = 120 + (((rand() % 601) % 20) * 20);
		randY = (((rand() % 601) % 20) * 20);
	} while (ConsumableIsColliding(snake, sf::Vector2f(randX, randY)));
	apple.SetSpawnLocation({ randX, randY }) ;

	return apple.GetLocation();
}

void Game::SnakeEats()
{

	if (snake.getIsDead() == false)
	{
		if (snake.GetSegments().front().x == apple.GetLocation().x && snake.GetSegments().front().y == apple.GetLocation().y)
		{
			snake.Grow();
			apple.SetSpawnLocation(SetConsumableLocation());
		}
	}
}

void Game::DrawGrid()
{
	Grid snakeGrid(sf::Vector2f(120, 0), sf::Vector2f(600, 600), sf::Vector2f(20, 20));
	for (auto& i : snakeGrid.GetGrid())
	{
		m_window.Draw(i);
	}

}

void Game::MoveSnake()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		if (snake.GetDirection() != Direction::Left)
		{
			snake.ChangeDirection(Direction::Right);
		}
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		if (snake.GetDirection() != Direction::Right)
		{
			snake.ChangeDirection(Direction::Left);
		}
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		if (snake.GetDirection() != Direction::Down)
		{
			snake.ChangeDirection(Direction::Up);
		}
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		if (snake.GetDirection() != Direction::Up)
		{
			snake.ChangeDirection(Direction::Down);
		}
	}
}

