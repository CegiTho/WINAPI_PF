#include "Framework.h"

TextCellSelect::TextCellSelect(TextCell* menu)
	:menu(menu),menuIndex(0),isActive(false)
{
	Vector2 center = { menu->GetRect()->center.x,
		menu->GetYLevel()[0] };
	Vector2 size = { menu->GetRect()->size.x + 40,
		menu->GetTotalHeight() };
	
	visualBar = new Rect(center, size);

	color = CreateSolidBrush(THOMAS_COLOR);
	edge = CreatePen(PS_SOLID, 1, THOMAS_COLOR);

	offset = { visualBar->Right() - 80 - visualBar->center.x,
		visualBar->Top() - 30 - visualBar->center.y };
	
	Vector2 p1, p2, p3;
	p1 =  visualBar->center + offset;
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
}

TextCellSelect::~TextCellSelect()
{
	if (isActive == false)
		return;

	delete visualBar;
	DeleteObject(color);
	DeleteObject(edge);

	for (Triangle* tri : deco)
		delete tri;
}

void TextCellSelect::Update()
{
	Move();
	if(menu->GetActive() == true)
		Select();

	if (menu->GetActive() == false && menu->GetMove() == false)
		Init();
}

void TextCellSelect::Render(HDC hdc)
{
	HBRUSH oldB = (HBRUSH)SelectObject(hdc,color);
	HPEN oldP = (HPEN)SelectObject(hdc,edge);

	visualBar->Render(hdc);

	for(Triangle* tri : deco)
		tri->Render(hdc);

	SelectObject(hdc, oldB);
	SelectObject(hdc, oldP);
}

void TextCellSelect::Select()
{
	if (KEYDOWN(VK_SPACE))
	{
		if (menu->GetTags()[menuIndex] == "Exit")
		{
			PostQuitMessage(0);
			return;
		}

		SCENE->ChangeScene(menu->GetTags()[menuIndex]);
	}
}

void TextCellSelect::Move()
{
	menuIndex = menu->GetMenuIndex();

	this->visualBar->center.y = LERP(this->visualBar->center.y, menu->GetYLevel()[menuIndex], DELTA  *5);
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
	else if(menuIndex != 0 && menuIndex != menu->GetTags().size() -1)
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
 		int delta = menu->GetRect()->center.x - 
			this->visualBar->center.x;
		this->visualBar->center.x += delta;
		
		for(Triangle* tri : deco)
			tri->Move(delta);
	}
}

void TextCellSelect::Init()
{
	menuIndex = 0;
	visualBar->center = { menu->GetRect()->center.x , menu->GetYLevel()[menuIndex] };

	deco[0]->GetVertices()[0].y = visualBar->center.y - offset.y;
	deco[0]->GetVertices()[1].y = deco[0]->GetVertices()[0].y - 10;
	deco[0]->GetVertices()[2].y = deco[0]->GetVertices()[0].y - 10;

	deco[1]->GetVertices()[0].y = visualBar->center.y + offset.y;
	deco[1]->GetVertices()[1].y = deco[1]->GetVertices()[0].y + 10;
	deco[1]->GetVertices()[2].y = deco[1]->GetVertices()[0].y + 10;

	deco[0]->SetRender(false);
	deco[1]->SetRender(true);
}
