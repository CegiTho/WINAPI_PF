#pragma once

class ObstacleManager
{
private:
	vector<Obstacle*> obstacles;


public:
	ObstacleManager();
	~ObstacleManager();

	void Update();
	void Render(HDC hdc);
	void Render(HDC hdc, Vector2 offset);

	T_Object* PlusObstacle(Type type, Vector2 center, Vector2 size);
	void PlusObstacle(Type type, Vector2 center, Vector2 size,Vector2 pathEnd,double speed);

	vector<Obstacle*> GetObj() { return obstacles; }
};


