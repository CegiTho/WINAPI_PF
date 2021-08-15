#pragma once

class Circle : public Object
{
public:
	Vector2 center;
	double radius;




	Circle();
	Circle(Vector2 center,double radius);
	~Circle();

	virtual void Render(HDC hdc) override;
	virtual void Set(Vector2 center, double radius) override;

	void SetCenter(Vector2 pos) { this->center = pos; }
	void SetRadius(double rad) { this->radius = rad; }

	double Left() { return center.x - radius; }
	double Right() { return center.x + radius; }
	double Top() { return center.y - radius; }
	double Bottom() { return center.y + radius; }
	Vector2 Center() { return center; }
	double Radius() { return radius; }

	virtual bool Collision(Vector2 pos) override;
	virtual bool Collision(Line* line) override;
	virtual bool Collision(Circle* circle) override;
	virtual bool Collision(Rect* rect) override;

};
