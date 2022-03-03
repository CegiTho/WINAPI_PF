#pragma once

class Vector2
{
public:
	double x;
	double y;




public:
	Vector2();
	Vector2(double x, double y);
	~Vector2();

	
	//============수학적으로는 틀린 정의들(편의용)================
	Vector2 operator*(const Vector2& value) const
	{
		return Vector2(x * value.x, y * value.y);
	}
	Vector2 operator/(const Vector2& value) const
	{
		return Vector2(x / value.x, y / value.y);
	}
	Vector2 operator+(const double& value) const
	{
		return Vector2(x + value, y + value);
	}
	Vector2 operator-(const double& value) const
	{
		return Vector2(x - value, y - value);
	}
	//============수학적으로는 틀린 정의들(편의용)================


	Vector2 operator+(const Vector2& value) const
	{
		return Vector2(x + value.x, y + value.y);
	}
	Vector2 operator-(const Vector2& value) const
	{
		return Vector2(x - value.x, y - value.y);
	}
	Vector2 operator*(const double& value) const
	{
		return Vector2(x * value, y * value);
	}
	Vector2 operator/(const double& value) const
	{
		return Vector2(x / value, y / value);
	}

	void operator+=(const Vector2& value)
	{
		x += value.x;
		y += value.y;
	}
	void operator-=(const Vector2& value)
	{
		x -= value.x;
		y -= value.y;
	}
	void operator*=(const Vector2& value)
	{
		x *= value.x;
		y *= value.y;
	}
	void operator/=(const Vector2& value)
	{
		x /= value.x;
		y /= value.y;
	}
	void operator*=(const double& value)
	{
		x *= value;
		y *= value;
	}
	void operator/=(const double& value)
	{
		x /= value;
		y /= value;
	}

	bool operator==(const Vector2& value)
	{
		return (x == value.x && y == value.y) ? true : false;
	}

	bool operator!=(const Vector2& value)
	{
		return (x != value.x || y != value.y) ? true : false;
	}

	double Cross(const Vector2& value) const;
	double Dot(const Vector2& value) const;
	double Length() const;
	double SqrtLength() const;
	double Angle() const;
	Vector2 Normal() const;
	void Normalize();


};
