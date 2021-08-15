#include "Framework.h"

Shade::Shade(T_Object* obj, Vector2* lSource)
	:object(obj),lSource(lSource),constant(0),isStatic(true)
{
	for (int i = 0; i < 4; i++)
	{
		points.emplace_back(new POINT[4]);
	}

	CreateSpotShade();

	color = CreateSolidBrush(BLACK);
}

Shade::Shade(T_Object* obj, double constant)
	:object(obj),lSource(nullptr),constant(constant),isStatic(true)
{
	for (int i = 0; i < 4; i++)
	{
		points.emplace_back(new POINT[4]);
	}

	CreateCurtainShade();

	color = CreateSolidBrush(BLACK);
}

Shade::~Shade()
{
	for (POINT* point : points)
		delete point;

	DeleteObject(color);
}

void Shade::CreateCurtainShade()
{
	if (lSource != nullptr)
		return;

	{//LeftTop - RightTop
		points[0][0] = object->GetRect()->LeftTop();
		points[0][1] = Direction(points[0][0], constant, ShadeLength);
		points[0][3] = object->GetRect()->RightTop();
		points[0][2] = Direction(points[0][3], constant, ShadeLength);
	}
	{//RightTop - RightBottom
		points[1][0] = object->GetRect()->RightTop();
		points[1][1] = Direction(points[1][0], constant, ShadeLength);
		points[1][3] = object->GetRect()->RightBottom();
		points[1][2] = Direction(points[1][3], constant, ShadeLength);
	}
	{//LeftTop - RightTop
		points[2][0] = object->GetRect()->RightBottom();
		points[2][1] = Direction(points[2][0], constant, ShadeLength);
		points[2][3] = object->GetRect()->LeftBottom();
		points[2][2] = Direction(points[2][3], constant, ShadeLength);
	}
	{//LeftTop - RightTop
		points[3][0] = object->GetRect()->LeftBottom();
		points[3][1] = Direction(points[3][0], constant, ShadeLength);
		points[3][3] = object->GetRect()->LeftTop();
		points[3][2] = Direction(points[3][3], constant, ShadeLength);
	}
}

void Shade::CreateSpotShade()
{
	if (lSource == nullptr)
		return;

	double leftTop = atan2(object->GetRect()->LeftTop().y - lSource->y, object->GetRect()->LeftTop().x - lSource->x);
	double rightTop = atan2(object->GetRect()->RightTop().y - lSource->y, object->GetRect()->RightTop().x - lSource->x);
	double rightBottom = atan2(object->GetRect()->RightBottom().y - lSource->y, object->GetRect()->RightBottom().x - lSource->x);
	double leftBottom = atan2(object->GetRect()->LeftBottom().y - lSource->y, object->GetRect()->LeftBottom().x - lSource->x);
	
	{//LeftTop - RightTop
		points[0][0] = object->GetRect()->LeftTop();
		points[0][1] = Direction(points[0][0], leftTop, ShadeLength);
		points[0][3] = object->GetRect()->RightTop();
		points[0][2] = Direction(points[0][3], rightTop, ShadeLength);
	}
	{//RightTop - RightBottom
		points[1][0] = object->GetRect()->RightTop();
		points[1][1] = Direction(points[1][0], rightTop, ShadeLength);
		points[1][3] = object->GetRect()->RightBottom();
		points[1][2] = Direction(points[1][3], rightBottom, ShadeLength);
	}
	{//RightBottom - LeftBottom
		points[2][0] = object->GetRect()->RightBottom();
		points[2][1] = Direction(points[2][0], rightBottom, ShadeLength);
		points[2][3] = object->GetRect()->LeftBottom();
		points[2][2] = Direction(points[2][3], leftBottom, ShadeLength);
	}
	{//LeftBottom - LeftTop
		points[3][0] = object->GetRect()->LeftBottom();
		points[3][1] = Direction(points[3][0], leftBottom, ShadeLength);
		points[3][3] = object->GetRect()->LeftTop();
		points[3][2] = Direction(points[3][3], leftTop, ShadeLength);
	}


}

