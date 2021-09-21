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

void ObjManager::Collision()
{
	for (Character* character : m_Character->GetObj())
	{
		if(character != nullptr)
			character->Collision(objects);
	}

}

void ObjManager::PlusCharacter(Name name)
{
	this->objects.emplace_back(this->m_Character->PlusCharacter(name));
}

void ObjManager::PlusObstacle(Type type, Vector2 center, Vector2 size)
{
	this->objects.emplace_back(this->m_Obstacle->PlusObstacle(type, center, size));
}
