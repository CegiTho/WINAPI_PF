#include "Framework.h"

Shade::Shade(Rect* rect, double constant, STAGE_NUM stage)
	: rect(rect),lSource(nullptr), constant(constant), isStatic(true)
{

	CreateShade();

	AlphaColor(stage);
}

Shade::Shade(Rect* rect, Vector2* lSource, STAGE_NUM stage)
	: rect(rect), lSource(lSource), constant(0), isStatic(true)
{
	CreateShade();

	AlphaColor(stage);
}

Shade::~Shade()
{
	delete[] shadeEdge;

	DeleteObject(color);
	DeleteObject(edge);
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

	double alpha = ALPHA / 255.0;

	//GdiAlphaBlend�Լ� ���۽�.
	//dest.color = (src.color * alpha) + {dest.color * (1-alpha)}
	//dest,src������ alphaä�ο� ���� ���� �޶����µ� ������ �ϴ� �� �� ����ä�� ���� ���
	DWORD op_Red = red * (1 - alpha);
	DWORD op_Green = green * (1 - alpha);
	DWORD op_Blue = blue * (1 - alpha);

	color = CreateSolidBrush(RGB(op_Red, op_Green, op_Blue));
	edge = CreatePen(PS_SOLID,1,RGB(op_Red, op_Green, op_Blue));
}

void Shade::CreateShade()
{
	shadeEdge = new POINT[6];

	Update();
}

void Shade::Update()
{
	ProjectionUpdate();
	SelectEdge();
}

void Shade::Render(HDC hdc)
{
	HBRUSH prevBrush = (HBRUSH)SelectObject(hdc, color);
	HPEN prevPen = (HPEN)SelectObject(hdc, edge);
	
	Polygon(hdc, shadeEdge, 6);
	
	SelectObject(hdc, prevBrush);
	SelectObject(hdc, prevPen);
}

void Shade::ProjectionUpdate()
{
	//projection���� ����� �ָ� �ִ� �׸����� ������ ����
	if (lSource == nullptr)
	{
		projection[PointSeq::LEFTBOTTOM] = Direction(this->rect->GetPoint(PointSeq::LEFTBOTTOM), constant, ShadeLength).GetPoint();
		projection[PointSeq::RIGHTTOP] = Direction(this->rect->GetPoint(PointSeq::RIGHTTOP), constant, ShadeLength).GetPoint();
		projection[PointSeq::LEFTTOP] = Direction(this->rect->GetPoint(PointSeq::LEFTTOP), constant, ShadeLength).GetPoint();
		projection[PointSeq::RIGHTBOTTOM] = Direction(this->rect->GetPoint(PointSeq::RIGHTBOTTOM), constant, ShadeLength).GetPoint();
	}
	else
	{
		double leftTop = atan2(rect->LeftTop().y - lSource->y, rect->LeftTop().x - lSource->x);
		double rightTop = atan2(rect->RightTop().y - lSource->y, rect->RightTop().x - lSource->x);
		double rightBottom = atan2(rect->RightBottom().y - lSource->y, rect->RightBottom().x - lSource->x);
		double leftBottom = atan2(rect->LeftBottom().y - lSource->y, rect->LeftBottom().x - lSource->x);

		projection[PointSeq::LEFTTOP] =
			Direction(this->rect->GetPoint(PointSeq::LEFTTOP), leftTop, ShadeLength).GetPoint();
		projection[PointSeq::RIGHTTOP] =
			Direction(this->rect->GetPoint(PointSeq::RIGHTTOP), rightTop, ShadeLength).GetPoint();
		projection[PointSeq::RIGHTBOTTOM] =
			Direction(this->rect->GetPoint(PointSeq::RIGHTBOTTOM), rightBottom, ShadeLength).GetPoint();
		projection[PointSeq::LEFTBOTTOM] =
			Direction(this->rect->GetPoint(PointSeq::LEFTBOTTOM), leftBottom, ShadeLength).GetPoint();
	}

}

void Shade::SelectEdge()
{
	//Projection�� �������� �߷����� �ϴ� ����(this->rect,projection���� ���� �ϳ���) ���� ��
	//ShadeEdge�ϼ�.
	double minLength = ShadeLength * ShadeLength;
	for (int i = 0; i < 4; i++)
	{
		int odd = 3 - i;		//PointSeq ���� 3�ΰ͵��� �ִܰŸ� �ĺ�����.
		double length, x, y;
		x = this->rect->GetPOINT((PointSeq)i).x - projection[(PointSeq)odd].x;
		y = this->rect->GetPOINT((PointSeq)i).y - projection[(PointSeq)odd].y;
		length = x * x + y * y;
		if (length < minLength)
		{
			failedPoint_1 = (PointSeq)i;	//this->rect���� Ż���Ǵ� ����
			failedPoint_2 = (PointSeq)odd;	//projection���� Ż���ϴ� ����
			minLength = length;
		}
	}

	PointSeq originNext, projNext;
	shadeEdge[0] = this->rect->GetPOINT(failedPoint_2);
	shadeEdge[3] = projection[failedPoint_1];

	if (failedPoint_1 == PointSeq::LEFTTOP || failedPoint_1 == PointSeq::RIGHTBOTTOM)
	{//LeftTop : 0  RightTop : 1 LeftBottom : 2  RightBottom : 3
	//��Ģ ����ų� ã�ƺ��ٰ� �����ߴµ� �̰� ���� �����ϸ鼭 ������ ���ǰ���.
		originNext = PointSeq::RIGHTTOP;
		projNext = PointSeq::LEFTBOTTOM;
	}
	else
	{
		originNext = PointSeq::RIGHTBOTTOM;
		projNext = PointSeq::LEFTTOP;
	}

	shadeEdge[1] = this->rect->GetPOINT(originNext);
	shadeEdge[2] = projection[originNext];

	shadeEdge[4] = projection[projNext];
	shadeEdge[5] = this->rect->GetPOINT(projNext);
}

POINT Shade::Direction(POINT origin, double inclination, double length)
{
	POINT endPos;
	endPos.x = origin.x + cos(inclination) * length;
	endPos.y = origin.y + sin(inclination) * length;

	return endPos;
}

Vector2 Shade::Direction(Vector2 origin, double inclination, double length)
{
	Vector2 endPos;
	endPos.x = origin.x + cos(inclination) * length;
	endPos.y = origin.y + sin(inclination) * length;

	return endPos;
}
