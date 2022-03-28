#include "Framework.h"
#include "Character.h"

Character::Character()
	:isGoal(false)
{
	side.assign(5, false);

	goalColor = CreateSolidBrush(WHITE);
	goalEdge = CreatePen(PS_SOLID, 1, WHITE);

	isPenetrated = false;
	isFloat = false;
	respawnDelay = 0.0;
}

Character::Character(Vector2 pos)
{
	side.assign(5, false);

	goalColor = CreateSolidBrush(WHITE);
	goalEdge = CreatePen(PS_SOLID, 1, WHITE);

	spawnPoint = pos;
	this->rect->center = pos;

	isPenetrated = false;
	isFloat = false;
	playOnce = false;
	respawnDelay = 0.0;
}

Character::~Character()
{
	DeleteObject(goalColor);
	DeleteObject(goalEdge);
}

void Character::Move()
{
	

	if (isActive == false)
		return;

	if (KEYPRESS(VK_RIGHT) && side[LEFT] == false)
	{
		this->rect->center.x += speed * DELTA;
	}

	if (KEYPRESS(VK_LEFT) && side[RIGHT] == false)
	{
		this->rect->center.x -= speed * DELTA;
	}

}

void Character::Render(HDC hdc)
{
	this->renderRect->center = this->rect->center;
	HBRUSH tempB;
	HPEN tempP;
	if (isGoal == true)
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
}

void Character::InitAgain()
{
	for (int i = 0; i < side.size(); i++)
		side[i] = false;
}

void Character::Collision(vector<T_Object*> objects)
{
	for (T_Object* obj : objects)    
	{
		if (static_cast<T_Object*>(this) == obj)
			continue;

		if (obj->GetRect()->Collision(this->GetRect()) == true )
		{
			switch (obj->GetID())
			{
			case ID::CHARACTER:
				CharacterCollision(static_cast<Character*>(obj));
				break;
			case ID::OBSTACLE:
				ObstacleCollision(static_cast<Obstacle*>(obj));
				break;
			}
		}

	}

}

void Character::CharacterCollision(Character* character)
{
	Rect overlap;
	
	Rect* other = character->GetRect();
	if (this->GetRect()->Collision(&overlap, other) == true)
	{
		bool isUpDown = overlap.size.x > overlap.size.y;
		if (isUpDown == true && overlap.center.y > other->center.y)
		{//down
			this->side[DOWN] = true;
			this->GetRect()->center.y += overlap.size.y;
		}
		else if (isUpDown == true && overlap.center.y < other->center.y)
		{//up
			this->GetRect()->center.y -= overlap.size.y;

			if (character->GetName() == Name::LAURA)
			{
				string tag = this->GetNameString() + "_Jump_Sound_FX";
				SOUND->Play(tag);
				dynamic_cast<Laura*>(character)->LauraJump(this);
				return;
			}
			if(this->isFalling == true)
				SOUND->Play("All_Land_Sound_FX");
			this->side[UP] = true;
		}
		else if (isUpDown == false && overlap.center.x > other->center.x)
		{//right
			this->GetRect()->center.x += overlap.size.x;
			this->side[RIGHT] = true;
		}
		else if (isUpDown == false && overlap.center.x < other->center.x)
		{//left
			this->GetRect()->center.x -= overlap.size.x;
			this->side[LEFT] = true;
		}
	}
}

void Character::ObstacleCollision(Obstacle* obstacle)
{
	switch (obstacle->GetType())
	{
	case NORMAL:
		NormalCollision(static_cast<NormalObstacle*>(obstacle));
		break;
	case SPIKE:
		SpikeCollision(static_cast<SpikeObstacle*>(obstacle));
		break;
	case WATER:
		WaterCollision(static_cast<Water*>(obstacle));
		break;
	case TRIGGER:
		if (static_cast<Trigger*>(obstacle)->GetActive() == true)
			TriggerCollision(static_cast<Trigger*>(obstacle));
	}
}

