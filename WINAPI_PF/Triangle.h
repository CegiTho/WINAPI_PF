#pragma once

class Triangle
{
private:
	POINT* vertices;

	HBRUSH color;
	HPEN edge;

	bool isRender;
public:
	Triangle(Vector2 xPoint, int yValue, COLORREF color);
	Triangle(Vector2 p1, Vector2 p2, Vector2 p3, COLORREF color);
	~Triangle();

	void Render(HDC hdc);
	void Move(int deltaX = 0, int deltaY = 0);

	bool GetRender() { return isRender; }
	void SetRender(bool value) { isRender = value; }

	POINT* GetVertices() { return vertices; }
};
