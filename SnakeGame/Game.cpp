#include "Game.h"
#include "Grid.h"


Game::Game()
	:m_window("Electric Snake", { 800,600 }), GameBackground(800, 600, "Snake Background.png"), SnakeEatSound("SnakeEats.wav"), SnakeElectrifiedSound("BatterySound.wav")
{
	if (!CountDownTexture.loadFromFile("CountDownClock.jpg"))
	{
		printf("CountDownClockTexture not loaded");
	}
	CountDownTexture.setSmooth(true);

	if (!AppleTex.loadFromFile("AppleTex.png"))
	{
		printf("AppleTex not loaded");
	}
	apple.SetTexture(AppleTex);
	AppleTex.setSmooth(true);

	if (!BatteryTex.loadFromFile("batteryTex.png"))
	{
		printf("batteryTex not loaded");
	}
	battery.SetTexture(BatteryTex);


	if (!ScoreFont.loadFromFile("SnakeFont.otf"))
	{
		printf("failed to load snake font");
	}

	AllApples.push_back(apple);
	AllApples.push_back(apple);
	AllApples.push_back(apple);
	AllApples.push_back(apple);
	AllApples.push_back(apple);

	SetAllAppleLocation();



	ScoreText.setFont(ScoreFont);
	ScoreText.setCharacterSize(25);
	ScoreText.setPosition(sf::Vector2f(2, 10));

	HighScoreText.setFont(ScoreFont);
	HighScoreText.setCharacterSize(25);
	HighScoreText.setPosition({ 2,70 });

	Tips.setFont(ScoreFont);
	Tips.setCharacterSize(25);
	Tips.setPosition(600, 10);
	Tips.setString("Tips: \n\n -Arrows: Move snake \n\n -Eat Apple to grow \n\n -Eat battery to \n be electrified ");

	CountDownText.setFont(ScoreFont);
	CountDownText.setColor(sf::Color::Red);
	CountDownText.setCharacterSize(30);
	CountDownText.setPosition(40, 500);

	CountDownCircle.setRadius(50);
	CountDownCircle.setPosition(10, 465);
	CountDownCircle.setTexture(&CountDownTexture);

	
	AISnakes.emplace_back(AI1);
	AISnakes.emplace_back(AI2);
	AISnakes.emplace_back(AI3);
	AISnakes.emplace_back(AI4);
	AISnakes.emplace_back(AI5);

	

	snake.SetOutline(true);

}

Game::~Game()
{
	
}

void Game::HandleInput()
{
	MoveSnake();

}

void Game::Update()
{
	m_window.Update();

	snake.Update();


	for (auto& i : AISnakes)
	{
		if (i->getIsDead() == false)
		{
			GetClosestApple(sf::Vector2f(i->GetSegments().front().x, AISnakes[0]->GetSegments().front().y), AllApples);
			i->Update();
			MoveAI(i);
		}
	}
	CheckAllSnakeCollision();

	SnakeEats();

	for (auto& i: AllApples)
	{
		i.Update();
	}

	battery.Update();
	

	
}

void Game::Render()
{
	m_window.BeginDraw();  //CLEAR
	GameBackground.Render(m_window);
	//DRAW GRID
	DrawGrid();

	for (auto& i : AllApples)
	{
		i.Render(m_window);
	}

	if (BatteryClock.getElapsedTime().asSeconds() >= 10)
	{
		battery.Render(m_window);
		SpawnBattery = true;
	}
	if (snake.getIsDead() == false)
		snake.Render(m_window);


	for (auto& i : AISnakes)
	{
		if (i->getIsDead() == false)
				i->Render(m_window);
	}


	HighScoreText.setString("HighScore: \n" + std::to_string(snake.GetHighScore()));
	ScoreText.setString("Score: " + std::to_string(snake.GetScore()));
	CheckHighScore(snake.GetScore());
	CountDownText.setString( std::to_string(snake.GetCountDown()));

	m_window.Draw(CountDownCircle);
	m_window.Draw(CountDownText);
	m_window.Draw(HighScoreText);
	m_window.Draw(ScoreText);
	m_window.Draw(Tips);
	m_window.EndDraw();
}

Window* Game::GetWindow()
{
	return &m_window;
}

bool Game::ConsumableIsColliding(Snake* m_snake, const sf::Vector2f& pos_)
{
	
	for (const SnakeSegment& seg_ : m_snake->GetSegments())
	{
		if (sf::Vector2f(seg_.x, seg_.y) == pos_)
			return true;
	}
	return false;
}