void Character::NormalCollision(NormalObstacle* obstacle)
{
	Rect overlap;

	Rect* other = obstacle->GetRect();
	if (this->GetRect()->Collision(&overlap, other) == true)
	{
		bool isUpDown = overlap.size.x > overlap.size.y;
		if (isUpDown == true && overlap.center.y > other->center.y)
		{//down
			if (this->name == JAMES && this->isFalling == true)
				SOUND->Play("All_Land_Sound_FX");
				
			this->side[DOWN] = true;
			this->GetRect()->center.y += overlap.size.y;
		}
		else if (isUpDown == true && overlap.center.y < other->center.y)
		{//up
			if (this->isFalling == true)
				SOUND->Play("All_Land_Sound_FX");

			this->GetRect()->center.y -= overlap.size.y;
			this->side[UP] = true;
		}
		else if (isUpDown == false && overlap.center.x > other->center.x)
		{//right
			this->GetRect()->center.x += overlap.size.x;
			this->side[RIGHT] = true;
		}
		else if (isUpDown == false && overlap.center.x < other->center.x)
		{//left
			this->GetRect()->center.x -= overlap.size.x;
			this->side[LEFT] = true;
		}
	}
}

void Character::SpikeCollision(SpikeObstacle* obstacle)
{
	Rect overlap;
	vector<bool> side = obstacle->GetSpikeSide();

	Rect* other = obstacle->GetRect();
	if (this->GetRect()->Collision(&overlap, other) == true)
	{
		bool isUpDown = overlap.size.x > overlap.size.y;
		if (isUpDown == true && overlap.center.y > other->center.y)
		{//down
			this->GetRect()->center.y += overlap.size.y;
			if (side[DOWN] == true)
			{
				isPenetrated = true;
				return;
			}
			this->side[DOWN] = true;
		}
		else if (isUpDown == true && overlap.center.y < other->center.y)
		{//up
			this->GetRect()->center.y -= overlap.size.y;
			if (side[UP] == true)
			{
				isPenetrated = true;
				return;
			}
			this->side[UP] = true;
		}
		else if (isUpDown == false && overlap.center.x > other->center.x)
		{//right
			this->GetRect()->center.x += overlap.size.x;
			if (side[RIGHT] == true)
			{
				isPenetrated = true;
				return;
			}
			this->side[RIGHT] = true;
		}
		else if (isUpDown == false && overlap.center.x < other->center.x)
		{//left
			this->GetRect()->center.x -= overlap.size.x;
			if (side[LEFT] == true)
			{
				isPenetrated = true;
				return;
			}
			this->side[LEFT] = true;
		}
	}

}

void Character::WaterCollision(Water* obstacle)
{
	if (this->rect->Collision(obstacle->GetRect()) == true)
	{
		isFloat = true;
	}
	if (this->name == CLARE)
		static_cast<Clare*>(this)->OnWater(obstacle);
}

void Character::TriggerCollision(Trigger* trigger)
{
	Rect overlap;

	Rect* other = trigger->GetRect();
	if (trigger->GetOwner() == this)
	{
		trigger->SetActive(false);
		SOUND->Play("Trigger_Active_Sound_FX");
		trigger->Active();
		return;
	}

	if (this->GetRect()->Collision(&overlap, other) == true)
	{
		bool isUpDown = overlap.size.x > overlap.size.y;
		if (isUpDown == true && overlap.center.y > other->center.y)
		{//down
			this->side[DOWN] = true;
			this->GetRect()->center.y += overlap.size.y;
		}
		else if (isUpDown == true && overlap.center.y < other->center.y)
		{//up
			this->GetRect()->center.y -= overlap.size.y;
			this->side[UP] = true;
		}
		else if (isUpDown == false && overlap.center.x > other->center.x)
		{//right
			this->GetRect()->center.x += overlap.size.x;
			this->side[RIGHT] = true;
		}
		else if (isUpDown == false && overlap.center.x < other->center.x)
		{//left
			this->GetRect()->center.x -= overlap.size.x;
			this->side[LEFT] = true;
		}
	}
}

