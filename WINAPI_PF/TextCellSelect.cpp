#include "Framework.h"

TextCellSelect::TextCellSelect(TextCell* menu)
	:menu(menu),menuIndex(0)
{
	Vector2 center = { menu->GetRect()->center.x,menu->GetYLevel()[0] };
	Vector2 size = { menu->GetRect()->size.x,menu->GetTotalHeight() };
	visualBar = new Rect(center, size);

	color = CreateSolidBrush(THOMAS_COLOR);
	edge = CreatePen(PS_SOLID, 1, THOMAS_COLOR);

}

TextCellSelect::~TextCellSelect()
{
	delete visualBar;
	DeleteObject(color);
	DeleteObject(edge);

}

void TextCellSelect::Update()
{
	Move();
	Select();
}

void TextCellSelect::Render(HDC hdc)
{
	HBRUSH oldB = (HBRUSH)SelectObject(hdc,color);
	HPEN oldP = (HPEN)SelectObject(hdc,edge);

	visualBar->Render(hdc);

	SelectObject(hdc, oldB);
	SelectObject(hdc, oldP);
}

void TextCellSelect::Select()
{
	if (KEYDOWN(VK_SPACE))
	{
		SCENE->ChangeScene(menu->GetMenu()[menuIndex]);
	}
}

void TextCellSelect::Move()
{
	if (menu->GetVerticalMove() == true)
	{
		int index = menu->GetMenuIndex();

		LERP(this->visualBar->center.y, menu->GetYLevel()[index], DELTA);

		double diff = this->visualBar->center.y - menu->GetYLevel()[index];
		if (diff * diff < EPSILON)
			menu->SetVerticalMove(false);
	}
}
