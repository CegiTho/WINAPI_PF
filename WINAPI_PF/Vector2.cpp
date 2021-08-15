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
}//��ũ����ǥ�� y���� �Ʒ��� ���� �����ε� atan2�� y�� ���ΰ� +angle, y�� �Ʒ��� -angle�̴�.

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
