#include "Snake.h"
#include "Window.h"
#include <thread>
#include <chrono>
#include <iostream>

 Snake::Snake()
	:rectangle({snakeSegmentSize.x - 1,snakeSegmentSize.y - 1 }),GameOver("GameOver.wav"),HighScoreFile("HighScore")
{
	 //SETS A RANDOM POSITIION FOR THE SNAKE, DEFUALT SIZE IS 3
	randomSpawnX = (rand()%(25-8+ 1) + 8)* 20;
	randomSpawnY = (rand() % 25)* 20;

	rectangle.setFillColor(GetRandomColor());
	//rectangle.setOutlineThickness(1);
	//rectangle.setOutlineColor(sf::Color::White);
	m_SegmentPos.push_back(SnakeSegment{ randomSpawnX,randomSpawnY });
	m_SegmentPos.push_back(SnakeSegment{ randomSpawnX - 20, randomSpawnY });
	m_SegmentPos.push_back(SnakeSegment{ randomSpawnX - 40,randomSpawnY});
	
	//GETS THE HIGH SCRORE AT BEGGINING OF GAME
	highScore = HighScoreFile.GetScore();

	ElectricBox.setFillColor(sf::Color(0, 0, 255, 120));
	ElectricBox.setSize(sf::Vector2f(20, 20));

	SetAutoDirection();
}

Snake::~Snake()
{
	//OVERRIDES HIGH SCRORE FILE IF PLAYER BEATS IT
	if (highScore > HighScoreFile.GetScore())
	{
		HighScoreFile.OverRideScore(highScore);
	}
}

void Snake::Update()
{
	if(isDead == false)
	{

		while (clock.getElapsedTime().asMilliseconds() < 120);
		clock.restart();

		//ADD MOVEMENT TO A MOVEMENT QUEUE
		if (m_SegmentPos[0].x % 20 == 0 && m_SegmentPos[0].y % 20 == 0)
			m_direction = m_direction_queue;

		//MOVEMENT OF SNAKE
		switch (m_direction)
		{
		case Direction::Up:
			std::reverse(m_SegmentPos.begin(), m_SegmentPos.end());
			m_SegmentPos.push_back(m_SegmentPos[m_SegmentPos.size() - 1]);
			std::reverse(m_SegmentPos.begin(), m_SegmentPos.end());
			m_SegmentPos[0].y -= 20;
			m_SegmentPos.pop_back();
			break;
		case Direction::Down:
			std::reverse(m_SegmentPos.begin(), m_SegmentPos.end());
			m_SegmentPos.push_back(m_SegmentPos[m_SegmentPos.size() - 1]);
			std::reverse(m_SegmentPos.begin(), m_SegmentPos.end());
			m_SegmentPos[0].y += 20;
			m_SegmentPos.pop_back();
			break;
		case Direction::Left:
			std::reverse(m_SegmentPos.begin(), m_SegmentPos.end());
			m_SegmentPos.push_back(m_SegmentPos[m_SegmentPos.size() - 1]);
			std::reverse(m_SegmentPos.begin(), m_SegmentPos.end());
			m_SegmentPos[0].x -= 20;
			m_SegmentPos.pop_back();
			break;
		case Direction::Right:
			std::reverse(m_SegmentPos.begin(), m_SegmentPos.end());
			m_SegmentPos.push_back(m_SegmentPos[m_SegmentPos.size() - 1]);
			std::reverse(m_SegmentPos.begin(), m_SegmentPos.end());
			m_SegmentPos[0].x += 20;
			m_SegmentPos.pop_back();
			break;
		}
		CheckCollision();

		SetTimeStamp(ElectrifiedClock.getElapsedTime().asSeconds());

		if (IsElectrified == true)
		{
			//STARTS TIMER FOR ELECTRIFIED
			if (ElectrifiedClock.getElapsedTime().asSeconds() - TimeStamp >= 10)
			{
				IsElectrified = false;
			}
		}



	}
		int timer = GameClock.getElapsedTime().asSeconds();
		if (timer > 0)
		{
			CountDown--;
			GameClock.restart();
		}
		//KILLS SNAKES IF TIMER IS = 0
		if (CountDown <= 0)
		{
			Dead();
		}
}


void Snake::Render(Window& window)
{
	//DRAWS ELECRIFIED GRID ROUND THE SNAKE
	if (IsElectrified == true)
	{
		BecomeElectrified(window);
	}
	//RENDERS SNAKE SEGMENTS
	for (int i = 0; i != m_SegmentPos.size(); i++)
	{
		rectangle.setPosition(sf::Vector2f(m_SegmentPos[i].x, m_SegmentPos[i].y));
		window.Draw(rectangle);
	}
}



void Snake::Grow()
{
	score += 10;
		//GROWS SEGMENT IN A LOCATION DEPENDING ON SNAKE LOCATION
		if (m_direction == Direction::Up)
		{
			m_SegmentPos.emplace_back(SnakeSegment{ m_SegmentPos[0].x  ,m_SegmentPos[0].y + 20 });
			return;
		}
		if (m_direction == Direction::Down)
		{
			m_SegmentPos.emplace_back(SnakeSegment{ m_SegmentPos[0].x,m_SegmentPos[0].y - 20 });
			return;
		}
		if (m_direction == Direction::Left)
		{
			m_SegmentPos.emplace_back(SnakeSegment{ m_SegmentPos[0].x + 20 ,m_SegmentPos[0].y });
			return;
		}
		if (m_direction == Direction::Right)
		{
			m_SegmentPos.emplace_back(SnakeSegment{ m_SegmentPos[0].x - 20 ,m_SegmentPos[0].y });
			return;
		}
	
}

