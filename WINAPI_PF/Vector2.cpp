#include "Framework.h"

Vector2::Vector2()
	:x(0),y(0)
{
}

Vector2::Vector2(double x, double y)
	:x(x),y(y)
{
}

Vector2::~Vector2()
{
}

double Vector2::Cross(const Vector2& value) const
{
	return x * value.y - y * value.x;
}

double Vector2::Dot(const Vector2& value) const
{
	return (x * value.y - y * value.x);
}

double Vector2::Length() const
{
	return sqrt(x * x + y * y);
}

double Vector2::SqrtLength() const
{
	return x * x + y * y;
}

double Vector2::Angle() const
{
	return atan2(-y, x);		
}//스크린좌표는 y축이 아래가 양의 방향인데 atan2는 y축 위로가 +angle, y축 아래는 -angle이다.

Vector2 Vector2::Normal() const
{
	double length = this->Length();
	return Vector2(x/length , y/length);
}

void Vector2::Normalize()
{
	double length = this->Length();
	this->x /= length;
	this->y /= length;
}
