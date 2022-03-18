#include "Framework.h"
#include "SavePoint.h"


SavePoint::SavePoint(vector<Character*> characters, Vector2 pos, Vector2 size)
	:characters(characters),frameDelta(0.0),index(0),isReturn(false),isAnim(false)
{
	Set(pos, size);

	test.emplace_back(new Line(this->rect->LeftTopV(), this->rect->RightTopV()));
	test.emplace_back(new Line(this->rect->RightTopV(), this->rect->RightBottomV()));
	test.emplace_back(new Line(this->rect->RightBottomV(), this->rect->LeftBottomV()));
	test.emplace_back(new Line(this->rect->LeftBottomV(), this->rect->LeftTopV()));
	testP = CreatePen(PS_SOLID, 1, GREEN);
}

SavePoint::~SavePoint()
{
	for (int i = 0; i < symbol.size(); i++)
	{
		for (Cross* c : symbol[i])
			delete c;
	}

	for (Line* l : test)
		delete l;
	DeleteObject(testP);
}

void SavePoint::Set(Vector2 pos, Vector2 size)
{
	Vector2 temp = size;
	int count = temp.y / 100;	//70은 별 생각없음 그냥 찍은숫자임
	int inverval = temp.y / count;

	temp.y = size.y - ((int)size.y % inverval);
	this->rect = new Rect(pos, temp);
	this->id = ID::GOAL;
	for (int i = 0; i < count; i++)
	{
		Vector2 leftTop = this->rect->LeftTopV();
		Vector2 rightTop = this->rect->RightTopV();
		symbol[0].emplace_back(
			new Cross({ leftTop.x + SYMBOL_SIZE * 0.5,(leftTop.y + SYMBOL_SIZE * 0.5) + (inverval * i) + SYMBOL_SIZE * 0.5 },
			{ SYMBOL_SIZE,SYMBOL_SIZE }, WHITE));
		symbol[0].emplace_back(
			new Cross({ rightTop.x - SYMBOL_SIZE * 0.5,(rightTop.y + SYMBOL_SIZE * 0.5) + (inverval * i) + SYMBOL_SIZE * 0.5 },
				{ SYMBOL_SIZE,SYMBOL_SIZE }, WHITE));

		symbol[1].emplace_back(
			new Cross({ leftTop.x + SYMBOL_SIZE * 0.5,(leftTop.y + SYMBOL_SIZE * 0.5) + (inverval * i) + SYMBOL_SIZE * 0.5 },
				{ (SYMBOL_SIZE * 1.4),(SYMBOL_SIZE * 1.4) },2, WHITE));
		symbol[1].emplace_back(
			new Cross({ rightTop.x - SYMBOL_SIZE * 0.5,(rightTop.y + SYMBOL_SIZE * 0.5) + (inverval * i) + SYMBOL_SIZE * 0.5 },
				{ (SYMBOL_SIZE * 1.4),(SYMBOL_SIZE * 1.4) },2, WHITE));

		symbol[2].emplace_back(
			new Cross({ leftTop.x + SYMBOL_SIZE * 0.5,(leftTop.y + SYMBOL_SIZE * 0.5) + (inverval * i) + SYMBOL_SIZE * 0.5 },
				{ (SYMBOL_SIZE * 1.8),(SYMBOL_SIZE * 1.8) }, 2, WHITE));
		symbol[2].emplace_back(
			new Cross({ rightTop.x - SYMBOL_SIZE * 0.5,(rightTop.y + SYMBOL_SIZE * 0.5) + (inverval * i) + SYMBOL_SIZE * 0.5 },
				{ (SYMBOL_SIZE * 1.8),(SYMBOL_SIZE * 1.8) }, 2, WHITE));

		symbol[3].emplace_back(
			new Cross({ leftTop.x + SYMBOL_SIZE * 0.5,(leftTop.y + SYMBOL_SIZE * 0.5) + (inverval * i) + SYMBOL_SIZE * 0.5 },
				{ (SYMBOL_SIZE * 2),(SYMBOL_SIZE * 2) }, 2, WHITE));
		symbol[3].emplace_back(
			new Cross({ rightTop.x - SYMBOL_SIZE * 0.5,(rightTop.y + SYMBOL_SIZE * 0.5) + (inverval * i) + SYMBOL_SIZE * 0.5 },
				{ (SYMBOL_SIZE * 2),(SYMBOL_SIZE * 2) }, 2, WHITE));
	}
}

void SavePoint::Update()
{
	Collision();
	if (isAnim == true)
		PlayCollision();
}

void SavePoint::Render(HDC hdc)
{
	for (Cross* symb : symbol[index])
		symb->Render(hdc);

	HPEN old = (HPEN)SelectObject(hdc, testP);
	for (Line* l : test)
		l->Render(hdc);
	SelectObject(hdc, old);
}

void SavePoint::Collision()
{
	for (Character* character : characters)
	{
		if (character == nullptr)
			continue;

		Rect* rect = this->GetRect();
		if (character->GetRect()->Collision(rect) == true)
		{
			if (character->GetSpawnPoint() != rect->Center())
			{
				SOUND->Play("Save_Point_In_FX");
				character->SetSpawnPoint(rect);
				isAnim = true;
			}
		}
	}
}

void SavePoint::PlayCollision()
{
	frameDelta += DELTA;
	if (frameDelta >= 0.04)
	{
		if (index == symbol.size() - 1)
			isReturn = true;
		index = isReturn == true ? --index : ++index;

		frameDelta = 0.0;

		if (index == 0)
		{
			isAnim = false;
			isReturn = false;
		}
	}
}


