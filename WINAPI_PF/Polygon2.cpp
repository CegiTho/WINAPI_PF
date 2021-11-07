#include "Framework.h"
#include "Polygon2.h"


Polygon2::Polygon2(vector<Vector2*> vertices)
	:vertices(vertices),rect(nullptr)
{
	points = new POINT[vertices.size()];
	SetArr();
}

Polygon2::Polygon2(Rect* rect)
	:rect(rect)
{

	points = new POINT[4];
	SetArr();

}

Polygon2::~Polygon2()
{
	delete[] points;
}

void Polygon2::Render(HDC hdc)
{
	Polygon(hdc, points, vertices.size());
}

void Polygon2::Update()
{
	SetArr();
}

void Polygon2::SetArr()
{
	if (rect == nullptr)
	{
		for (int i = 0; i < vertices.size(); i++)
		{
			points[i].x = (LONG)vertices[i]->x;
			points[i].y = (LONG)vertices[i]->y;
		}
	}
	else
	{
		points[0].x = (LONG)rect->Left();
		points[0].y = (LONG)rect->Top();
	
		points[1].x = (LONG)rect->Right();
		points[1].y = (LONG)rect->Top();

		points[2].x = (LONG)rect->Right();
		points[2].y = (LONG)rect->Bottom();

		points[3].x = (LONG)rect->Left();
		points[3].y = (LONG)rect->Bottom();
	}

}

bool Polygon2::Collision(Line* line)
{
	vector<Line> lines(vertices.size());
	for (int i = 0; i < lines.size(); i++)
	{
		lines[i].Start() = *vertices[i];
		lines[i].End() = (i == lines.size() - 1) ? *vertices[0] : *vertices[i + 1];
	}

	for (Line l : lines)
	{
		if (l.Collision(line) == true)
			return true;
	}

	return false;
}

bool Polygon2::Collision(Circle* circle)
{
	return false;
}

bool Polygon2::Collision(Rect* rect)
{
	return false;
}

