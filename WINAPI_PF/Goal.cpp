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
	
	//Render시 배경이랑 색이 맞아야 테두리만 나옴.
	//그림자도 감안해야되는데 이건 방법이 안떠오르네.
	//그림자 외곽선이랑 사각형 외곽선 충돌로 영역 특정하면 될거같은데 엄청나게 성가실거같은 느낌.
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

