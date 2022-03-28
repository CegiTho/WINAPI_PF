#include "Framework.h"

NormalObstacle::NormalObstacle(Vector2 center, Vector2 size)
{
	rect = new Rect(center, size);

	this->startPos = center;
	this->destPos = center;
	this->times = 0;
	this->isMove = false;
	
	color = CreateSolidBrush(BLACK);
	edge = CreatePen(PS_SOLID, 1, BLACK);

	type = Type::NORMAL;
}

NormalObstacle::NormalObstacle(Vector2 center, Vector2 size, Vector2 pathEnd, bool isMove ,bool loop ,double speed)
{
	rect = new Rect(center, size);

	this->isMove = isMove;
	this->startPos = center;
	endPositions.push(pathEnd);
	this->times = speed;
	this->isLoop = loop;

	color = CreateSolidBrush(BLACK);
	edge = CreatePen(PS_SOLID, 1, BLACK);

	type = Type::NORMAL;
}

NormalObstacle::~NormalObstacle()
{
	delete rect;

	DeleteObject(color);
	DeleteObject(edge);

}

void NormalObstacle::Update()
{
	if (isMove == false)
		return;

	Move();
}

void NormalObstacle::Render(HDC hdc)
{
	HBRUSH tempB = (HBRUSH)SelectObject(hdc, color);
	HPEN tempP = (HPEN)SelectObject(hdc, edge);

	rect->Render(hdc);

	SelectObject(hdc, tempB);
	SelectObject(hdc, tempP);

}
