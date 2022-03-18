#include "Framework.h"


TextCell::TextCell(vector<string> renderMenu, vector<string> tags)
	:renderMenu(renderMenu), isMove(false), isActive(false), fontHeight(40), ascent(13), decent(13), menuIndex(0),isEnd(false),
	tags(tags)
{
	font = CreateFont(fontHeight, 0, 0, 0, 10, false, false, 
		false, HANGUL_CHARSET, 100, 0, 0, 0,
		L"¾ÖÇÃ»êµ¹°íµñ³×¿À ±½°Ô TTF");

	Vector2 menuStart, menuSize;
	menuStart.x = WIN_WIDTH - MENUCELL_SIZE_X;
	menuStart.y = WIN_HEIGHT *0.8- (renderMenu.size() * fontHeight) - (renderMenu.size() * ascent) - (renderMenu.size() * decent);

	menuSize.x = MENUCELL_SIZE_X;
	menuSize.y = renderMenu.size() * (fontHeight + ascent + decent);

	
	activePos = { menuStart.x + menuSize.x * 0.5,menuStart.y + menuSize.y * 0.5 };
	hidedPos.x = activePos.x + menuSize.x  + 100;
	hidedPos.y = activePos.y;
	targetPos = activePos;

	rect = new Rect(hidedPos, menuSize);

	for (int i = 0; i < renderMenu.size(); i++)
	{
		yLevel.emplace_back(menuStart.y + (fontHeight * 0.5) + ascent * (i + 1) + decent * i + (fontHeight * i));
	}

	
}

TextCell::~TextCell()
{
	delete rect;
	DeleteObject(font);
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
	
	for (int i = 0; i < renderMenu.size(); i++)
	{
		SetTextAlign(hdc, TA_TOP);
		SetTextAlign(hdc, TA_LEFT);

		if(menuIndex != i)
			TextOutA(hdc, rect->Left(), yLevel[i] - fontHeight * 0.5, renderMenu[i].c_str(), renderMenu[i].size());
		else
		{
			SetTextColor(hdc, WHITE);
			TextOutA(hdc, rect->Left(), yLevel[i] - fontHeight * 0.5, renderMenu[i].c_str(), renderMenu[i].size());
			SetTextColor(hdc, THOMAS_COLOR);
		}
	}

	SelectObject(hdc, oldFont);
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
		menuIndex--;
		isVerticalMove = true;
		if (menuIndex < 0)
		{
			menuIndex = 0;
			return;
		}
		menuIndex = menuIndex < 0 ? 0 : menuIndex;

		targetPos.y += fontHeight;
		//activePos.y += fontHeight;
		//hidedPos.y += fontHeight;
	}
	if (KEYDOWN(VK_DOWN))
	{
		menuIndex++;
		isVerticalMove = true;
		if (menuIndex == renderMenu.size())
		{
			menuIndex = renderMenu.size() - 1;
			return;
		}
		menuIndex = menuIndex > renderMenu.size() - 1 ? renderMenu.size() - 1 : menuIndex;
		targetPos.y -= fontHeight;
		//activePos.y -= fontHeight;
		//hidedPos.y -= fontHeight;
	}
	
	{
		double dist = targetPos.y - rect->center.y;
		rect->center = LERP(rect->center, targetPos, DELTA * 10);
		activePos.y = LERP(activePos.y, targetPos.y, DELTA * 10);
		hidedPos.y = LERP(hidedPos.y, targetPos.y, DELTA * 10);
		for (int i = 0; i < yLevel.size(); i++)
		{
			yLevel[i] = LERP(yLevel[i], yLevel[i] + dist, DELTA * 10);
		}
	}
}

void TextCell::Hide()
{
	rect->center.x = LERP(rect->center.x, hidedPos.x, DELTA * 6);
	Vector2 diff = hidedPos - rect->center;
	if (diff.Length() <= EPSILON)
	{
		Init();
	}
}

void TextCell::Out()
{
	rect->center.x = LERP(rect->center.x, activePos.x, DELTA * 6);
	Vector2 diff = activePos - rect->center;
	if (diff.Length() <= EPSILON)
	{
		isActive = true;
		isMove = false;
		isEnd = false;
	}
}

void TextCell::Init()
{
	for (int i = 0; i < menuIndex; i++)
	{
		activePos.y -= fontHeight;
		hidedPos.y -= fontHeight;
		
		for (double d : yLevel)
		{
			d -= fontHeight;
		}
	}
	targetPos = activePos;
	isActive = false;
	isMove = false;
	isEnd = false;
	menuIndex = 0;
	rect->center = hidedPos;
}