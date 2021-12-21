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

T_Object* ObstacleManager::PlusObstacle(Vector2 center, Vector2 size, bool left, bool up, bool right, bool down)
{
	SpikeObstacle* newObs = new SpikeObstacle(center, size, left, up, right, down);
	obstacles.emplace_back(newObs);
	return newObs;
}

