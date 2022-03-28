#include "Framework.h"
#include "Polygon2.h"


Polygon2::Polygon2(vector<Vector2*> vertices)
	:vertices(vertices),rect(nullptr)
{//이거 하나 호출중.
	points = new POINT[vertices.size()];
	InitArr();
}

Polygon2::Polygon2()
	:vertices{  },rect(nullptr)
{
	points = new POINT[3];

}

Polygon2::~Polygon2()
{
	delete[] points;
}

void Polygon2::Render(HDC hdc)
{
	Polygon(hdc, points, rect == nullptr ? vertices.size() : 3);
}


void Polygon2::InitArr()
{
	if (rect != nullptr)
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
	else
	{
		if (vertices[0] != nullptr)
		{
			for (int i = 0; i < vertices.size(); i++)
			{
				points[i].x = (LONG)vertices[i]->x;
				points[i].y = (LONG)vertices[i]->y;
			}
		}
	}
}

void Polygon2::SetArr(Character* character)
{
	rect = character->GetRect();
	LONG deltaX = PickTriangle * 0.5;
	LONG deltaY = PickTriangle * 0.5 * sqrt(3.0);

	points[0].x = (LONG)character->GetRect()->center.x;
	points[0].y = (LONG)(character->GetRect()->center.y - (character->GetRect()->size.y * 0.5) - 5);
	//-5는 살짝 떨어뜨리는거임. 그리고 선 두께때문에 -3정도 안하면 어차피 부자연스러워보임.

	points[1].x = points[0].x - deltaX;
	points[1].y = points[0].y - deltaY;

	points[2].x = points[0].x + deltaX;
	points[2].y = points[0].y - deltaY;
}

void Polygon2::Shift(vector<Vector2> vertices)
{
	if (vertices.size() != this->vertices.size())
		return;

	for (int i = 0; i < vertices.size(); i++)
	{
		points[i].x = vertices[i].x;
		points[i].y = vertices[i].y;
	}
		
}

