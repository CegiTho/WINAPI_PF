#pragma once

class ObstacleManager
{
private:
	vector<Obstacle*> obstacles;
	vector<Trigger*> triggers;

public:
	ObstacleManager();
	~ObstacleManager();

	void Update();
	void Render(HDC hdc);

	T_Object* PlusTrigger(Character* owner,Vector2 center,bool isHori);
	T_Object* PlusObstacle(Type type, Vector2 center, Vector2 size);
	T_Object* PlusObstacle(Type type, Vector2 startPos,Vector2 endPos, Vector2 size, bool isMove, bool isLoop,double times);
	T_Object* PlusObstacle(Vector2 center, Vector2 size,bool left , bool up , bool right,bool down);
	T_Object* PlusObstacle(Vector2 startPos,Vector2 endPos, Vector2 size,bool left , bool up , bool right,bool down, 
		bool isMove, bool isLoop,double times);

	vector<Obstacle*> GetObj() { return obstacles; }
	vector<Trigger*> GetTriggers() { return triggers; }
};


