#include "Framework.h"

ObstacleManager::ObstacleManager()
	:obstacles{}
{
	
}

ObstacleManager::~ObstacleManager()
{
	for (Obstacle* obs : obstacles)
		delete obs;
}

void ObstacleManager::Update()
{
	for (Obstacle* obs : obstacles)
		obs->Update();

}

void ObstacleManager::Render(HDC hdc)
{
	for (Obstacle* obs : obstacles)
	{
		obs->Render(hdc);
	}

}

T_Object* ObstacleManager::PlusTrigger(Character* owner, Vector2 center,bool isHori)
{
	Trigger* temp = new Trigger(owner, center,isHori);
	obstacles.emplace_back(temp);
	triggers.emplace_back(temp);
	return temp;
}

T_Object* ObstacleManager::PlusObstacle(Type type, Vector2 center, Vector2 size)
{
	switch (type)
	{
		case NORMAL:
		{
			NormalObstacle* normalObs = new NormalObstacle(center, size);
			obstacles.emplace_back(normalObs);
			return normalObs;
		}
		case WATER:
		{
			Water* waterObs = new Water(center, size);
			obstacles.emplace_back(waterObs);
			return waterObs;
		}
	}
}

T_Object* ObstacleManager::PlusObstacle(Type type, Vector2 startPos, Vector2 endPos, Vector2 size, bool isMove, bool isLoop, double times)
{
	//Water는 움직일 이유가 없어서 삭제.
	NormalObstacle* normalObs = new NormalObstacle(startPos, size,endPos,isMove,isLoop,times);
	obstacles.emplace_back(normalObs);
	return normalObs;
	
}

T_Object* ObstacleManager::PlusObstacle(Vector2 center, Vector2 size, bool left, bool up, bool right, bool down)
{
	SpikeObstacle* newObs = new SpikeObstacle(center, size, left, up, right, down);
	obstacles.emplace_back(newObs);
	return newObs;
}

T_Object* ObstacleManager::PlusObstacle(Vector2 startPos, Vector2 endPos, Vector2 size, bool left, bool up, bool right, bool down,
	bool isMove, bool isLoop, double times)
{
	SpikeObstacle* newObs = new SpikeObstacle(startPos, size, endPos, times,isMove, isLoop, left, up, right, down);
	obstacles.emplace_back(newObs);
	return newObs;
}

