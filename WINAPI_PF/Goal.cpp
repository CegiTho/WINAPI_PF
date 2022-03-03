#include "Framework.h"

Goal::Goal(Character* character, Vector2 pos)
	:character(character)
{
	CreateElement(character, pos);
}

Goal::~Goal()
{
	delete rect;

	for (Line* line : lines)
		delete line;

	DeleteObject(color);
	DeleteObject(edge);

}

void Goal::CreateElement(Character* character, Vector2 pos)
{
	this->id = ID::GOAL;
	this->rect = new Rect(pos, character->GetRect()->size);
	this->name = character->GetName();
	isGoal = false;

	edge = CreatePen(PS_SOLID, 1, WHITE);
	goalEdge = CreatePen(PS_SOLID, 2, WHITE);

	lines.emplace_back(new Line(this->rect->LeftTopV(), this->rect->RightTopV()));
	lines.emplace_back(new Line(this->rect->RightTopV(), this->rect->RightBottomV()));
	lines.emplace_back(new Line(this->rect->RightBottomV(), this->rect->LeftBottomV()));
	lines.emplace_back(new Line(this->rect->LeftBottomV(), this->rect->LeftTopV()));
}

void Goal::Render(HDC hdc)
{
	HPEN temp;
	isGoal == true ? temp = (HPEN)SelectObject(hdc, goalEdge) : temp = (HPEN)SelectObject(hdc, edge);

	isGoal = false;

	for (Line* line : lines)
		line->Render(hdc);

	SelectObject(hdc, temp);
}

void Goal::Collision()
{
	Rect temp;

	if (character->GetRect()->Collision(&temp, this->GetRect()) == true)
	{
		if (temp.Area() >= this->GetRect()->Area() * 0.7)
		{
			isGoal = true;
			character->SetGoal(true);
			return;
		}
		else
		{
			isGoal = false;
			character->SetGoal(false);
			return;
		}

	}
	
	isGoal = false;
	character->SetGoal(false);
}
