#include "Snake.h"
#include "Window.h"
#include <thread>
#include <chrono>
#include <iostream>

Snake::Snake()
	:rectangle({snakeSegmentSize.x - 1,snakeSegmentSize.y - 1 }),GameOver("GameOver.wav"),HighScoreFile("HighScore")
{
	rectangle.setFillColor(sf::Color::Red);
	//rectangle.setOutlineThickness(1);
	//rectangle.setOutlineColor(sf::Color::White);
	m_SegmentPos.emplace_back(SnakeSegment{ 160,20 });
	m_SegmentPos.emplace_back(SnakeSegment{ 140,20 });
	m_SegmentPos.emplace_back(SnakeSegment{ 120,20});
	
	highScore = HighScoreFile.GetScore();

	ElectricBox.setFillColor(sf::Color(0, 0, 255, 120));
	ElectricBox.setSize(sf::Vector2f(20, 20));
}

Snake::~Snake()
{
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


		if (m_SegmentPos[0].x % 20 == 0 && m_SegmentPos[0].y % 20 == 0)
			m_direction = m_direction_queue;


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
	
			if (ElectrifiedClock.getElapsedTime().asSeconds() - TimeStamp >= 10)
			{
				IsElectrified = false;
			}
		}
	}
}


void Snake::Render(Window& window)
{
	if (IsElectrified == true)
	{
		BecomeElectrified(window);
	}

	for (int i = 0; i != m_SegmentPos.size(); i++)
	{
		rectangle.setPosition(sf::Vector2f(m_SegmentPos[i].x, m_SegmentPos[i].y));
		window.Draw(rectangle);
	}
}



void Snake::Grow()
{
	score += 10;

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
	GameOver.PlaySound();
	isDead = true;
	score = 0;
	std::this_thread::sleep_for(std::chrono::seconds(3));
	m_SegmentPos.clear();	
	Respawn();
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
	if (isDead == true)
	{
		isDead = false;
		m_SegmentPos.emplace_back(SnakeSegment{ 160,20 });
		m_SegmentPos.emplace_back(SnakeSegment{ 140,20 });
		m_SegmentPos.emplace_back(SnakeSegment{ 120,20 });
		m_direction = Direction::none;
		m_direction_queue = Direction::none;
	}
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

std::vector<SnakeSegment> Snake::GetSegments()
{
	return m_SegmentPos;
}

Direction Snake::GetDirection()
{
	return m_direction;
}

