#pragma once

class Cross
{
private:
	Line* horizontal;
	Line* vertical;

	Vector2 pos;
	Vector2 size;

	HPEN color;
public:
	Cross(Vector2 pos,Vector2 size,COLORREF color);
	Cross(Vector2 pos,Vector2 size,int width,COLORREF color);
	~Cross();

	void Render(HDC hdc);
};

