#include "Framework.h"

Goal::Goal(Character* character, Vector2 pos, STAGE_NUM stage)
	:character(character)
{
	CreateElement(character, pos,stage);
}

Goal::~Goal()
{
}

void Goal::CreateElement(Character* character, Vector2 pos, STAGE_NUM stage)
{
	this->id = ID::GOAL;
	this->rect = new Rect(pos, character->GetRect()->size);
	this->name = character->GetName();
	isGoal = false;

	edge = CreatePen(PS_SOLID, 1, WHITE);

	lines.emplace_back(new Line(this->rect->LeftTopV(), this->rect->RightTopV()));
	lines.emplace_back(new Line(this->rect->RightTopV(), this->rect->RightBottomV()));
	lines.emplace_back(new Line(this->rect->RightBottomV(), this->rect->LeftBottomV()));
	lines.emplace_back(new Line(this->rect->LeftBottomV(), this->rect->LeftTopV()));
}

void Goal::Update()
{
	Collision();

}

void Goal::Render(HDC hdc)
{
	HPEN temp = (HPEN)SelectObject(hdc, edge);
	for (Line* line : lines)
		line->Render(hdc);

	SelectObject(hdc, temp);
}

void Goal::Collision()
{
	Rect temp;

	if (character->GetRect()->Collision(this->GetRect(), &temp) == true)
	{
		if (temp.Area() >= this->GetRect()->Area() * 0.7)
		{
			isGoal = true;
		}
	}
	else
		isGoal = false;

}

