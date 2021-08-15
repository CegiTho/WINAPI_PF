#include "Framework.h"

Obstacle::Obstacle()
{
	id = ID::OBSTACLE;
}

Obstacle::~Obstacle()
{
}

void Obstacle::Move()
{
	Vector2 dir = (path->end - path->start) / path->Length();
	
	rect->center += dir * speed * DELTA;
}
