#include "Framework.h"

ShadeManager::ShadeManager(STAGE_NUM num, Vector2 lSource)
	:constant(0),stage(num)
{
	this->lSource = new Vector2(lSource.x, lSource.y);

	
	CreateAlphaDC(num);
}

ShadeManager::ShadeManager(STAGE_NUM num, double constant)
	:constant(constant),lSource(nullptr)
{
	CreateAlphaDC(num);

}

ShadeManager::~ShadeManager()
{
	DeleteObject(memDC);
	DeleteObject(bitmap);

	DeleteObject(stageColor);

	if (lSource != nullptr)
		delete lSource;
}

void ShadeManager::Update()
{
	for (Shade* s : shade)
	{
		s->Update();
	}
}

void ShadeManager::Render(HDC hdc)
{
	PatBlt(memDC, 0, 0, WIN_WIDTH, WIN_HEIGHT, PATCOPY);

	for (Shade* s : shade)
	{
		s->Render(memDC);
	}

	BitBlt(hdc, 0, 0, WIN_WIDTH, WIN_HEIGHT,
		memDC, 0, 0, SRCCOPY);
}

void ShadeManager::SetShade(T_Object* objects)
{
	if (lSource == nullptr)
		shade.emplace_back(new Shade(objects, constant,stage));
	else
		shade.emplace_back(new Shade(objects, lSource, stage));
}

void ShadeManager::CreateAlphaDC(STAGE_NUM num)
{
	HDC hdc = GetDC(hWnd);
	memDC = CreateCompatibleDC(hdc);
	bitmap = CreateCompatibleBitmap(hdc, WIN_WIDTH, WIN_HEIGHT);
	SelectObject(memDC, bitmap);

	ReleaseDC(hWnd, hdc);

	switch (num)
	{
	case STAGE_1:
		stageColor = CreateSolidBrush(BG_COLOR_1);
		break;
	case STAGE_2:
		stageColor = CreateSolidBrush(BG_COLOR_2);
		break;
	case STAGE_3:
		stageColor = CreateSolidBrush(BG_COLOR_3);
		break;
	case STAGE_4:
		stageColor = CreateSolidBrush(BG_COLOR_4);
		break;
	case STAGE_5:
		stageColor = CreateSolidBrush(BG_COLOR_5);
		break;
	}

	SelectObject(memDC, stageColor);
}