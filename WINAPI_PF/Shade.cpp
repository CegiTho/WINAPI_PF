#include "Framework.h"

Shade::Shade(T_Object* obj, Vector2* lSource, STAGE_NUM stage)
	:object(obj),lSource(lSource),constant(0),isStatic(true)
{
	for (int i = 0; i < 4; i++)
	{
		points.emplace_back(new POINT[4]);
	}

	CreateSpotShade();

	AlphaColor(stage);
}

Shade::Shade(T_Object* obj, double constant, STAGE_NUM stage)
	:object(obj),lSource(nullptr),constant(constant),isStatic(true)
{
	for (int i = 0; i < 4; i++)
	{
		points.emplace_back(new POINT[4]);
	}

	CreateCurtainShade();

	AlphaColor(stage);

	//color = CreateSolidBrush(BLACK);
}

Shade::~Shade()
{
	for (POINT* point : points)
		delete point;

	DeleteObject(color);
}

void Shade::AlphaColor(STAGE_NUM stage)
{
	COLORREF bg_Color;
	switch (stage)
	{
	case STAGE_1:
		bg_Color = BG_COLOR_1;
		break;
	case STAGE_2:
		bg_Color = BG_COLOR_2;
		break;
	case STAGE_3:
		bg_Color = BG_COLOR_3;
		break;
	case STAGE_4:
		bg_Color = BG_COLOR_4;
		break;
	case STAGE_5:
		bg_Color = BG_COLOR_5;
		break;
	}

	DWORD red = GetRValue(bg_Color);
	DWORD green = GetGValue(bg_Color);
	DWORD blue = GetBValue(bg_Color);

	double alpha = SHADE_ALPHA / 255.0;

	//GdiAlphaBlend함수 동작식.
	//dest.color = (src.color * alpha) + {dest.color * (1-alpha)}
	//dest,src각각의 alpha채널에 따라 식이 달라지는데 지금은 일단 둘 다 알파채널 없는 계산
	DWORD op_Red = red * (1 - alpha);
	DWORD op_Green = green * (1 - alpha);
	DWORD op_Blue = blue * (1 - alpha);

	color = CreateSolidBrush(RGB(op_Red, op_Green, op_Blue));
	edge = CreatePen(PS_SOLID,1,RGB(op_Red, op_Green, op_Blue));
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
	HBRUSH prevBrush = (HBRUSH)SelectObject(hdc, color);
	HPEN prevPen = (HPEN)SelectObject(hdc, edge);
	for (POINT* point : points)
	{
		Polygon(hdc, point, 4);
	}
	SelectObject(hdc, prevBrush);
	SelectObject(hdc, prevPen);
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
