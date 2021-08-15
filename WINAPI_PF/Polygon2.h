#pragma once


class Polygon2 : public Object
{
private:
	vector<Vector2*> vertices;
	Rect* rect;

	POINT* points;



public:
	Polygon2(vector<Vector2*> vertices);
	Polygon2(Rect* rect);
	~Polygon2();

	virtual void Render(HDC hdc) override;
	void Update();

	void SetArr();

	virtual bool Collision(Line* line) override;
	virtual bool Collision(Circle* circle) override;
	virtual bool Collision(Rect* rect) override;

};

