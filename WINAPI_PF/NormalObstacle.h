#pragma once

class NormalObstacle : public Obstacle
{
private:


public:
	NormalObstacle(Vector2 center,Vector2 size);
	NormalObstacle(Vector2 center,Vector2 size,Vector2 pathEnd,double speed);
	~NormalObstacle();

	virtual void Update() override;
	virtual void Render(HDC hdc) override;
};



