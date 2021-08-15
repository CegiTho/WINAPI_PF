#include "Framework.h"

NormalObstacle::NormalObstacle(Vector2 center, Vector2 size)
{
	rect = new Rect(center, size);

	this->path = nullptr;
	speed = 0;

	color = CreateSolidBrush(BLACK);
	edge = CreatePen(PS_SOLID, 1, BLACK);

	type = Type::NORMAL;
}

NormalObstacle::NormalObstacle(Vector2 center, Vector2 size, Vector2 pathEnd,double speed)
{
	rect = new Rect(center, size);

	this->speed = speed;
	this->path = new Line(this->rect->center, pathEnd);

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
	if (isMove == true)
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
