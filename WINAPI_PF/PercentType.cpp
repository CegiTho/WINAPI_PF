#include "Framework.h"

PercentType::PercentType(TextCell* menu)
{
	this->menu = menu;
	menuIndex = 0;
	isActive = false;

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

	Vector2 start, end;
	start = { visualBar->Left() - 240 , visualBar->center.y };
	end = { visualBar->Left() - 20 , visualBar->center.y };
	line = new Line(start, end);

	size = { 30,30 };
	center = { line->start.x + size.x * 0.5 , menu->GetYLevel()[0] };
	rect = new Rect(center, size);

	font = CreateFont(45, 0, 0, 0, 10, false, false, false, HANGUL_CHARSET, 100, 0, 0, 0, L"애플산돌고딕네오 굵게 TTF");

	volMem.assign(menu->GetTags().size()," 0 %");
	VolumeUpdate();
}

PercentType::~PercentType()
{
	//visualBar,triangles,color,edge는 부모클래스에서 지워짐.
	delete line;
	delete rect;

	DeleteObject(font);
}

void PercentType::Update()
{
	Move();
	if(menu->GetActive() == true)
		Select();

	if (menu->GetActive() == false && menu->GetMove() == false)
		Init();
	
	VolumeUpdate();

}

void PercentType::Render(HDC hdc)
{
	if (isActive == false)
		return;

	HBRUSH hOld = (HBRUSH)SelectObject(hdc, color);
	HPEN pOld = (HPEN)SelectObject(hdc, edge);
	HFONT fOld = (HFONT)SelectObject(hdc, font);
	COLORREF cOld = SetTextColor(hdc, THOMAS_COLOR);

	SetTextAlign(hdc, TA_CENTER);
	SetTextAlign(hdc, TA_BOTTOM);

	TextOutA(hdc, line->Center().x, line->Center().y - 30, volMem[menuIndex].c_str(), volMem[menuIndex].size());

	rect->Render(hdc);
	line->Render(hdc);
	visualBar->Render(hdc);

	SelectObject(hdc, hOld);
	SelectObject(hdc, pOld);
	SelectObject(hdc, fOld);
	SetTextColor(hdc, cOld);
}

void PercentType::Select()
{
	if (isActive == false)
		return;

	int seg = (line->end.x - line->start.x) / 10;
	int menuIndex = menu->GetMenuIndex();

	string num;

	if (volMem[menuIndex] == "100%")
		num = "100"; 
	else
		num = volMem[menuIndex].substr(0, 2);

	int vol = stoi(num);
	rect->center.x = line->Start().x + (vol * 0.1 * seg);

	if (KEYDOWN(VK_RIGHT))
	{
		if (vol == 100)
			vol = 100;
		else 
		{
			rect->center.x += seg;
			vol += 10;
			SOUND->SetVolume(menu->GetTags()[menuIndex], (float)(vol * 0.01));
		}

		num = to_string(vol);
	}
	if (KEYDOWN(VK_LEFT))
	{
		if (vol == 0)
			vol = 0;
		else
		{
			rect->center.x -= seg;
			vol -= 10;
			SOUND->SetVolume(menu->GetTags()[menuIndex], (float)(vol * 0.01));
		}
		num = to_string(vol);
	}
	volMem[menuIndex] = num + " %";
}

void PercentType::Move()
{
	menuIndex = menu->GetMenuIndex();

	this->visualBar->center.y = LERP(this->visualBar->center.y, menu->GetYLevel()[menuIndex], DELTA  *5);
	this->line->start.y = LERP(this->visualBar->center.y, menu->GetYLevel()[menuIndex], DELTA * 5);
	this->line->end.y = LERP(this->visualBar->center.y, menu->GetYLevel()[menuIndex], DELTA * 5);
	this->rect->center.y = LERP(this->visualBar->center.y, menu->GetYLevel()[menuIndex], DELTA * 5);

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
 		int delta = menu->GetRect()->center.x - this->visualBar->center.x;
		this->visualBar->center.x += delta;
		line->start.x += delta;
		line->end.x += delta;

		rect->center.x += delta;

		for(Triangle* tri : deco)
			tri->Move(delta);
	}
}

void PercentType::Init()
{
	menuIndex = 0;
	visualBar->center = { menu->GetRect()->center.x , menu->GetYLevel()[menuIndex] };
	this->line->start.y = this->visualBar->center.y, menu->GetYLevel()[menuIndex];
	this->line->end.y = this->visualBar->center.y, menu->GetYLevel()[menuIndex];
	this->rect->center.x = line->start.x + rect->size.x * 0.5;
	this->rect->center.y = this->visualBar->center.y, menu->GetYLevel()[menuIndex];

	deco[0]->GetVertices()[0].y = visualBar->center.y - offset.y;
	deco[0]->GetVertices()[1].y = deco[0]->GetVertices()[0].y - 10;
	deco[0]->GetVertices()[2].y = deco[0]->GetVertices()[0].y - 10;

	deco[1]->GetVertices()[0].y = visualBar->center.y + offset.y;
	deco[1]->GetVertices()[1].y = deco[1]->GetVertices()[0].y + 10;
	deco[1]->GetVertices()[2].y = deco[1]->GetVertices()[0].y + 10;

	deco[0]->SetRender(false);
	deco[1]->SetRender(true);


}

void PercentType::VolumeUpdate()
{
	map<CHANNEL, float> volumeTable = SOUND->GetVolume();

	for (auto volume : volumeTable)
	{
		int vol;
		switch (volume.first)
		{
		case MAIN_FX_CHANNEL:
		case SUB_FX_CHANNEL:
			vol = volume.second * 100;
			volMem[1] = to_string(vol) + "%";
			break;
		case BG_CHANNEL:			
			vol = volume.second * 100;
			volMem[2] = to_string(vol) + "%";
			break;
		
		}
	}


}
