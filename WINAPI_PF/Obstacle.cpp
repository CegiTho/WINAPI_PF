#include "Framework.h"

Obstacle::Obstacle()
{
	isGoback = false;
	id = ID::OBSTACLE;
	time = 0.0;
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
		time += DELTA;
		Vector2 newPos = Math::SineInterpolation(startPos, destPos, times, time);
		Vector2 delta = newPos - this->rect->center;
		this->rect->center = newPos;
		double diff = (destPos - this->rect->center).Length();
		
		for (Character* character : moveWith)
		{
			character->GetRect()->center += delta;
		}

		if (diff <= EPSILON && isLoop == true)
		{
			isGoback = true;
			time = 0.0;
		}
		else if (diff < EPSILON && isLoop == false)
		{
			startPos = destPos;
			isGoback = false;
			isMove = false;
			time = 0.0;
		}
	}
	else					//end -> start
	{
		time += DELTA;
		Vector2 newPos = Math::SineInterpolation(destPos, startPos, times, time);
		Vector2 delta = newPos - this->rect->center;
		this->rect->center = newPos;

		for (Character* character : moveWith)
		{
			character->GetRect()->center += delta;
		} 

		double diff = (startPos - this->rect->center).Length();
		if (diff < EPSILON)
		{
			isGoback = false;
			time = 0.0;
		}
	}
}

void Obstacle::AddMoveWith(Character* character)
{
	moveWith.emplace_back(character);
}