void Snake::ChangeDirection(Direction newDirection)
{
	m_direction_queue = newDirection;
}

void Snake::Dead()
{
	//KILLS SNAKE

	isDead = true;
	//GameOver.PlaySound();
	IsElectrified = false;
	//score = 0;
	//std::this_thread::sleep_for(std::chrono::seconds(3));
	//m_SegmentPos.clear();	
	//Respawn();
}

bool Snake::CheckCollision()
{
	//SNAKE VS WORLD
	if (m_SegmentPos[0].x == 600 || m_SegmentPos[0].x == 100)
	{
		Dead();
	}
	else if (m_SegmentPos[0].y == -20 || m_SegmentPos[0].y == 600)
	{
		Dead();
	}
	//SNAKE VS SNAKE
	for (int i = 1; i < m_SegmentPos.size(); i++ )
	{
		if (m_SegmentPos[0].x == m_SegmentPos[i].x && m_SegmentPos[0].y == m_SegmentPos[i].y)
		{
			Dead();
			break;
		}

	}

	return true;
}

bool Snake::getIsDead()
{
	return isDead;
}

void Snake::Respawn()
{
	//RESPAWNS THE SNKAE IN A RANDOM POSITION
		m_SegmentPos.clear();

		randomSpawnX = (rand()%(25-8+ 1) + 8)* 20;
		randomSpawnY = (rand() % 25)* 20;

		 headPos = sf::Vector2i(randomSpawnX,randomSpawnY) ;
		 subHeadPos = sf::Vector2i(randomSpawnX-20,randomSpawnY);


		m_SegmentPos.emplace_back(SnakeSegment{headPos.x,headPos.y});
		m_SegmentPos.emplace_back(SnakeSegment{ subHeadPos.x,  subHeadPos.y});
		m_SegmentPos.emplace_back(SnakeSegment{ randomSpawnX - 40,randomSpawnY });

		SetAutoDirection();

		score = 0;
		m_direction = Direction::Right;
		m_direction_queue = Direction::none;
		isDead = false;
		CountDown = 90;
		//SetOutline(true);
}

int Snake::GetScore()
{
	return score;
}

int Snake::GetHighScore()
{
	return highScore;
}

void Snake::SetHighScore(int x)
{
	highScore = x;
}

void Snake::BecomeElectrified(Window& window)
{
	//SETS THE POSITIONS OF THE ELECTRIFIED SEGMENTS AROUND THE SNAKE
	for (int i = 0; i < m_SegmentPos.size(); i++)
	{
		int a, b;
		for (a = -1; a <= 1; a++)
		{
			for (b = -1; b <= 1; b++)
			{

				if (a == 0 && b == 0)
					continue;

				float newX = m_SegmentPos[i].x + (snakeSegmentSize.x * b);
				float newY = m_SegmentPos[i].y + (snakeSegmentSize.y * a);

				if (newY < 0 || newY >= 600 || newX < 120 || newX >= 600)
					continue;

				ElectricBox.setPosition(newX, newY);
				ElectricBody.emplace_back(ElectricBox);
			}
		}	
	}



		for (int j = 0; j < ElectricBody.size(); j++)
		{
			window.Draw(ElectricBody[j]);
		}
		ElectricBody.clear();
}

void Snake::SetIsElectrified(bool electrified)
{
	IsElectrified = electrified;
}

void Snake::SetTimeStamp(int time)
{
	if (IsElectrified == false)
	{
		TimeStamp = time;
	}
}

int Snake::GetCountDown()
{
	return CountDown;
}

sf::Color Snake::GetRandomColor()
{
	//CHOSES A RAND COLOR
	int color = 0;
	color = rand() % (5 - 1 + 1) + 1;

	if (color == 1)
		return sf::Color::Red;
	if (color == 2)
		return sf::Color::Cyan;
	if (color == 3)
		return sf::Color::Green;
	if (color == 4)
		return sf::Color::Magenta;
	if (color == 5)
		return sf::Color::Yellow;
}

std::vector<SnakeSegment> Snake::GetSegments()
{
	return m_SegmentPos;
}

Direction Snake::GetDirection()
{
	return m_direction;
}

void Snake::SetOutline(bool x)
{
	//SHOWS OULINE OF SNAKE
	if (x == true)
	{
		rectangle.setOutlineThickness(2);
		rectangle.setOutlineColor(sf::Color::White);
	}
	if (x == false)
	{
		rectangle.setOutlineThickness(0);
	}
}

bool Snake::GetIsElectified()
{
	return IsElectrified;
}

void Snake::SetName(std::string name)
{
	Name = name;
}

std::string Snake::GetName()
{
	return Name;
}

void Snake::SetAutoDirection()
{
	//if head is above sub seg then go up
	if (headPos.y < subHeadPos.y)
	{
		m_direction = Direction::Up;
	}
	//if head is below sub then do down
	else if (headPos.y > subHeadPos.y)
	{
		m_direction = Direction::Down;
	}
	//if head is to the left of the sub then go left
	else if (headPos.x < subHeadPos.x)
	{
		m_direction = Direction::Left;
	}
	//if the head if to the right of the sub then to right
	else if (headPos.x > subHeadPos.x)
	{
		m_direction = Direction::Right;
	}
}

