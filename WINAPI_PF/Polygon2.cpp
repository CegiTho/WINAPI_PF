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

	points = new POINT[3];
	SetArr();

}

Polygon2::~Polygon2()
{
	delete[] points;
}

void Polygon2::Render(HDC hdc)
{
	Polygon(hdc, points, rect == nullptr ? vertices.size() : 3);
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
		LONG deltaX = PickTriangle * 0.5;
		LONG deltaY = PickTriangle * 0.5 * sqrt(3.0);

		points[0].x = (LONG)rect->center.x;
		points[0].y = (LONG)(rect->center.y - (rect->size.y * 0.5) - 3);	//-3안하면 묘하게 안맞는데 아마 테두리 두꼐 1 때문인거같음.
	
		points[1].x = points[0].x - deltaX;
		points[1].y = points[0].y - deltaY;

		points[2].x = points[0].x + deltaX;
		points[2].y = points[0].y - deltaY;

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