void Shade::Update()
{
	if(lSource == nullptr)
		CurtainUpdate();
	else
		SpotUpdate();
	
}

void Shade::Render(HDC hdc)
{
	HBRUSH prev = (HBRUSH)SelectObject(hdc, color);
	for (POINT* point : points)
	{
		Polygon(hdc, point, 4);
	}
	SelectObject(hdc, prev);
}

void Shade::CurtainUpdate()
{
	if (lSource != nullptr)
		return;

	{//LeftTop - RightTop
		points[0][0] = object->GetRect()->LeftTop();
		points[0][1] = Direction(points[0][0], constant, ShadeLength);
		points[0][3] = object->GetRect()->RightTop();
		points[0][2] = Direction(points[0][3], constant, ShadeLength);
	}
	{//RightTop - RightBottom
		points[1][0] = object->GetRect()->RightTop();
		points[1][1] = Direction(points[1][0], constant, ShadeLength);
		points[1][3] = object->GetRect()->RightBottom();
		points[1][2] = Direction(points[1][3], constant, ShadeLength);
	}
	{//LeftTop - RightTop
		points[2][0] = object->GetRect()->RightBottom();
		points[2][1] = Direction(points[2][0], constant, ShadeLength);
		points[2][3] = object->GetRect()->LeftBottom();
		points[2][2] = Direction(points[2][3], constant, ShadeLength);
	}
	{//LeftTop - RightTop
		points[3][0] = object->GetRect()->LeftBottom();
		points[3][1] = Direction(points[3][0], constant, ShadeLength);
		points[3][3] = object->GetRect()->LeftTop();
		points[3][2] = Direction(points[3][3], constant, ShadeLength);
	}
	
	

}

void Shade::SpotUpdate()
{
	if (lSource == nullptr)
		return;

	double leftTop = atan2(object->GetRect()->LeftTop().y - lSource->y, object->GetRect()->LeftTop().x - lSource->x);
	double rightTop = atan2(object->GetRect()->RightTop().y - lSource->y, object->GetRect()->RightTop().x - lSource->x);
	double rightBottom = atan2(object->GetRect()->RightBottom().y - lSource->y, object->GetRect()->RightBottom().x - lSource->x);
	double leftBottom = atan2(object->GetRect()->LeftBottom().y - lSource->y, object->GetRect()->LeftBottom().x - lSource->x);

	{//LeftTop - RightTop
		points[0][0] = object->GetRect()->LeftTop();
		points[0][1] = Direction(points[0][0], leftTop, ShadeLength);
		points[0][3] = object->GetRect()->RightTop();
		points[0][2] = Direction(points[0][3], rightTop, ShadeLength);
	}
	{//RightTop - RightBottom
		points[1][0] = object->GetRect()->RightTop();
		points[1][1] = Direction(points[1][0], rightTop, ShadeLength);
		points[1][3] = object->GetRect()->RightBottom();
		points[1][2] = Direction(points[1][3], rightBottom, ShadeLength);
	}
	{//RightBottom - LeftBottom
		points[2][0] = object->GetRect()->RightBottom();
		points[2][1] = Direction(points[2][0], rightBottom, ShadeLength);
		points[2][3] = object->GetRect()->LeftBottom();
		points[2][2] = Direction(points[2][3], leftBottom, ShadeLength);
	}
	{//LeftBottom - LeftTop
		points[3][0] = object->GetRect()->LeftBottom();
		points[3][1] = Direction(points[3][0], leftBottom, ShadeLength);
		points[3][3] = object->GetRect()->LeftTop();
		points[3][2] = Direction(points[3][3], leftTop, ShadeLength);
	}
}

POINT Shade::Direction(POINT origin, double inclination, double length)
{
	POINT endPos;
	endPos.x = origin.x + cos(inclination) * length;
	endPos.y = origin.y + sin(inclination) * length;

	return endPos;
}
