#include "Framework.h"
#include "SavePoint.h"


SavePoint::SavePoint(vector<Character*> characters, Vector2 pos, Vector2 size)
	:characters(characters),frameDelta(0.0),index(0),isReturn(false),isAnim(false)
{
	Set(pos, size);
}

SavePoint::~SavePoint()
{
	for (int i = 0; i < symbol.size(); i++)
	{
		for (Cross* c : symbol[i])
			delete c;
	}
}

void SavePoint::Set(Vector2 pos, Vector2 size)
{
	Vector2 temp = size;
	temp.y = size.y - ((int)size.y % SYMBOL_INTERVAL);
	this->rect = new Rect(pos, temp);
	this->id = ID::GOAL;

	int count = this->rect->size.y / 70;	//70은 별 생각없음 그냥 찍은숫자임

	for (int i = 0; i < count; i++)
	{
		Vector2 leftTop = this->rect->LeftTopV();
		Vector2 rightTop = this->rect->RightTopV();
		symbol[0].emplace_back(
			new Cross({ leftTop.x + SYMBOL_SIZE * 0.5,(leftTop.y + SYMBOL_SIZE * 0.5) + (SYMBOL_INTERVAL * i) + SYMBOL_SIZE * 0.5 },
			{ SYMBOL_SIZE,SYMBOL_SIZE }, WHITE));
		symbol[0].emplace_back(
			new Cross({ rightTop.x - SYMBOL_SIZE * 0.5,(rightTop.y + SYMBOL_SIZE * 0.5) + (SYMBOL_INTERVAL * i) + SYMBOL_SIZE * 0.5 },
				{ SYMBOL_SIZE,SYMBOL_SIZE }, WHITE));

		symbol[1].emplace_back(
			new Cross({ leftTop.x + SYMBOL_SIZE * 0.5,(leftTop.y + SYMBOL_SIZE * 0.5) + (SYMBOL_INTERVAL * i) + SYMBOL_SIZE * 0.5 },
				{ (SYMBOL_SIZE * 1.4),(SYMBOL_SIZE * 1.4) },2, WHITE));
		symbol[1].emplace_back(
			new Cross({ rightTop.x - SYMBOL_SIZE * 0.5,(rightTop.y + SYMBOL_SIZE * 0.5) + (SYMBOL_INTERVAL * i) + SYMBOL_SIZE * 0.5 },
				{ (SYMBOL_SIZE * 1.4),(SYMBOL_SIZE * 1.4) },2, WHITE));

		symbol[2].emplace_back(
			new Cross({ leftTop.x + SYMBOL_SIZE * 0.5,(leftTop.y + SYMBOL_SIZE * 0.5) + (SYMBOL_INTERVAL * i) + SYMBOL_SIZE * 0.5 },
				{ (SYMBOL_SIZE * 1.8),(SYMBOL_SIZE * 1.8) }, 2, WHITE));
		symbol[2].emplace_back(
			new Cross({ rightTop.x - SYMBOL_SIZE * 0.5,(rightTop.y + SYMBOL_SIZE * 0.5) + (SYMBOL_INTERVAL * i) + SYMBOL_SIZE * 0.5 },
				{ (SYMBOL_SIZE * 1.8),(SYMBOL_SIZE * 1.8) }, 2, WHITE));

		symbol[3].emplace_back(
			new Cross({ leftTop.x + SYMBOL_SIZE * 0.5,(leftTop.y + SYMBOL_SIZE * 0.5) + (SYMBOL_INTERVAL * i) + SYMBOL_SIZE * 0.5 },
				{ (SYMBOL_SIZE * 2),(SYMBOL_SIZE * 2) }, 2, WHITE));
		symbol[3].emplace_back(
			new Cross({ rightTop.x - SYMBOL_SIZE * 0.5,(rightTop.y + SYMBOL_SIZE * 0.5) + (SYMBOL_INTERVAL * i) + SYMBOL_SIZE * 0.5 },
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


