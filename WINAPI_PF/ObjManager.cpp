#include "Framework.h"

ObjManager::ObjManager()
{	
	m_Obstacle = new ObstacleManager();
	m_Character = new CharacterManager();
	m_Goal = new GoalManager();

}

ObjManager::~ObjManager()
{
	delete m_Obstacle;
	delete m_Character;
	delete m_Goal;
}

void ObjManager::LoadStage(STAGE_NUM num)
{
	string file;
	switch (num)
	{
	case STAGE_1:
		break;
	case STAGE_2:
		break;
	case STAGE_3:
		break;
	case STAGE_4:
		file = "Resource/Stage_4_Data.xml";
		break;
	case STAGE_5:
		break;
	}

	XmlDocument* document = new XmlDocument();
	document->LoadFile(file.c_str());

	XmlElement* stageElement	=	document->FirstChildElement("StageElement");
	XmlElement* character		=	stageElement->FirstChildElement("Character");
	XmlElement* goal			=	stageElement->FirstChildElement("Goal");
	XmlElement* obstacle		=	stageElement->FirstChildElement("Obstacle");

	int index = 0;
	int name = 0;
	Vector2 pos;
	Vector2 size;

	character = character->FirstChildElement("Thomas");
	for (; character != nullptr; character = character->NextSiblingElement())
	{
		index = character->IntAttribute("consist");
		name = character->IntAttribute("name");
		if (index != 1)
			continue;

		XmlElement* character_Pos = character->FirstChildElement();
		pos.x = character_Pos->IntAttribute("posX");
		pos.y = character_Pos->IntAttribute("posY");

		this->PlusCharacter((Name)name, pos);
	}

	index = 0;
	goal = goal->FirstChildElement("Thomas");
	for (; goal != nullptr; goal = goal->NextSiblingElement())
	{
		bool consist = goal->IntAttribute("consist");
		//m_Character->GetObj의 null 체크가 불필요할지 아닐지 모르겠음.
		if (consist != true || m_Character->GetObj()[index] == nullptr)
		{
			index++;
			continue;
		}

		XmlElement* goal_Pos = goal->FirstChildElement();
		pos.x = goal_Pos->IntAttribute("posX");
		pos.y = goal_Pos->IntAttribute("posY");

		this->PlusGoal(m_Character->GetObj()[index], pos);;
		index++;
	}

	name = 0;
	obstacle = obstacle->FirstChildElement();
	for (; obstacle != nullptr; obstacle = obstacle->NextSiblingElement())
	{
		XmlElement* type		=	obstacle->FirstChildElement("type");
		XmlElement* obs_Pos		=	obstacle->FirstChildElement("position");
		XmlElement* obs_Size	=	obstacle->FirstChildElement("size");

		name = type->IntAttribute("type");
	
		pos.x = obs_Pos->IntAttribute("posX");
		pos.y = obs_Pos->IntAttribute("posY");
		
		size.x = obs_Size->IntAttribute("sizeX");
		size.y = obs_Size->IntAttribute("sizeY");

		switch ((Type)name)
		{
		case NORMAL:
			this->PlusObstacle((Type)name, pos, size);
			break;
		case SPIKE:
			break;
		case WATER:
			break;
		}
	}
}

void ObjManager::Update()
{
	Collision();

	m_Character->Update();
	m_Obstacle->Update();
	m_Goal->Update();


}

void ObjManager::Render(HDC hdc)
{
	m_Character->Render(hdc);
	m_Obstacle->Render(hdc);
	m_Goal->Render(hdc);
}

void ObjManager::Render(HDC hdc, Vector2 offset)
{
	m_Character->Render(hdc, offset);
	m_Obstacle->Render(hdc, offset);
	m_Goal->Render(hdc, offset);

}

void ObjManager::Collision()
{
	for (Character* character : m_Character->GetObj())
	{
		if(character != nullptr)
			character->Collision(objects);
	}

}

void ObjManager::PlusCharacter(Name name,Vector2 pos)
{
	this->objects.emplace_back(this->m_Character->PlusCharacter(name,pos));
}

void ObjManager::PlusObstacle(Type type, Vector2 center, Vector2 size)
{
	this->objects.emplace_back(this->m_Obstacle->PlusObstacle(type, center, size));
}

void ObjManager::PlusGoal(Character* character, Vector2 pos)
{
	this->m_Goal->PlusGoal(character, pos);
}
