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

	T_Object* PlusObstacle(Type type, Vector2 center, Vector2 size);
	T_Object* PlusObstacle(Vector2 center, Vector2 size,bool left , bool up , bool right,bool down);

	vector<Obstacle*> GetObj() { return obstacles; }
};


