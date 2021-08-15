#include "Framework.h"

ObjManager::ObjManager()
{
	m_Obstacle = new ObstacleManager();
	m_Character = new CharacterManager();

}

ObjManager::~ObjManager()
{
	delete m_Obstacle;
	delete m_Character;
}

void ObjManager::Update()
{
	Collision();

	m_Character->Update();
	m_Obstacle->Update();
}

void ObjManager::Render(HDC hdc)
{
	m_Character->Render(hdc);
	m_Obstacle->Render(hdc);
}

void ObjManager::SetCharacter(vector<Character*> characters)
{
	for (Character* character : characters)
		this->characters.emplace_back(character);

	for (Character* character : characters)
		this->objects.emplace_back((T_Object*)character);
}

void ObjManager::SetObstacle(vector<Obstacle*> obstacles)
{
	for (Obstacle* obstacle : obstacles)
		objects.emplace_back((T_Object*)obstacle);
}

void ObjManager::Collision()
{
	for (T_Object* character : characters)
	{
		dynamic_cast<Character*>(character)->Collision(objects);
	}

}

void ObjManager::PlusCharacter(Name name)
{
	this->m_Character->PlusCharacter(name);
}

void ObjManager::PlusObstacle(Type type, Vector2 center, Vector2 size)
{
	this->m_Obstacle->PlusObstacle(type, center, size);
}
