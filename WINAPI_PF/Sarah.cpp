#include "Framework.h"

Sarah::Sarah()
{
	CreateSarah(SARAH_START);
}

Sarah::~Sarah()
{
	delete rect;

	DeleteObject(color);
	DeleteObject(edge);

	delete anim;

}

void Sarah::CreateSarah(Vector2 pos)
{
	id = ID::CHARACTER;
	name = Name::SARAH;
	rect = new Rect(pos, SARAH_SIZE);
	color = CreateSolidBrush(SARAH_COLOR);
	edge = CreatePen(PS_SOLID, 1, SARAH_COLOR);

	speed = SPEED;
	thrust = 0;
	isActive = true;
	isJump = false;
	isDoubleJump = false;
	isFalling = true;
	gravity = GRAVITY;

	anim = new RectAnimation(this);

	{
		vector<Vector2> jump;
		jump.emplace_back(Vector2(1, 1));
		jump.emplace_back(Vector2(0.8, 1.2));
		jump.emplace_back(Vector2(0.5, 1.3));
		jump.emplace_back(Vector2(0.8, 1.2));
		jump.emplace_back(Vector2(1, 1));
		anim->SetAnim(State::JUMP, jump, 0.04);
	}

	{
		vector<Vector2> goal;
		goal.emplace_back(Vector2(1, 1));
		goal.emplace_back(Vector2(0.8, 0.8));
		goal.emplace_back(Vector2(0.6, 0.6));
		goal.emplace_back(Vector2(0.3, 0.3));
		goal.emplace_back(Vector2(0, 0));
		anim->SetAnim(State::GOAL, goal, 0.1);
	}
}

void Sarah::Update()
{
	Move();
	Jump();
	anim->Update();

	InitAgain();
}

void Sarah::Render(HDC hdc)
{
	HBRUSH tempB;
	HPEN tempP;

	if (this->isGoal == true)
	{
		tempB = (HBRUSH)SelectObject(hdc, goalColor);
		tempP = (HPEN)SelectObject(hdc, goalEdge);
	}
	else
	{
		tempB = (HBRUSH)SelectObject(hdc, color);
		tempP = (HPEN)SelectObject(hdc, edge);
	}

	anim->Render(hdc);

	SelectObject(hdc, tempB);
	SelectObject(hdc, tempP);

	PrintElement(1400);

}

void Sarah::Jump()
{//======Jump===========
	if (KEYDOWN(VK_UP) && isJump == true && isDoubleJump == false)
	{
		thrust += SARAH_THRUST;
		isDoubleJump = true;
		side[UP] = false;
		anim->SetState(State::JUMP);
	}

	if (KEYDOWN(VK_UP) && isJump == false)
	{
		thrust = SARAH_THRUST;
		isJump = true;
		side[UP] = false;
		anim->SetState(State::JUMP);
	}

	//======Falling===========
	if (isFalling == true || isJump == true || side[UP] == true || isDoubleJump == true)
	{
		thrust -= gravity * DELTA;
		this->rect->center.y -= thrust * DELTA;
	}

	//=========jumpState========
	if ((side[UP] || side[DOWN] || side[RIGHT] || side[LEFT]) == false)
		side[NONE] = true;

	if (side[NONE] == true)
	{
		isFalling = true;
		return;
	}

	if (side[UP] == true)
	{
		isJump = false;
		isDoubleJump = false;
		isFalling = false;
		thrust = 0;
	}

	if (side[DOWN] == true)
	{
		this->thrust = 0;
		isFalling = true;
	}

}

void Sarah::InitAgain()
{
	for (int i = 0; i < side.size(); i++)
		side[i] = false;
}

void Sarah::Collision(vector<T_Object*> objects)
{
	for (T_Object* object : objects)
	{
		if ((Sarah*)object == this)
			continue;

		switch (object->GetID())
		{
		case ID::CHARACTER:
			CharacterCollision(object);
			break;
		case ID::OBSTACLE:
			ObstacleCollision(object);
			break;
		case ID::GOAL:
			break;
		}
	}
}

void Sarah::CharacterCollision(T_Object* character)
{
	switch (dynamic_cast<Character*>(this)->Collision(character))
	{
	case Side::UP:
		if (dynamic_cast<Character*>(character)->GetName() == Name::LAURA)
		{
			dynamic_cast<Laura*>(character)->LauraJump(this);
			this->isDoubleJump = false;
		}
		else
			side[UP] = true;
		break;
	case Side::DOWN:
		side[DOWN] = true;
		break;
	case Side::LEFT:
		side[LEFT] = true;
	case Side::RIGHT:
		side[RIGHT] = true;
		break;
	case Side::NONE:
		break;
	}
}

void Sarah::ObstacleCollision(T_Object* obstacle)
{
	switch (dynamic_cast<Character*>(this)->Collision(obstacle))
	{
	case Side::UP:
		side[UP] = true;
		break;
	case Side::DOWN:
		side[DOWN] = true;
		break;
	case Side::LEFT:
		side[LEFT] = true;
		break;
	case Side::RIGHT:
		side[RIGHT] = true;
		break;
	case Side::NONE:
		break;
	}
}
