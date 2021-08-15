#include "Framework.h"

ShadeManager::ShadeManager(STAGE_NUM num, Vector2 lSource)
	:constant(0)
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

	DeleteObject(alphaMemDC);
	DeleteObject(alphaBitmap);

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

	AlphaRender();
}

void ShadeManager::Render(HDC hdc)
{
	BitBlt(hdc, 0, 0, WIN_WIDTH, WIN_HEIGHT,
		alphaMemDC, 0, 0, SRCCOPY);
}

void ShadeManager::AlphaRender()
{
	PatBlt(alphaMemDC, 0, 0, WIN_WIDTH, WIN_HEIGHT, PATCOPY);
	PatBlt(memDC, 0, 0, WIN_WIDTH, WIN_HEIGHT, PATCOPY);

	for (Shade* s : shade)
	{
		s->Render(memDC);
	}

	blendFunc.SourceConstantAlpha = SHADE_ALPHA;
	
	GdiAlphaBlend(alphaMemDC, 0, 0, WIN_WIDTH, WIN_HEIGHT,
		memDC, 0, 0, WIN_WIDTH, WIN_HEIGHT,
		blendFunc);
	//AlphaBlend에서 지금같은 경우 기본 비트맵 위에 알파채널이 있는 비트맵을 덫씌우는 방식임.
	//따라서 Dest.rgb = Src.rgb * (alpha/255) + Dest.rgb{1-(alpha/255)}의
	//계산식으로 rgb값이 변함. GdiAlphaBlend함수사용으로 거의 프레임이 50넘게 떨어지는중인데
	//정 안되면 배경색 입력해서 그림자색을 산수로 계산하게 만들어야함
}

void ShadeManager::SetShade(T_Object* objects)
{
	if (lSource == nullptr)
		shade.emplace_back(new Shade(objects, constant));
	else
		shade.emplace_back(new Shade(objects, lSource));
}

void ShadeManager::CreateAlphaDC(STAGE_NUM num)
{
	HDC hdc = GetDC(hWnd);
	memDC = CreateCompatibleDC(hdc);
	bitmap = CreateCompatibleBitmap(hdc, WIN_WIDTH, WIN_HEIGHT);
	SelectObject(memDC, bitmap);

	alphaMemDC = CreateCompatibleDC(hdc);
	alphaBitmap = CreateCompatibleBitmap(hdc, WIN_WIDTH, WIN_HEIGHT);
	SelectObject(alphaMemDC, alphaBitmap);

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

	SelectObject(alphaMemDC, stageColor);
	SelectObject(memDC, stageColor);
}