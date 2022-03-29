#include "Framework.h"

Trigger::Trigger(Character* owner, Obstacle* attachedObj, bool isHori, Side side, double distance)
	:owner(owner),isActive(true),isHori(isHori)
{	
	//전부 쓸모없는것들
	destPos = { 0,0 };
	isGoback = false;
	isMove = false;
	isLoop = false;
	times = 0.0;
	//Obstacle 상속으로 땜질한거라 의미없음

	type = Type::TRIGGER;
	this->attachedObj = attachedObj;
	Vector2 size;
	size.x = isHori == true ? 25 : 11;
	size.y = isHori == true ? 11 : 25;
	if (side == RIGHT)
	{
		offset.x = attachedObj->GetRect()->size.x * 0.5 + size.x * 0.5;
		offset.y = distance;
	}
	else if (side == LEFT)
	{
		offset.x = -attachedObj->GetRect()->size.x * 0.5 - size.x * 0.5;;
		offset.y = distance;
	}
	else if (side == UP)
	{
		offset.x = distance;
		offset.y = -attachedObj->GetRect()->size.y * 0.5 - size.y * 0.5;
	}
	else
	{
		offset.x = distance;
		offset.y = attachedObj->GetRect()->size.y * 0.5 + size.y * 0.5;
	}


	Vector2 pos = owner->GetRect()->center + offset;

	rect = new Rect(pos, size);

	Set();
}

Trigger::~Trigger()
{
	delete rect;
	DeleteObject(color);
	DeleteObject(edge);
}

void Trigger::Set()
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
}

void Trigger::Update()
{
	if (isActive == false)
		return;

	rect->center = attachedObj->GetRect()->center + offset;
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


void Trigger::Active()
{
	for (int i = 0; i < connectedObj.size(); i++)
	{
		T_Object* temp = connectedObj[i];
		if (temp->GetID() == ID::OBSTACLE)
			static_cast<Obstacle*>(temp)->SetIsMove(true);
		else if (temp->GetID() == ID::GOAL)
			static_cast<Goal*>(temp)->SetIsMove(true);
	
		//Trigger는 아예 Obstacle에 붙여놔서 굳이 isMove쓸 필요 없음.
	}
}
