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
		obs->Render(hdc);
}

void ObstacleManager::PlusObstacle(Type type, Vector2 center, Vector2 size)
{
	switch (type)
	{
	case Type::NORMAL:
		obstacles.emplace_back(new NormalObstacle(center, size));
		break;
	case Type::SPIKE:
		break;
	case Type::WATER:
		break;
	default:
		break;
	}
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
