#pragma once
#include "Snake.h"



class AISnake : public Snake
{
public:
	AISnake();
	~AISnake();
	void MoveSnake(Direction dir);

};

