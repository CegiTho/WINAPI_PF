#include "Framework.h"
#include "James.h"

James::James()
{
	CreateJames(JAMES_START);

}

James::James(Vector2 pos)
{
	CreateJames(pos);
}

James::~James()
{
	delete rect;

	DeleteObject(color);
	DeleteObject(edge);

	delete anim;
}

void James::CreateJames(Vector2 pos)
{
	id = ID::CHARACTER;
	name = Name::JAMES;
	rect = new Rect(pos, JAMES_SIZE);
	color = CreateSolidBrush(JAMES_COLOR);
	edge = CreatePen(PS_SOLID, 1, JAMES_COLOR);
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

void James::Update(vector<T_Object*> obj)
{
	Collision(obj);

	Jump();
	anim->Update();
	InitAgain();
	pick->Update();

	if (isActive == false)
		return;
	Move();
}

void James::Jump()
{
	//======Jump===========
	if (KEYDOWN(VK_SPACE) && isJump == false && isActive == true)
	{
		thrust = JAMES_THRUST;
		isJump = true;
		side[DOWN] = false;
		anim->SetState(State::JUMP);
	}

	//======Falling===========
	if (isFalling == true || isJump == true || side[DOWN] == true)
	{
		thrust -= gravity * DELTA;
		this->rect->center.y += thrust * DELTA;
	}

	//=========jumpState========
	if ((side[UP] || side[DOWN] || side[RIGHT] || side[LEFT]) == false)
		side[NONE] = true;

	if (side[NONE] == true)
	{
		isFalling = true;
		return;
	}

	if (side[DOWN] == true)
	{
		isJump = false;
		isFalling = false;
		thrust = 0;
	}

	if (side[UP] == true)
	{
		this->thrust = 0;
		isFalling = true;
	}
}
