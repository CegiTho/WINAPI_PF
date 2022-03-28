#pragma once

#define FAR_AWAY {10000,10000}

class Obstacle : public T_Object
{
protected:
	Type type;

	Vector2 startPos;
	Vector2 destPos;
	queue<Vector2> endPositions;
	bool isGoback;
	bool isMove;
	bool isLoop;
	double times;


public:
	Obstacle();
	virtual ~Obstacle();

	virtual void Update() = 0;
	virtual void Render(HDC hdc) = 0;
	virtual Rect* GetRenderRect() = 0;
	
	void SetIsMove(bool value);
	Type GetType() { return type; }

	void AddEndPos(Vector2 endPos) { endPositions.push(endPos); }
	
	virtual void Move();

};


