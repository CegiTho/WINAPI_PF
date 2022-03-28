#include "Framework.h"

RectListType::RectListType(TextCell* menu)
{
	this->menu = menu;
	menuIndex = 0;
	isActive = false;

	double leftAdd = 400;
	Vector2 size = { menu->GetRect()->size.x + 40 ,
		menu->GetTotalHeight() };
	Vector2 center = { WIN_WIDTH - size.x * 0.5,
		menu->GetYLevel()[0] };
	
	visualBar = new Rect(center, size);
	leftSide = new Rect(visualBar->Left() - size.x * 0.6,visualBar->Top(),visualBar->Left(),visualBar->Bottom());

	color = CreateSolidBrush(THOMAS_COLOR);
	edge = CreatePen(PS_SOLID, 1, THOMAS_COLOR);

	stageColor = CreateSolidBrush(WHITE);
	stageEdge = CreatePen(PS_SOLID, 1, WHITE);

	offset = { visualBar->Right() - 80 - visualBar->center.x,
		visualBar->Top() - 30 - visualBar->center.y };

	Vector2 p1, p2, p3;
	p1 = visualBar->center + offset;
	p2 = { p1.x + 10 , p1.y + 10 };
	p3 = { p1.x - 10 , p1.y + 10 };
	deco.emplace_back(new Triangle(p1, p2, p3, THOMAS_COLOR));

	p1.x = visualBar->center.x + offset.x;
	p1.y = visualBar->center.y - offset.y;
	p2 = { p1.x + 10 , p1.y - 10 };
	p3 = { p1.x - 10 , p1.y - 10 };
	deco.emplace_back(new Triangle(p1, p2, p3, THOMAS_COLOR));
	deco[0]->SetRender(false);
	deco[1]->SetRender(true);

	font = CreateFont(40, 0, 0, 0, 10, false, false, false, HANGUL_CHARSET, 100, 0, 0, 0, L"애플산돌고딕네오 굵게 TTF");

	stage = 0;
	normalSize = 10;
	highlightedSize = 30;
	Vector2 start = { leftSide->Left() + 20,menu->GetYLevel()[0] };
	Vector2 period = { 40,0 };
	for (int i = 0; i < 10; i++)
		list.emplace_back(new Rect(start + period * i, { normalSize,normalSize }));

}

RectListType::~RectListType()
{
	for (Rect* rec : list)
		delete rec;

	DeleteObject(font);

}

void RectListType::Update()
{
	Move();
	if(menu->GetActive() ==true)
		Select();

	if (menu->GetActive() == false && menu->GetMove() == false)
		Init();
}

void RectListType::Render(HDC hdc)
{
	if (isActive == false)
		return;

	HBRUSH hOld = (HBRUSH)SelectObject(hdc, color);
	HPEN pOld = (HPEN)SelectObject(hdc, edge);
	HFONT fOld = (HFONT)SelectObject(hdc, font);
	COLORREF cOld = SetTextColor(hdc, THOMAS_COLOR);

	SetTextAlign(hdc, TA_LEFT);
	SetTextAlign(hdc, TA_TOP);

	TextOutA(hdc, leftSide->Left(), leftSide->Top() - 50,
		(to_string(menu->GetMenuIndex()) + "." + to_string(stage + 1)).c_str(),
		(to_string(menu->GetMenuIndex()) + "." + to_string(stage + 1)).size());

	visualBar->Render(hdc);
	leftSide->Render(hdc);

	SelectObject(hdc, stageColor);
	SelectObject(hdc, stageEdge);
	for (Rect* rec : list)
		rec->Render(hdc);

	SelectObject(hdc, hOld);
	SelectObject(hdc, pOld);
	SelectObject(hdc, fOld);
	SetTextColor(hdc, cOld);
}

