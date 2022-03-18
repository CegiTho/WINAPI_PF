#include "Framework.h"

Trigger::Trigger()
{	
	//���� ������°͵�
	startPos = { 0,0 };
	endPos = { 0,0 };
	isGoback = false;
	isMove = false;
	isLoop = false;
	times = 0.0;
	//Obstacle ������� �����ѰŶ� �ǹ̾���

	type = Type::TRIGGER;
}

Trigger::Trigger(Character* owner, Vector2 pos)
	:owner(owner),isActive(true)
{
	//���� ������°͵�
	startPos = { 0,0 };
	endPos = { 0,0 };
	isGoback = false;
	isMove = false;
	isLoop = false;
	times = 0.0;
	//Obstacle ������� �����ѰŶ� �ǹ̾���

	type = Type::TRIGGER;

	Set(pos);
}

Trigger::~Trigger()
{
	delete rect;
	DeleteObject(color);
	DeleteObject(edge);
}

void Trigger::Set(Vector2 pos)
{
	switch (owner->GetName())
	{
	case THOMAS:
		color = CreateSolidBrush(THOMAS_COLOR);
		edge =  CreatePen(PS_SOLID,1,THOMAS_COLOR);
		break;
	case CHRIS:
		color = CreateSolidBrush(CHRIS_COLOR);
		edge = CreatePen(PS_SOLID, 1, CHRIS_COLOR);
		break;
	case CLARE:
		color = CreateSolidBrush(CLARE_COLOR);
		edge = CreatePen(PS_SOLID, 1, CLARE_COLOR);
		break;
	case JAMES:
		color = CreateSolidBrush(JAMES_COLOR);
		edge = CreatePen(PS_SOLID, 1, JAMES_COLOR);
		break;
	case JOHN:
		color = CreateSolidBrush(JOHN_COLOR);
		edge = CreatePen(PS_SOLID, 1, JOHN_COLOR);
		break;
	case LAURA:
		color = CreateSolidBrush(LAURA_COLOR);
		edge = CreatePen(PS_SOLID, 1, LAURA_COLOR);
		break;
	case SARAH:
		color = CreateSolidBrush(SARAH_COLOR);
		edge = CreatePen(PS_SOLID, 1, SARAH_COLOR);
		break;
	}

	Vector2 size = { 24,8 };
	this->rect = new Rect(pos, size);

}

void Trigger::Update()
{
	if (isActive == false)
		return;

	Collision();
}

void Trigger::Render(HDC hdc)
{
	if (isActive == false)
		return;

	HBRUSH oldB = (HBRUSH)SelectObject(hdc, color);
	HPEN oldP = (HPEN)SelectObject(hdc, edge);

	this->rect->Render(hdc);

	SelectObject(hdc, oldB);
	SelectObject(hdc, oldP);
}

void Trigger::Collision()
{
	if (this->rect->Collision(owner->GetRect()) == true)
	{
		isActive = false;
		SOUND->Play("Trigger_Active_Sound_FX");
		Active();
	}
}

void Trigger::Active()
{
	for (int i = 0; i < connectedObj.size(); i++)
	{
		T_Object* temp = connectedObj[i];
		if (temp->GetID() == ID::OBSTACLE)
			static_cast<Obstacle*>(temp)->SetIsMove(true);
		else if (temp->GetID() == ID::GOAL)
			static_cast<Goal*>(temp)->SetIsMove(true);
	}
}
