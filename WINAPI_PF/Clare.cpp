#include "Framework.h"

Clare::Clare()
{
	CreateClare(CLARE_START);

}

Clare::Clare(Vector2 pos)
{
	CreateClare(pos);
}

Clare::~Clare()
{
	delete rect;

	DeleteObject(color);
	DeleteObject(edge);

	delete anim;
}

void Clare::CreateClare(Vector2 pos)
{
	id = ID::CHARACTER;
	name = Name::CLARE;
	rect = new Rect(pos, CLARE_SIZE);
	renderRect = new Rect(pos, this->rect->size);
	color = CreateSolidBrush(CLARE_COLOR);
	edge = CreatePen(PS_SOLID, 1, CLARE_COLOR);
	spawnPoint = rect->center;

	speed = SPEED;
	thrust = 0;
	isActive = false;
	isJump = false;
	isDoubleJump = false;
	isFalling = true;
	isEscape = false;
	gravity = GRAVITY;

	anim = new RectAnimation(this);

	{
		vector<Vector2> jump;
		jump.emplace_back(Vector2(1, 1));
		jump.emplace_back(Vector2(0.95, 0.95));
		jump.emplace_back(Vector2(0.9, 0.9));
		jump.emplace_back(Vector2(0.95, 0.95));
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

void Clare::Update(vector<T_Object*> obj)
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

void Clare::Jump()
{
	if (isFloat == false)
	{
		floatingTime = 0.0;
		if (isEscape == true)
			isEscape = false;
	}

	//======Jump===========
	if (KEYDOWN(KEYBOARD->GetJumpKey()) && isJump == false && isActive == true 
		&& isFloat == false )		
	{
		SOUND->Play("Clare_Jump_Sound_FX");
		thrust = CLARE_THRUST;
		isJump = true;
		side[UP] = false;
		anim->SetState(State::JUMP);
	}

	//=========On Water=================
	if (KEYDOWN(KEYBOARD->GetJumpKey()) == true && isActive == true && isFloat == true 
		&& isEscape == false && side[DOWN] == false)
	{//side[DOWN] == false조건은 떠있는동안 위에 다른 character있을 때 Jump하면 isEscape가 실패하면서 그대로 가라앉아버림.
		isEscape = true;
		isJump = true;
		this->thrust += CLARE_THRUST * 1.4;
	}
	isFloat = false;

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

void Clare::ReturnSpawnPoint()
{
	if (isPenetrated == true)
		respawnDelay += DELTA;

	if (respawnDelay >= 0.2)
	{
		this->rect->center = spawnPoint;
		this->thrust = 0;
		respawnDelay = 0.0;
		isPenetrated = false;
	}
}

void Clare::OnWater(Water* obs)
{
	if (floatingTime == 0.0)
	{
		this->thrust = 0;
		isJump = false;
		isFalling = false;
		isEscape = false;
		playOnce = false;

		if (playOnce == false)
		{
			SOUND->Play("Water_Collision_Sound_FX");
			playOnce = true;
		}
	}
	
	if (isEscape == true)
		return;
	isJump = false;

	this->thrust += gravity * DELTA;
	floatingTime += DELTA;

	double surfaceLevel = obs->GetRect()->Top();
	if (floatingTime > 4.0)
	{
		this->rect->center.y = surfaceLevel;
		return;
	}

	double height = 30.0;		//의미없음 
	double angular = 2 * PI * 2;	//수면에서 위치의 감쇠진동주기(1/angular sec)
	double dampTime = 0.3;		//감쇠계수(시간에 따르므로 약 dampTime sec 마다 1/exp만큼 감쇠)
	double damp = -height * exp(-floatingTime * 0.8) * cos(angular * floatingTime);
	
	this->rect->center.y = surfaceLevel + damp;
	
}
