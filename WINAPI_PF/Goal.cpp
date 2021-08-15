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
	
	//Render�� ����̶� ���� �¾ƾ� �׵θ��� ����.
	//�׸��ڵ� �����ؾߵǴµ� �̰� ����� �ȶ�������.
	//�׸��� �ܰ����̶� �簢�� �ܰ��� �浹�� ���� Ư���ϸ� �ɰŰ����� ��û���� �����ǰŰ��� ����.
	switch (stage)
	{
	case STAGE_1:
		color = CreateSolidBrush(BG_COLOR_1);
		break;
	case STAGE_2:
		color = CreateSolidBrush(BG_COLOR_2);
		break;
	case STAGE_3:
		color = CreateSolidBrush(BG_COLOR_3);
		break;
	case STAGE_4:
		color = CreateSolidBrush(BG_COLOR_4);
		break;
	case STAGE_5:
		color = CreateSolidBrush(BG_COLOR_5);
		break;
	}
	

}

void Goal::Update()
{
	Collision();

}

void Goal::Render(HDC hdc)
{
	HBRUSH prevBrush = (HBRUSH)SelectObject(hdc, color);
	HPEN prevPen = (HPEN)SelectObject(hdc, edge);

	rect->Render(hdc);

	SelectObject(hdc, prevBrush);
	SelectObject(hdc, prevPen);
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

