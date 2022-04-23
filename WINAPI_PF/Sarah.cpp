#include "Framework.h"

Sarah::Sarah()
{
	CreateSarah(SARAH_START);
}

Sarah::Sarah(Vector2 pos)
{
	CreateSarah(pos);
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
	renderRect = new Rect(pos, this->rect->size);

	color = CreateSolidBrush(SARAH_COLOR);
	edge = CreatePen(PS_SOLID, 1, SARAH_COLOR);
	spawnPoint = rect->center;

	speed = SPEED;
	thrust = 0;
	isActive = false;
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

void Sarah::Update(vector<T_Object*> obj)
{
	Move();
	InitAgain();

	Collision(obj);
	ReturnSpawnPoint();

	Jump();
	anim->Update();


	if (isActive == false)
		return;
}

void Sarah::Jump()
{//======Jump===========
	if (KEYDOWN(KEYBOARD->GetJumpKey()) && isJump == true && isDoubleJump == false && isActive == true)
	{
		SOUND->Play("Sarah_Jump_Sound_FX");
		thrust = 0;
		thrust += SARAH_THRUST;
		isDoubleJump = true;
		side[UP] = false;
		anim->SetState(State::JUMP);
	}

	if (KEYDOWN(KEYBOARD->GetJumpKey()) && isJump == false && isActive == true)
	{
		SOUND->Play("Sarah_Jump_Sound_FX");
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
	}

}