void Character::ReturnSpawnPoint()
{
	if (isFloat == true || isPenetrated == true)
	{
		respawnDelay += DELTA;
		if (isFloat == true && playOnce == false)
		{
			playOnce = true;
			SOUND->Play("Water_Collision_Sound_FX");
		}
	}
	if (respawnDelay >= 0.2)
	{
		this->rect->center = spawnPoint;
		this->thrust = 0;
		respawnDelay = 0.0;
		isFloat = false;
		isPenetrated = false;
		playOnce = false;
	}
}

void Character::SetSpawnPoint(Rect* rect)
{
	this->spawnPoint = rect->Center();
}

string  Character::GetNameString()
{
	switch (this->name)
	{
	case THOMAS:
		return "Thomas";
		break;
	case CHRIS:
		return "Chris";
		break;
	case CLARE:
		return "Clare";
		break;
	case JAMES:
		return "James";
		break;
	case JOHN:
		return "John";
		break;
	case LAURA:
		return "Laura";
		break;
	case SARAH:
		return "Sarah";
		break;
	}
}




void Character::PrintElement(HDC hdc, int x)
{
	switch (name)
	{
	case THOMAS:
		PrintElement(hdc, 200);
		break;
	case CHRIS:
		PrintElement(hdc, 400);
		break;
	case CLARE:
		PrintElement(hdc, 600);
		break;
	case JAMES:
		PrintElement(hdc, 800);
		break;
	case JOHN:
		PrintElement(hdc, 1000);
		break;
	case LAURA:
		PrintElement(hdc, 1200);
		break;
	case SARAH:
		PrintElement(hdc, 1400);
		break;
	}


	wstring s_Height;
	switch (this->name)
	{
	case Name::THOMAS:
		s_Height = L"Name : THOMAS";
		TextOut(hdc, x, 0, s_Height.c_str(), s_Height.size());
		break;
	case Name::CHRIS:
		s_Height = L"Name : CHRIS";
		TextOut(hdc, x, 0, s_Height.c_str(), s_Height.size());
		break;
	case Name::CLARE:
		s_Height = L"Name : CLARE";
		TextOut(hdc, x, 0, s_Height.c_str(), s_Height.size());
		break;
	case Name::JAMES:
		s_Height = L"Name : JAMES";
		TextOut(hdc, x, 0, s_Height.c_str(), s_Height.size());
		break;
	case Name::JOHN:
		s_Height = L"Name : JOHN";
		TextOut(hdc, x, 0, s_Height.c_str(), s_Height.size());
		break;
	case Name::LAURA:
		s_Height = L"Name : LAURA";
		TextOut(hdc, x, 0, s_Height.c_str(), s_Height.size());
		break;
	case Name::SARAH:
		s_Height = L"Name : SARAH";
		TextOut(hdc, x, 0, s_Height.c_str(), s_Height.size());
		break;
	}

	double y = 15;
	double height = rect->center.y;
	s_Height = to_wstring(height);
	s_Height = L"Height : " + s_Height;
	TextOut(hdc, x, y, s_Height.c_str(), s_Height.size());
	y += 15;

	wstring s_Thrust = to_wstring(thrust);
	s_Thrust = L"Thrust : " + s_Thrust;
	TextOut(hdc, x, y, s_Thrust.c_str(), s_Thrust.size());
	y += 15;

	wstring falling = isFalling ? L"True" : L"False";
	falling = L"isFalling : " + falling;
	TextOut(hdc, x, y, falling.c_str(), falling.size());
	y += 15;

	falling = isJump ? L"True" : L"False";
	falling = L"isJump : " + falling;
	TextOut(hdc, x, y, falling.c_str(), falling.size());
	y += 15;

	falling = L"======================";



}
