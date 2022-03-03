#include "Framework.h"
#include "Cross.h"

Cross::Cross(Vector2 pos, Vector2 size, COLORREF color)
	:pos(pos),size(size)
{
	this->color = CreatePen(PS_SOLID, 1, color);

	vertical = new Line({ pos.x,pos.y - (size.y * 0.5) }, { pos.x,pos.y + (size.y * 0.5) });
	horizontal = new Line({ pos.x - (size.x * 0.5),pos.y }, { pos.x + (size.x * 0.5),pos.y });
}

Cross::Cross(Vector2 pos, Vector2 size, int width, COLORREF color)
	:pos(pos), size(size)
{
	this->color = CreatePen(PS_SOLID, width, color);

	vertical = new Line({ pos.x,pos.y - (size.y * 0.5) }, { pos.x,pos.y + (size.y * 0.5) });
	horizontal = new Line({ pos.x - (size.x * 0.5),pos.y }, { pos.x + (size.x * 0.5),pos.y });
}


Cross::~Cross()
{
	delete vertical;
	delete horizontal;
}


void Cross::Render(HDC hdc)
{
	HPEN temp = (HPEN)SelectObject(hdc,this->color);
	vertical->Render(hdc);
	horizontal->Render(hdc);

	SelectObject(hdc, temp);
}