sf::Vector2f Game::SetAppleLocation()
{
	float randX, randY;
		do {
			randX = 120 + (((rand() % 601) % 20) * 20);
			randY = (((rand() % 601) % 20) * 20);
		} while (ConsumableIsColliding(&snake, sf::Vector2f(randX, randY)));

		for (const auto& AIsna : AISnakes)
		{
			do {
				randX = 120 + (((rand() % 601) % 20) * 20);
				randY = (((rand() % 601) % 20) * 20);
			} while (ConsumableIsColliding(AIsna, sf::Vector2f(randX, randY)));
		}


		apple.SetSpawnLocation({ randX, randY });

	return apple.GetLocation();
}
sf::Vector2f Game::SetBatteryLocation()
{
	float randX, randY;
	do {
		randX = 120 + (((rand() % 601) % 20) * 20);
		randY = (((rand() % 601) % 20) * 20);
	} while (ConsumableIsColliding(&snake, sf::Vector2f(randX, randY)));
	battery.SetSpawnLocation({ randX, randY });

	return battery.GetLocation();
}
void Game::SnakeEats()
{

	if (BatteryClock.getElapsedTime().asSeconds() >= 10 && once == 0)
	{
		battery.SetSpawnLocation(SetBatteryLocation());
		once++;
	}

	if (snake.getIsDead() == false)
	{
		for (auto& i: AllApples)
		{
			if (snake.GetSegments().front().x == i.GetLocation().x && snake.GetSegments().front().y == i.GetLocation().y )
			{
				SnakeEatSound.PlaySound();
				snake.Grow();
				i.SetSpawnLocation(SetAppleLocation());
			}
		}
		if (snake.GetSegments().front().x == battery.GetLocation().x && snake.GetSegments().front().y == battery.GetLocation().y)
		{
			BatteryClock.restart();
			SnakeElectrifiedSound.PlaySound();
			snake.Grow();
			snake.SetIsElectrified(true);
		}
	}
	for (auto& x : AISnakes)
	{
		if (x->getIsDead() == false)
		{
			for (auto& i : AllApples)
			{
				if (x->GetSegments().front().x == i.GetLocation().x && x->GetSegments().front().y == i.GetLocation().y)
				{
					SnakeEatSound.PlaySound();
					x->Grow();
					i.SetSpawnLocation(SetAppleLocation());
				}
			}
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
		snake.SetOutline(false);
		if (snake.GetDirection() != Direction::Left)
		{
			snake.ChangeDirection(Direction::Right);
		}
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		snake.SetOutline(false);

		if (snake.GetDirection() != Direction::Right)
		{
			snake.ChangeDirection(Direction::Left);
		}
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		snake.SetOutline(false);

		if (snake.GetDirection() != Direction::Down)
		{
			snake.ChangeDirection(Direction::Up);
		}
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		snake.SetOutline(false);

		if (snake.GetDirection() != Direction::Up)
		{
			snake.ChangeDirection(Direction::Down);
		}
	}
}

void Game::CheckHighScore(int x)
{
	if (snake.GetScore() > snake.GetHighScore())
	{
		snake.SetHighScore(snake.GetScore());
	}
}

void Game::BatteryLocationTimer()
{

	if (SpawnBattery == true)
	{
		battery.SetSpawnLocation(SetBatteryLocation());
		SpawnBattery = false;
	}
}

void Game::SetAllAppleLocation()
{
	for (auto& i : AllApples)
	{
		i.SetSpawnLocation(SetAppleLocation());
	}
}

void Game::MoveAI(AISnake* AI)
{
	if (AI->GetSegments()[0].x > ClosestAppleLocation->x)
	{
		if (AI->GetDirection() != Direction::Right)
			AI->ChangeDirection(Direction::Left);
	}

	else if (AI->GetSegments()[0].x < ClosestAppleLocation->x)
	{
		if (AI->GetDirection() != Direction::Left)
			AI->ChangeDirection(Direction::Right);
	}

	else if (AI->GetSegments()[0].y < ClosestAppleLocation->y)
	{
		if (AI->GetDirection() != Direction::Up)
			AI->ChangeDirection(Direction::Down);
	}

	else if (AI->GetSegments()[0].y > ClosestAppleLocation->y)
	{
		if (AI->GetDirection() != Direction::Down)
			AI->ChangeDirection(Direction::Up);
	}

	if (AI->GetSegments()[0].y + 20 == 600)
	{
		if (AI->GetDirection() == Direction::Down)
		{
			AI->ChangeDirection(Direction::Right);
		}
	}
	else if (AI->GetSegments()[0].y - 20 == 0)
	{
		if (AI->GetDirection() == Direction::Up)
		{
			AI->ChangeDirection(Direction::Right);
		}
	}
	else if (AI->GetSegments()[0].x + 20 == 600)
	{
		if (AI->GetDirection() == Direction::Right)
		{
			AI->ChangeDirection(Direction::Down);
		}
	}
	else if (AI->GetSegments()[0].x + 20 == 600)
	{
		if (AI->GetDirection() == Direction::Right)
		{
			AI->ChangeDirection(Direction::Up);
		}
	}
	else if (AI->GetSegments()[0].x - 20 == 120)
	{
		if (AI->GetDirection() == Direction::Left)
		{
			AI->ChangeDirection(Direction::Up);
		}
	}

	for (auto& i : AISnakes)
	{
		for (auto& j : AISnakes)
		{
			if (j != i)
			{
				if (i->GetSegments()[0].x + 20 == j->GetSegments()[0].x)
				{
					if (i->GetDirection() == Direction::Right)
					{
						i->ChangeDirection(Direction::Up);
					}
				}
				else if(i->GetSegments()[0].x - 20 == j->GetSegments()[0].x)
				{
					if (i->GetDirection() == Direction::Left)
					{
						i->ChangeDirection(Direction::Up);
					}
				}
				else if (i->GetSegments()[0].y - 20 == j->GetSegments()[0].y)
				{
					if (i->GetDirection() == Direction::Up)
					{
						i->ChangeDirection(Direction::Right);
					}
				}
				else if (i->GetSegments()[0].y + 20 == j->GetSegments()[0].y)
				{
					if (i->GetDirection() == Direction::Down)
					{
						i->ChangeDirection(Direction::Right);
					}
				}
			}
		}
	}
}

sf::Vector2f Game::GetClosestApple(sf::Vector2f AISnakeLoc, std::vector<Apple>& AllApples)
{
	int distance = 10000;
	//CHECK FOR CLOSEST APPLE
	for (auto& i : AllApples)
	{
		int newDis = sqrt(pow(i.GetLocation().x - AISnakeLoc.x, 2) + pow(i.GetLocation().y - AISnakeLoc.y, 2));
		if (newDis < distance)
		{
			if (i.GetIsAlive() == true)
			{
				distance = 10000;
				*ClosestAppleLocation = i.GetLocation();
			}
		}
		

	}
	
	return *ClosestAppleLocation;
}

void Game::CheckAllSnakeCollision()
{
	for (auto& i : AISnakes)
	{
		if (i->getIsDead() == false)
		{
			
			if (snake.GetSegments().front().x == i->GetSegments()[0].x && snake.GetSegments().front().y == i->GetSegments()[0].y)
			{
				if (snake.GetIsElectified() == true)
				{
					i->Dead();
				}
				else
				{
					snake.Dead();
					i->Dead();
				}
			}
			for (auto& j : AISnakes)
			{
				if (j->getIsDead() == false)
				{
					if (j != i)
					{
						if (j->GetSegments()[0].x == i->GetSegments()[0].x && j->GetSegments()[0].y == i->GetSegments()[0].y)
						{
							j->Dead();
							i->Dead();
						}
					}
				}
			}
			for (auto& h : i->GetSegments())
			{
				if (snake.GetSegments().front().x == h.x && snake.GetSegments().front().y == h.y)
				{
					if (snake.GetIsElectified() == true)
					{
						i->Dead();
					}
					else
						snake.Dead();
				}
				for (auto& j : AISnakes)
				{
					if (j->getIsDead() == false)
					{
						if (j != i)
						{
							if (j->GetSegments()[0].x == h.x && j->GetSegments()[0].y == h.y)
							{
								j->Dead();
							}
						}
					}
				}
			}
			if (snake.getIsDead() == false)
			{
				for (auto& k : snake.GetSegments())
				{
					if (i->GetSegments()[0].x == k.x && i->GetSegments()[0].y == k.y)
					{
						i->Dead();
					}
				}
			}
		}

	}
	

}

void Game::RespawnAll()
{
	snake.Respawn();
	for (auto& i : AISnakes)
	{
		i->Respawn();
	}
}

bool Game::CheckAllDead()
{
	for (auto& i : AISnakes)
	{
		if (snake.getIsDead() == true && i->getIsDead() == true)
		{
			return true;
		}
		else
			return false;
	}
}

