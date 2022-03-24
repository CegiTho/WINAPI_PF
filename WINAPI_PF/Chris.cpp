#include "Framework.h"

Chris::Chris()
{
	CreateChris(CHRIS_START);

}

Chris::Chris(Vector2 pos)
{
	CreateChris(pos);
}

Chris::~Chris()
{
	delete rect;
	delete pick;

	DeleteObject(color);
	DeleteObject(edge);

	delete anim;
}

void Chris::CreateChris(Vector2 pos)
{
	id = ID::CHARACTER;
	name = Name::CHRIS;
	rect = new Rect(pos, CHRIS_SIZE);
	color = CreateSolidBrush(CHRIS_COLOR);
	edge = CreatePen(PS_SOLID, 1, CHRIS_COLOR);
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

	{
		pick = new Polygon2(this->GetRect());
	}

}

void Chris::Update(vector<T_Object*> obj)
{
	Move();

	Collision(obj);
	ReturnSpawnPoint();
	Jump();
	anim->Update();

	InitAgain();
	pick->Update();

	if (isActive == false)
		return;

}

void Chris::Jump()
{
	//======Jump===========
	if (KEYDOWN(KEYBOARD->GetJumpKey()) && isJump == false && isActive == true)
	{
		SOUND->Play("Chris_Jump_Sound_FX");
		thrust = CHRIS_THRUST;
		isJump = true;
		side[UP] = false;
		anim->SetState(State::JUMP);
	}

	//======Falling===========
	if (isFalling == true || isJump == true || side[UP] == true)
	{
		thrust -= gravity * DELTA;
		this->rect->center.y -= thrust * DELTA;
	}

	//=========jumpState========
	if (side[UP] == false && side[DOWN] == false && side[RIGHT] == false && side[LEFT] == false)
		side[NONE] = true;

	if (side[NONE] == true)
	{
		isFalling = true;
		return;
	}

	if (side[UP] == true)
	{
		isJump = false;
		isFalling = false;
		thrust = 0;
	}
	if (side[DOWN] == true)
	{
		this->thrust = 0;
		//isFalling = true;
	}
}

