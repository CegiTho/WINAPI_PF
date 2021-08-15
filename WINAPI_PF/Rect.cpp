#include "Framework.h"

Rect::Rect()
	:center(0,0),size(0,0)
{

}

Rect::Rect(Vector2 center, Vector2 size)
	: center(center), size(size)
{

}

Rect::Rect(double left, double top, double right, double bottom)
{
	SetRect(left, top, right, bottom);

}

Rect::~Rect()
{


}

void Rect::Render(HDC hdc)
{
	Rectangle(hdc,
		(int)Left(),(int)Top(),
		(int)Right(),(int)Bottom()
	);
}

bool Rect::Collision(Vector2 pos)
{
	if (pos.x > this->Left() && pos.x < this->Right() && pos.y > Top() && pos.y < Bottom())
		return true;

	return false;
}

void Rect::Set(Vector2 center, double radius)
{
	this->center = center;
	this->size = { radius,radius };
}

void Rect::SetRect(double left, double top, double right, double bottom)
{
	this->center.x = (left + right) * 0.5;
	this->center.y = (top + bottom) * 0.5;
	
	this->size = { abs(right - left) , abs(bottom - top) };
}

void Rect::SetRect(Vector2 center, Vector2 size)
{
	this->center = center;
	this->size = size;
}


bool Rect::Collision(Line* line)
{


	return false;
}

bool Rect::Collision(Circle* circle)
{
	if ((circle->Center().x > this->Left() && circle->Center().y < this->Right()) ||
		(circle->Center().y > this->Top() && circle->Center().y < this->Bottom()))
	{
		Rect temp(circle->Center(), { circle->Radius() * 2 , circle->Radius() * 2 });

		if (this->Collision(&temp) == true)
			return true;
	}
	else
	{
		vector<Vector2> points(4);
		points[0] = { this->Left() , this->Top() };
		points[1] = { this->Right() , this->Top() };
		points[2] = { this->Right() , this->Bottom() };
		points[3] = { this->Left() , this->Bottom() };
		
		for (Vector2 point : points)
		{
			if (circle->Collision(point) == true)
				return true;
		}
	}

	return false;
}

bool Rect::Collision(Rect* rect)
{
	if (this->Right() > rect->Left() && this->Left() < rect->Right())
	{
		if (this->Top() < rect->Bottom() && this->Bottom() > rect->Top())
			return true;
	}

	return false;
}

bool Rect::Collision(OUT Rect* overlap, IN Rect* rect)
{
	double left = max(rect->Left(), Left());
	double right = min(rect->Right(), Right());

	double top = max(rect->Top(), Top());
	double bottom = min(rect->Bottom(), Bottom());

	if (right - left > 0 && bottom - top > 0)
	{
		if (overlap != nullptr)
			overlap->SetRect(left, top, right, bottom);
		return true;
	}

	return false;
}

void Rect::TestMethod()
{
	


}