#include "Framework.h"

Goal::Goal(Character* character, Vector2 pos)
	:character(character),isMove(false),isGoback(false),times(0.0)
{
	CreateElement(character, pos);
}

Goal::Goal(Character* character, Vector2 pos,Vector2 endPos,double times, bool isMove, bool isLoop)
	:character(character),startPos(pos),isGoback(false),times(times),isLoop(isLoop),isMove(isMove)
{
	destPositions.push(endPos);
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
	goalEdge = CreatePen(PS_SOLID, 3, WHITE);

	lines.emplace_back(new Line(this->rect->LeftTopV(), this->rect->RightTopV()));
	lines.emplace_back(new Line(this->rect->RightTopV(), this->rect->RightBottomV()));
	lines.emplace_back(new Line(this->rect->RightBottomV(), this->rect->LeftBottomV()));
	lines.emplace_back(new Line(this->rect->LeftBottomV(), this->rect->LeftTopV()));
}

void Goal::Update()
{
	if (isMove == false)
		return;
	
	Move();
}

void Goal::Render(HDC hdc)
{
	HPEN temp;
	isGoal == true ? temp = (HPEN)SelectObject(hdc, goalEdge) : temp = (HPEN)SelectObject(hdc, edge);

	for (Line* line : lines)
		line->Render(hdc);

	SelectObject(hdc, temp);
}

void Goal::SetIsMove(bool value)
{
	if (destPositions.empty() == true)
		return;

	this->isMove = value;
	endPos = destPositions.front();
	destPositions.pop();
}

void Goal::Collision()
{
	Rect temp;

	if (character->GetRect()->Collision(&temp, this->GetRect()) == true)
	{
		if (temp.Area() >= this->GetRect()->Area() * 0.5)
		{
			if (isGoal == false)
				SOUND->Play("Goal_In_Sound_FX");
			
			isGoal = true;
			character->SetGoal(true);
			return;
		}
		else
		{
			if (isGoal == true)
				SOUND->Play("Goal_Out_Sound_FX");

			isGoal = false;
			character->SetGoal(false);
			return;
		}
	}
	isGoal = false;
	character->SetGoal(false);
	return;
}

void Goal::Move()
{
	if (isGoback == false)	//start -> end
	{
		Vector2 prevPos = this->rect->center;
		this->rect->center = LERP(this->rect->center, endPos, DELTA * times);
		Vector2 delta = this->rect->center - prevPos;

		for (Line* line : lines)
		{
			line->start.x += delta.x;
			line->start.y += delta.y;
			line->end.x += delta.x;
			line->end.y += delta.y;
		}
		double diff = (endPos - this->rect->center).Length();
		
		if (diff < EPSILON && isLoop == true)
			isGoback = true;
		else if (diff < EPSILON && isLoop == false)
		{
			isGoback = false;
			isMove = false;
		}
	}
	else					//end -> start
	{
		Vector2 prevPos = this->rect->center;
		this->rect->center = LERP(this->rect->center, startPos, DELTA * times);
		Vector2 delta = this->rect->center - prevPos;

		for (Line* line : lines)
		{
			line->start.x += delta.x;
			line->start.y += delta.y;
			line->end.x += delta.x;
			line->end.y += delta.y;
		}

		double diff = (startPos - this->rect->center).Length();
		if (diff < EPSILON)
			isGoback = false;

	}

}
