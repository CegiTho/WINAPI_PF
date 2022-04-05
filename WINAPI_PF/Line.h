#pragma once
class Circle;
class Rect;

class Line : public Object
{
public:
	Vector2 start;
	Vector2 end;



	Line();
	Line(Vector2 start,Vector2 end);
	~Line();

	virtual void Render(HDC hdc) override;
	virtual bool Collision(Line* line) override;
	virtual bool Collision(Circle* circle) override;
	virtual bool Collision(Rect* rect) override;

	bool Intersection(OUT Vector2& intersection, IN Line* line);

	bool IsBetween(Line* line);
	
	double Length() { return (end - start).Length(); }
	Vector2& Start() { return start; }
	Vector2& End() { return end; }

	Vector2 Center() { return { (start.x + end.x) / 2,(start.y + end.y) / 2 }; }
};