void RectListType::Select()
{
	if (KEYDOWN(VK_RIGHT) && stage < 9)
	{
		list[stage]->size.x = normalSize;
		list[stage]->size.y = normalSize;
		stage++;
		list[stage]->size.x = highlightedSize;
		list[stage]->size.y = highlightedSize;
		
	}
	if (KEYDOWN(VK_LEFT) && stage > 0)
	{
		list[stage]->size.x = normalSize;
		list[stage]->size.y = normalSize;
		stage--;
		list[stage]->size.x = highlightedSize;
		list[stage]->size.y = highlightedSize;
	}

	if (KEYDOWN(VK_SPACE) && isActive == true)
	{
		int chapter = menu->GetMenuIndex();
		int stg = stage + 1;
		string scene = "Stage_" + to_string(chapter) + "-"+to_string(stg);
		SCENE->ChangeScene(scene);
	}
}

void RectListType::Move()
{
	menuIndex = menu->GetMenuIndex();

	if (menu->GetVertical() == true)
	{
		stage = 0;
		for (int i = 0; i < list.size(); i++)
		{
			if (i == 0)
			{
				list[i]->size.x = highlightedSize;
				list[i]->size.y = highlightedSize;
			}
			else
			{
				list[i]->size.x = normalSize;
				list[i]->size.y = normalSize;
			}
		}
		menu->SetVertical(false);
	}

	this->visualBar->center.y = LERP(this->visualBar->center.y, menu->GetYLevel()[menuIndex], DELTA * 5);
	this->leftSide->center.y = LERP(this->leftSide->center.y, menu->GetYLevel()[menuIndex], DELTA * 5);

	for (Rect* rec : list)
		rec->center.y = LERP(rec->center.y, menu->GetYLevel()[menuIndex], DELTA * 5);

	deco[0]->GetVertices()[0].y = visualBar->center.y - offset.y;
	deco[0]->GetVertices()[1].y = deco[0]->GetVertices()[0].y - 10;
	deco[0]->GetVertices()[2].y = deco[0]->GetVertices()[0].y - 10;

	deco[1]->GetVertices()[0].y = visualBar->center.y + offset.y;
	deco[1]->GetVertices()[1].y = deco[1]->GetVertices()[0].y + 10;
	deco[1]->GetVertices()[2].y = deco[1]->GetVertices()[0].y + 10;

	if (menuIndex == 0)
	{
		deco[0]->SetRender(true);
		deco[1]->SetRender(false);
	}
	else if (menuIndex != 0 && menuIndex != menu->GetTags().size() - 1)
	{
		deco[0]->SetRender(true);
		deco[1]->SetRender(true);
	}
	else
	{
		deco[0]->SetRender(false);
		deco[1]->SetRender(true);
	}

	if (menu->GetMove() == true)
	{
		//delta를 double로 써봤었는데 정수에서 미세하게 벗어난 n.***값에서 0.***값들때문에 의도보다 두배정도 더 움직였었음.
		int delta = menu->GetRect()->center.x - this->visualBar->center.x;
		this->visualBar->center.x += delta;
		this->leftSide->center.x += delta;
		
		for (Rect* rec : list)
			rec->center.x += delta;

		for (Triangle* tri : deco)
			tri->Move(delta);
	}
}

void RectListType::Init()
{
	menuIndex = 0;
	visualBar->center = { menu->GetRect()->center.x , menu->GetYLevel()[menuIndex] };
	leftSide->center = { visualBar->Left() - visualBar->size.x * 0.6,menu->GetYLevel()[menuIndex] };
	stage = 0;

	deco[0]->GetVertices()[0].y = visualBar->center.y - offset.y;
	deco[0]->GetVertices()[1].y = deco[0]->GetVertices()[0].y - 10;
	deco[0]->GetVertices()[2].y = deco[0]->GetVertices()[0].y - 10;

	deco[1]->GetVertices()[0].y = visualBar->center.y + offset.y;
	deco[1]->GetVertices()[1].y = deco[1]->GetVertices()[0].y + 10;
	deco[1]->GetVertices()[2].y = deco[1]->GetVertices()[0].y + 10;

	deco[0]->SetRender(false);
	deco[1]->SetRender(true);

}
