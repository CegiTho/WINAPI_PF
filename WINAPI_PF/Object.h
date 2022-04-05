#pragma once
class Rect;
class Circle;
class Line;

class Object
{
private:


public:
	Object();
	virtual ~Object();

	virtual void Render(HDC hdc) = 0;
	virtual void Set(Vector2 center, double radius) {}

	//========Collision========
	virtual bool Collision(Vector2 pos) { return true; }			//rect,circle에만 필요함.
	virtual bool Collision(Line* line) { return true; }
	virtual bool Collision(Circle* circle) { return true; }
	virtual bool Collision(Rect* rect) { return true; }
	//========Collision========

};

