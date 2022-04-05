#pragma once

class NormalObstacle : public Obstacle
{
private:


public:
	NormalObstacle(Vector2 center,Vector2 size);
	NormalObstacle(Vector2 center,Vector2 size,Vector2 pathEnd,bool isMove,bool loop,double speed);
	~NormalObstacle();

	virtual void Update() override;
	virtual void Render(HDC hdc) override;
	virtual Rect* GetRenderRect() override { return rect; }
};



