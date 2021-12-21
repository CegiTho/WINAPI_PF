#pragma once

class Obstacle : public T_Object
{
protected:
	Type type;
	bool isMove;
	Line* path;
	double speed;


public:
	Obstacle();
	virtual ~Obstacle();

	virtual void Update() = 0;
	virtual void Render(HDC hdc) = 0;
	virtual Rect* GetRenderRect() = 0;
	
	void SetIsMove(bool value) { isMove = value; }
	Type GetType() { return type; }
	void Move();

};


