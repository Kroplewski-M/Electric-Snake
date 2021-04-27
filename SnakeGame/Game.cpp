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
	ScoreText.setPosition(sf::Vector2f(2, 70));

	AI1Score.setFont(ScoreFont);
	AI1Score.setCharacterSize(25);
	AI1Score.setPosition(sf::Vector2f(2, 120));

	AI2Score.setFont(ScoreFont);
	AI2Score.setCharacterSize(25);
	AI2Score.setPosition(sf::Vector2f(2, 150));

	AI3Score.setFont(ScoreFont);
	AI3Score.setCharacterSize(25);
	AI3Score.setPosition(sf::Vector2f(2, 180));

	AI4Score.setFont(ScoreFont);
	AI4Score.setCharacterSize(25);
	AI4Score.setPosition(sf::Vector2f(2, 210));

	AI5Score.setFont(ScoreFont);
	AI5Score.setCharacterSize(25);
	AI5Score.setPosition(sf::Vector2f(2, 240));

	HighScoreText.setFont(ScoreFont);
	HighScoreText.setCharacterSize(25);
	HighScoreText.setPosition({ 2,10 });

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

	snake.SetName("Player");
	AI1->SetName("AI1");
	AI2->SetName("AI2");
	AI3->SetName("AI3");
	AI4->SetName("AI4");
	AI5->SetName("AI5");

	

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

	if (GameIsFinished == false)
	{

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

		for (auto& i : AllApples)
		{
			i.Update();
		}

		battery.Update();

		bool isOneSnakeAlive = false;
		for (auto& i : AISnakes)
		{
			if (i->getIsDead() == false) 
			{ 
				isOneSnakeAlive = true; 
				break;
			}
		}

		if (isOneSnakeAlive == false && snake.getIsDead() == true)
			GameIsFinished = true;
	}
	else
		FindWinner();
	
}

void Game::Render()
{
	m_window.BeginDraw();  //CLEAR

	if (GameIsFinished == false)
{

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
		ScoreText.setString("Player: " + std::to_string(snake.GetScore()));
		AI1Score.setString("AI1: " + std::to_string(AI1->GetScore()));
		AI2Score.setString("AI2: " + std::to_string(AI2->GetScore()));
		AI3Score.setString("AI3: " + std::to_string(AI3->GetScore()));
		AI4Score.setString("AI4: " + std::to_string(AI4->GetScore()));
		AI5Score.setString("AI5: " + std::to_string(AI5->GetScore()));

		CheckHighScore(snake.GetScore());
		CountDownText.setString( std::to_string(snake.GetCountDown()));

		m_window.Draw(CountDownCircle);
		m_window.Draw(CountDownText);
		m_window.Draw(HighScoreText);
		m_window.Draw(ScoreText);

		m_window.Draw(AI1Score);
		m_window.Draw(AI2Score);
		m_window.Draw(AI3Score);
		m_window.Draw(AI4Score);
		m_window.Draw(AI5Score);

		m_window.Draw(Tips);

	}
	else if (GameIsFinished == true)
	{
		GameOverScreen();
	}
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

void Game::GameOverScreen()
{
	
		sf::RectangleShape EndMenuBox;
		EndMenuBox.setSize({ 200,400 });
		EndMenuBox.setOutlineThickness(2);
		EndMenuBox.setOutlineColor(sf::Color::White);
		EndMenuBox.setFillColor(sf::Color::Blue);
		EndMenuBox.setPosition(300, 100);

		GameOverText.setFont(ScoreFont);
		GameOverText.setCharacterSize(30);
		GameOverText.setPosition(340, 110);
		GameOverText.setColor(sf::Color::Black);
		GameOverText.setOutlineThickness(1);
		GameOverText.setOutlineColor(sf::Color::White);
		GameOverText.setString("Game Over!");

		WinnerText.setFont(ScoreFont);
		WinnerText.setCharacterSize(30);
		WinnerText.setPosition(355, 165);
		WinnerText.setColor(sf::Color::Black);
		WinnerText.setString("Winner:");

		WinningPlayer.setFont(ScoreFont);
		WinningPlayer.setCharacterSize(50);
		WinningPlayer.setPosition(330, 220);
		WinningPlayer.setColor(sf::Color::Red);
		WinningPlayer.setOutlineThickness(1);
		WinningPlayer.setOutlineColor(sf::Color::White);
		//WinningPlayer.setString("Player");

		RestartButton.setSize({ 100,50 });
		RestartButton.setPosition({ 350,340 });
		RestartButton.setFillColor(sf::Color::Black);

		QuitButton.setSize({ 100,50 });
		QuitButton.setPosition({ 350,400 });
		QuitButton.setFillColor(sf::Color::Black);


		PlayAgainText.setFont(ScoreFont);
		PlayAgainText.setCharacterSize(35);
		PlayAgainText.setPosition(350, 340);
		PlayAgainText.setColor(sf::Color::Red);
		PlayAgainText.setOutlineThickness(1);
		PlayAgainText.setOutlineColor(sf::Color::White);
		PlayAgainText.setString("Restart");
		

		QuitText.setFont(ScoreFont);
		QuitText.setCharacterSize(35);
		QuitText.setPosition(370, 405);
		QuitText.setColor(sf::Color::Red);
		QuitText.setOutlineThickness(1);
		QuitText.setOutlineColor(sf::Color::White);
		QuitText.setString("Quit");

		if (GetWindow()->getMouseLocation().x > RestartButton.getPosition().x && GetWindow()->getMouseLocation().x < RestartButton.getPosition().x + RestartButton.getSize().x &&
			GetWindow()->getMouseLocation().y > RestartButton.getPosition().y && GetWindow()->getMouseLocation().y < RestartButton.getPosition().y + RestartButton.getSize().y)
		{
			RestartButton.setOutlineThickness(2);
			RestartButton.setOutlineColor(sf::Color::White);

			if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
			{
				GameIsFinished = false;
				RespawnAll();
				return;
			}
		}
		else
			RestartButton.setOutlineThickness(0);

		if (GetWindow()->getMouseLocation().x > QuitButton.getPosition().x && GetWindow()->getMouseLocation().x < QuitButton.getPosition().x + QuitButton.getSize().x &&
			GetWindow()->getMouseLocation().y > QuitButton.getPosition().y && GetWindow()->getMouseLocation().y < QuitButton.getPosition().y + QuitButton.getSize().y)
		{
			QuitButton.setOutlineThickness(2);
			QuitButton.setOutlineColor(sf::Color::White);

			if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
			{
				m_window.SetIsDone(true);
			}
		}
		else
			QuitButton.setOutlineThickness(0);

		m_window.Draw(EndMenuBox);
		m_window.Draw(GameOverText);
		m_window.Draw(WinnerText);
		m_window.Draw(WinningPlayer);
		m_window.Draw(RestartButton);
		m_window.Draw(QuitButton);
		m_window.Draw(PlayAgainText);
		m_window.Draw(QuitText);

}

void Game::FindWinner()
{
	if (snake.GetScore() > TopScore)
	{
		TopScore = snake.GetScore();
		WinningPlayer.setString(snake.GetName() + "\n" + "Score " + std::to_string(snake.GetScore()));

	}
	for (auto& i : AISnakes)
	{
		if (i->GetScore() > TopScore)
		{
			TopScore = i->GetScore();
			WinningPlayer.setString("   " + i->GetName() + "\n" + "Score " + std::to_string(i->GetScore()));
		}
	}

}

void Game::SetAllDirection()
{
	for (auto& i : AISnakes)
	{
		i->SetAutoDirection();
	}
}

