#include "AISnake.h"


AISnake::AISnake()
	:Snake()
{

}

AISnake::~AISnake()
{

}

//---NOT USED IN GAME ---
void AISnake::MoveSnake(Direction dir)
{

	if (dir == Direction::Right)
	{
		ChangeDirection(Direction::Right);
	}
	if (dir == Direction::Left)
	{
		ChangeDirection(Direction::Left);
	}if (dir == Direction::Up)
	{
		ChangeDirection(Direction::Up);
	}if (dir == Direction::Down)
	{
		ChangeDirection(Direction::Down);
	}
}
