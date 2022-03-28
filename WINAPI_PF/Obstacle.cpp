#include "Framework.h"

Obstacle::Obstacle()
{
	isGoback = false;
	id = ID::OBSTACLE;
}

Obstacle::~Obstacle()
{
}

void Obstacle::SetIsMove(bool value)
{
	if (endPositions.empty() == true)
		return;

  	this->isMove = value;
	destPos = endPositions.front();
	endPositions.pop();
}

void Obstacle::Move()
{
	if (isGoback == false)	//start -> end
	{
		this->rect->center = LERP(this->rect->center, destPos, DELTA * times);
		double diff = (destPos - this->rect->center).Length();
		
		if (diff < EPSILON && isLoop == true)
			isGoback = true;
		else if (diff < EPSILON && isLoop == false)
		{
			isGoback = false;
			isMove = false;
			destPos = FAR_AWAY;
		}

	}
	else					//end -> start
	{
		double diff = (startPos - this->rect->center).Length();
		if (diff < EPSILON)
			isGoback = false;

		this->rect->center = LERP(this->rect->center, startPos, DELTA * times);
	}
}
