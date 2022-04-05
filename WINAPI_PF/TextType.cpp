#include "Framework.h"

TextType::TextType(TextCell* menu)
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

	font = CreateFont(50, 0, 0, 0, 10, false, false, false, HANGUL_CHARSET, 100, 0, 0, 0, L"애플산돌고딕네오 굵게 TTF");

	//key를 vector말고 map에 담아놓는거? map<string,UCHAR> tag랑 UCHAR
	for (int i = 0; i < menu->GetTags().size(); i++)
		key[menu->GetTags()[i]] = ' ';

	key["Jump"] = KEYBOARD->GetJumpKey();
	key["Next Character"] = KEYBOARD->GetNextCharKey();
	key["Prev Character"] = KEYBOARD->GetPrevCharKey();

}

TextType::~TextType()
{
	DeleteObject(font);
}

void TextType::Update()
{

	Move();
	if(menu->GetActive() ==true)
		Select();

	if (menu->GetActive() == false && menu->GetMove() == false)
		Init();
}

void TextType::Render(HDC hdc)
{
	if (isActive == false)
		return;

	HBRUSH oldB = (HBRUSH)SelectObject(hdc, color);
	HPEN oldP = (HPEN)SelectObject(hdc, edge);
	HFONT oldF = (HFONT)SelectObject(hdc, font);
	COLORREF oldC = SetTextColor(hdc, THOMAS_COLOR);

	visualBar->Render(hdc);

	string now = menu->GetTags()[menuIndex];
	string temp;
	char k = key[now];
	if (k == VK_SPACE)//그냥 두면 공백으로 나와서 입력을 시각적으로 확인할 방법이 없음
		temp = "SPACE";
	else
		temp.insert(0,1,k);

	SetTextAlign(hdc, TA_LEFT);
	SetTextAlign(hdc, TA_TOP);
	TextOutA(hdc, menu->GetRect()->Left() - 500, menu->GetYLevel()[menuIndex] - 25,
		(now + " : " + temp).c_str(),(now + " : " +temp).size());

	for (Triangle* tri : deco)
		tri->Render(hdc);

	SelectObject(hdc, oldB);
	SelectObject(hdc, oldP);
	SelectObject(hdc, oldF);
	SetTextColor(hdc, oldC);
}

void TextType::Select()
{
	string now = menu->GetTags()[menuIndex];

	//처음에 출력 안되는 이유.
	//key가 전부 ""으로 초기화되어있고 아래 조건문은 해당 메뉴단계에서 입력이 있어야 비로소 key[menuIndex]에 
	//"~~ : *"이렇게 입력이 들어감.
	if (KEYBOARD->GetConfirm() == true && (now == "Jump" || now == "Next Character" || now == "Prev Character") )
	{
		char temp = KEYBOARD->GetKey();
		if (temp == VK_UP || temp == VK_DOWN)
		{//UP,DOWN키는 UI조작키라서 설정에서 제외해야함.
			KEYBOARD->SetConfirm(false);
			return;
		}
		string k(1,temp);

		if (now == "Jump")
		{
			KEYBOARD->SetJumpKey(temp);
			//VK_UP은 Vertical Move때문에 안넣었음.
			if (KEYBOARD->GetJumpKey() == VK_SPACE)
				key[now] = VK_SPACE;
			else
				key[now] = temp;
		}
		else if (now == "Next Character")
		{
			KEYBOARD->SetNextKey(temp);
			key[now] = temp;
		}
		else if (now == "Prev Character")
		{
			KEYBOARD->SetPrevKey(temp);
			key[now] = temp;
		}
		KEYBOARD->SetConfirm(false);
	}
}

void TextType::Move()
{
	menuIndex = menu->GetMenuIndex();

	this->visualBar->center.y = LERP(this->visualBar->center.y, menu->GetYLevel()[menuIndex], DELTA * 5);
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

		for (Triangle* tri : deco)
			tri->Move(delta);
	}
}

void TextType::Init()
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
