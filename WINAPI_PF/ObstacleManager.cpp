#include "Framework.h"

ObstacleManager::ObstacleManager()
	:obstacles{}
{
}

ObstacleManager::~ObstacleManager()
{
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
		if (obs->GetRect()->Collision(M_CAM->GetScreen()) == true)
			obs->Render(hdc);
	}
}

T_Object* ObstacleManager::PlusObstacle( Vector2 center, Vector2 size)
{
	NormalObstacle* newObs = new NormalObstacle(center, size);
	obstacles.emplace_back(newObs);
	return newObs;
}

T_Object* ObstacleManager::PlusObstacle(Vector2 center, Vector2 size, bool left, bool up, bool right, bool down)
{
	SpikeObstacle* newObs = new SpikeObstacle(center, size, left, up, right, down);
	obstacles.emplace_back(newObs);
	return newObs;
}

void ObstacleManager::PlusObstacle(Type type, Vector2 center, Vector2 size, Vector2 pathEnd, double speed)
{
	switch (type)
	{
	case Type::NORMAL:
		obstacles.emplace_back(new NormalObstacle(center, size,pathEnd,speed));
		break;
	case Type::SPIKE:
		break;
	case Type::WATER:
		break;
	default:
		break;
	}
}
