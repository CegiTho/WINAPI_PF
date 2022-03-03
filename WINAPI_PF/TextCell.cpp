#include "Framework.h"


TextCell::TextCell(vector<string> menu)
	:menu(menu), isMove(false), isHided(true), isActive(false), fontHeight(40), ascent(30), decent(30), menuIndex(0)
{
	font = CreateFont(fontHeight, 0, 0, 0, 10, false, false, false, HANGUL_CHARSET, 100, 0, 0, 0, L"¾ÖÇÃ»êµ¹°íµñ³×¿À ±½°Ô TTF");
	test = CreatePen(PS_SOLID, 1, GREEN);

	Vector2 menuStart, menuSize;
	menuStart.x = WIN_WIDTH - MENUCELL_SIZE_X;
	menuStart.y = WIN_HEIGHT - (menu.size() * fontHeight) - (menu.size() * ascent) - (menu.size() * decent);

	menuSize.x = MENUCELL_SIZE_X;
	menuSize.y = menu.size() * (fontHeight + ascent + decent);

	
	activePos = { menuStart.x + menuSize.x * 0.5,menuStart.y + menuSize.y * 0.5 };
	hidedPos.x = activePos.x + menuSize.x;
	hidedPos.y = activePos.y;
	targetPos = activePos;

	rect = new Rect(activePos, menuSize);

	for (int i = 0; i < menu.size(); i++)
	{
		yLevel.emplace_back(menuStart.y + (fontHeight * 0.5) + ascent * (i + 1) + decent * i);
	}

	{//for test
		for (int i = 0; i < menu.size(); i++)
		{
			testLine.emplace_back(new Line({ rect->Left(),yLevel[i] }, { rect->Right(), yLevel[i] }));
		}
		testLine.emplace_back(new Line(rect->LeftTopV(), rect->RightTopV()));
		testLine.emplace_back(new Line(rect->LeftTopV(), rect->LeftBottomV()));
		testLine.emplace_back(new Line(rect->RightTopV(), rect->RightBottomV()));
		testLine.emplace_back(new Line(rect->LeftBottomV(), rect->RightBottomV()));
	}
}

TextCell::~TextCell()
{
	delete rect;
	DeleteObject(font);
	DeleteObject(test);
	for (Line* line : testLine)
		delete line;
}

void TextCell::Update()
{
	if (isMove == true)
	{
		HoriMove();
	}
	else if(isMove == false && isActive == true)
	{
		VertMove();
	}
}

void TextCell::Render(HDC hdc)
{
	HFONT oldFont = (HFONT)SelectObject(hdc, font);
	COLORREF oldColor = SetTextColor(hdc, THOMAS_COLOR);
	HPEN oldPen = (HPEN)SelectObject(hdc, test);
	
	for (int i = 0; i < menu.size(); i++)
	{
		SetTextAlign(hdc, TA_TOP);
		SetTextAlign(hdc, TA_LEFT);

		TextOutA(hdc, rect->Left(), yLevel[i] - fontHeight * 0.5,menu[i].c_str(),menu[i].size());
	}

	for (Line* line : testLine)
		line->Render(hdc);

	SelectObject(hdc, oldPen);
	SelectObject(hdc, oldPen);
	SetTextColor(hdc, oldColor);
}

void TextCell::HoriMove()
{
	if (isActive == true)//Active -> Hide
		Hide();
	else				 //Hide -> Active
		Out();
}

void TextCell::VertMove()
{
	if (KEYDOWN(VK_UP))
	{
		menuIndex = menuIndex == 0 ? 0 : ++menuIndex;
		targetPos.y += fontHeight;
		isVerticalMove = true;
	}
	if (KEYDOWN(VK_DOWN))
	{
		menuIndex = menuIndex == menu.size() - 1 ? menu.size() - 1 : --menuIndex;
		targetPos.y -= fontHeight;
		isVerticalMove = true;
	}

	LERP(rect->center, targetPos, DELTA);
	for (int i = 0; i < yLevel.size(); i++)
	{
		LERP(yLevel[i], targetPos.y, DELTA);
	}
}

void TextCell::Hide()
{
	LERP(rect->center, hidedPos, DELTA);
	Vector2 diff = hidedPos - rect->center;
	if (diff.Length() < EPSILON)
	{
		isActive = false;
		isHided = true;
		isMove = false;
	}
}

void TextCell::Out()
{
	LERP(rect->center, activePos, 0.4);
	Vector2 diff = activePos - rect->center;
	if (diff.Length() < EPSILON)
	{
		isActive = true;
		isHided = false;
		isMove = false;
	}
}
