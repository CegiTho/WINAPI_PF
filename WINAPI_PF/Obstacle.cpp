#include "Framework.h"

Obstacle::Obstacle()
{
	isGoback = false;
	id = ID::OBSTACLE;
}

Obstacle::~Obstacle()
{
}

void Obstacle::Move()
{
	if (isGoback == false)	//start -> end
	{
		this->rect->center = LERP(this->rect->center, endPos, DELTA * times);
		double diff = (endPos - this->rect->center).Length();
		
		if (diff < EPSILON && isLoop == true)
			isGoback = true;
		else if (diff < EPSILON && isLoop == false)
		{
			isGoback = false;
			isMove = false;
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
