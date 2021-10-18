#include "Framework.h"
#include "Character.h"

Character::Character()
	:isGoal(false)
{
	side.assign(5, false);

	goalColor = CreateSolidBrush(WHITE);
	goalEdge = CreatePen(PS_SOLID, 1, WHITE);

}

Character::Character(Vector2 pos)
{
	side.assign(5, false);

	goalColor = CreateSolidBrush(WHITE);
	goalEdge = CreatePen(PS_SOLID, 1, WHITE);

	this->rect->center = pos;
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

	if (KEYPRESS(VK_RIGHT))
	{
		rect->center.x += speed * DELTA;

	}

	if (KEYPRESS(VK_LEFT))
	{
		rect->center.x -= speed * DELTA;

	}

}

void Character::PrintElement(int x)
{
	wstring s_Height;
	switch (this->name)
	{
	case Name::THOMAS:
		s_Height = L"Name : THOMAS";
		TextOut(Program::backBuffer, x, 0, s_Height.c_str(), s_Height.size());
		break;
	case Name::CHRIS:
		s_Height = L"Name : CHRIS";
		TextOut(Program::backBuffer, x, 0, s_Height.c_str(), s_Height.size());
		break;
	case Name::CLARE:
		s_Height = L"Name : CLARE";
		TextOut(Program::backBuffer, x, 0, s_Height.c_str(), s_Height.size());
		break;
	case Name::JAMES:
		s_Height = L"Name : JAMES";
		TextOut(Program::backBuffer, x, 0, s_Height.c_str(), s_Height.size());
		break;
	case Name::JOHN:
		s_Height = L"Name : JOHN";
		TextOut(Program::backBuffer, x, 0, s_Height.c_str(), s_Height.size());
		break;
	case Name::LAURA:
		s_Height = L"Name : LAURA";
		TextOut(Program::backBuffer, x, 0, s_Height.c_str(), s_Height.size());
		break;
	case Name::SARAH:
		s_Height = L"Name : SARAH";
		TextOut(Program::backBuffer, x, 0, s_Height.c_str(), s_Height.size());
		break;
	}

	double y = 15;
	double height = rect->center.y;
	s_Height = to_wstring(height);
	s_Height = L"Height : " + s_Height;
	TextOut(Program::backBuffer, x, y, s_Height.c_str(), s_Height.size());
	y += 15;

	wstring s_Thrust = to_wstring(thrust);
	s_Thrust = L"Thrust : " + s_Thrust;
	TextOut(Program::backBuffer, x, y, s_Thrust.c_str(), s_Thrust.size());
	y += 15;

	wstring falling = isFalling ? L"True" : L"False";
	falling = L"isFalling : " + falling;
	TextOut(Program::backBuffer, x, y, falling.c_str(), falling.size());
	y += 15;

	falling = isJump ? L"True" : L"False";
	falling = L"isJump : " + falling;
	TextOut(Program::backBuffer, x, y, falling.c_str(), falling.size());
	y += 15;

	falling = L"======================";
	


} 

Side Character::Collision(T_Object* obj)
{
	Rect overlap;
	
	if (this->GetRect()->Collision(&overlap, obj->GetRect()) == true)
	{
		if (overlap.size.x > overlap.size.y)	//상하충돌
		{
			if (this->GetRect()->center.y > obj->GetRect()->center.y)
			{

				this->GetRect()->center.y += overlap.size.y;
				return Side::DOWN;
			}
			else
			{
				this->GetRect()->center.y -= overlap.size.y;
				return Side::UP;
			}
		}
		else
		{
			if (this->GetRect()->center.x > obj->GetRect()->center.x)
			{
				this->GetRect()->center.x += overlap.size.x;
				return Side::RIGHT;
			}
			else
			{
				this->GetRect()->center.x -= overlap.size.x;
				return Side::LEFT;
			}
		}
	}
	return Side::NONE;
}

void Character::Render(HDC hdc)
{
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

	switch (name)
	{
	case THOMAS:
		PrintElement(200);
		break;
	case CHRIS:
		PrintElement(400);
		break;
	case CLARE:
		PrintElement(600);
		break;
	case JAMES:
		PrintElement(800);
		break;
	case JOHN:
		PrintElement(1000);
		break;
	case LAURA:
		PrintElement(1200);
		break;
	case SARAH:
		PrintElement(1400);
		break;
	}

}
