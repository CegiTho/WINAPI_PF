#include "Framework.h"

Triangle::Triangle(Vector2 xPoint, int yValue,COLORREF color)
{
	this->color = CreateSolidBrush(color);
	edge = CreatePen(PS_SOLID, 1, color);

	vertices = new POINT[3];

	LONG height = xPoint.y > yValue ?  xPoint.y - yValue : yValue - xPoint.y;
	LONG delta = height / tan(3.141592654/3);

	vertices[0].x = xPoint.x;
	vertices[0].y = xPoint.y;

	vertices[1].x = xPoint.x - delta;
	vertices[1].y = yValue;

	vertices[2].x = xPoint.x + delta;
	vertices[2].y = yValue;

	isRender = true;
}

Triangle::Triangle(Vector2 p1, Vector2 p2, Vector2 p3, COLORREF color)
{
	isRender = true;
	this->color = CreateSolidBrush(color);
	edge = CreatePen(PS_SOLID, 1, color);

	vertices = new POINT[3];

	vertices[0].x = p1.x;
	vertices[0].y = p1.y;

	vertices[1].x = p2.x;
	vertices[1].y = p2.y;

	vertices[2].x = p3.x;
	vertices[2].y = p3.y;
}

Triangle::~Triangle()
{
	DeleteObject(color);
	DeleteObject(edge);

	delete[] vertices;
}

void Triangle::Render(HDC hdc)
{
	if (isRender == false)
		return;

	Polygon(hdc, vertices, 3);
}

void Triangle::Move(int deltaX, int deltaY)
{
	for (int i = 0; i < 3; i++)
	{
		vertices[i].x += deltaX;
		vertices[i].y += deltaY;
	}
}
