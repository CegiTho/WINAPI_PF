#include "Framework.h"
#include "Polygon2.h"


Polygon2::Polygon2(vector<Vector2*> vertices)
	:vertices(vertices),rect(nullptr)
{//�̰� �ϳ� ȣ����.
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
		points[0].y = (LONG)(rect->center.y - (rect->size.y * 0.5) - 3);	//-3���ϸ� ���ϰ� �ȸ´µ� �Ƹ� �׵θ� �β� 1 �����ΰŰ���.

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
	//-5�� ��¦ ����߸��°���. �׸��� �� �β������� -3���� ���ϸ� ������ ���ڿ�����������.

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

