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

void ObjManager::Update()
{
	m_Obstacle->Update();
	m_Character->Update(objects);
	m_Goal->Update();
}

void ObjManager::Render(HDC hdc)
{
	m_Character->Render(hdc);
	m_Obstacle->Render(hdc);
	m_Goal->Render(hdc);
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
	m_Goal->SetNowStage(num);

	XmlDocument* document = new XmlDocument();
	document->LoadFile(file.c_str());

	XmlElement* stageElement = document->FirstChildElement("StageElement");

	LoadCharacter(stageElement);
	LoadObstacle(stageElement);
	LoadGoal(stageElement);

	ConnectToTrigger();
}

void ObjManager::ConnectToTrigger()
{
	for (int i = 0; i < m_Obstacle->GetTriggers().size(); i++)
	{
		vector<Trigger*> triggers = m_Obstacle->GetTriggers();
		for (int temp : triggerAndObstacle[i])
			triggers[i]->AddConnect(this->m_Obstacle->GetObj()[temp]);

		triggers[i]->AddConnect(triggerAndGoal[i]);
	}
}

void ObjManager::LoadCharacter(XmlElement* stageData)
{
	XmlElement* character = stageData->FirstChildElement("Character");
	int index = 0;
	int name = 0;
	Vector2 pos;

	//==========CHARACTER=======================
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
}

void ObjManager::LoadObstacle(XmlElement* stageData)
{
	XmlElement* obstacle = stageData->FirstChildElement("Obstacle");
	XmlElement* trigger = stageData->FirstChildElement("Trigger");

	obstacle = obstacle->FirstChildElement("obs1");
	for (; obstacle != nullptr; obstacle = obstacle->NextSiblingElement())
	{
		int type, triggerIndex;
		double times;
		bool isMove, isLoop, isShade, isStatic;
		Vector2 startPos, endPos, size;

		XmlElement* data = obstacle->FirstChildElement("basic_element");
		type = data->IntAttribute("type");
		isShade = data->IntAttribute("shade");
		isStatic = data->IntAttribute("isstatic");

		data = data->NextSiblingElement("move_info");

		if (isStatic == false)
		{
			isMove = data->IntAttribute("ismove");
			isLoop = data->IntAttribute("isLoop");
			triggerIndex = data->IntAttribute("trigger_index");
			times = data->DoubleAttribute("times");
		}

		data = data->NextSiblingElement("position");
		startPos.x = data->IntAttribute("posX");
		startPos.y = data->IntAttribute("posY");
		
		data = data->NextSiblingElement("end_position");
		endPos.x = data->IntAttribute("posX");
		endPos.y = data->IntAttribute("posY");
		
		data = data->NextSiblingElement("size");
		size.x = data->IntAttribute("sizeX");
		size.y = data->IntAttribute("sizeY");
		
		data = data->NextSiblingElement("side");
		vector<bool> side;
		side.assign(4, false);
		if (type == Type::SPIKE)
		{
			side[Side::LEFT] = data->IntAttribute("left");
			side[Side::UP] = data->IntAttribute("top");
			side[Side::RIGHT] = data->IntAttribute("right");
			side[Side::DOWN] = data->IntAttribute("bottom");
		}

		if (isShade == true)
			shadeIndex.emplace_back(this->m_Obstacle->GetObj().size());
		if (isStatic == false && triggerIndex >= 0)
			triggerAndObstacle[triggerIndex].emplace_back(this->m_Obstacle->GetObj().size());

		switch (type)
		{
		case NORMAL:
		{
			if (isStatic == false)
				this->PlusObstacle((Type)type, startPos, endPos, size, isMove, isLoop, times);
			else
				this->PlusObstacle((Type)type, startPos, size);
		}
			break;
		case SPIKE:
		{
			if (isStatic == false)
				this->PlusObstacle(startPos, endPos, size, side[LEFT], side[UP], side[RIGHT], side[DOWN], isMove, isLoop, times);
			else
				this->PlusObstacle(startPos, size, side[LEFT], side[UP], side[RIGHT], side[DOWN]);
		}
			break;
		case WATER:
			this->PlusObstacle((Type)type, startPos, size);
			break;
		}
	}

	trigger = trigger->FirstChildElement("trigger1");
	Name owner;
	Vector2 pos;
	for (; trigger != nullptr; trigger = trigger->NextSiblingElement())
	{

		XmlElement* data = trigger->FirstChildElement("owner");
		owner = (Name)data->IntAttribute("owner");
		
		data = data->NextSiblingElement();
		pos.x = data->IntAttribute("posX");
		pos.y = data->IntAttribute("posY");

		this->PlusTrigger(m_Character->GetObj()[owner], pos);
	}
}

void ObjManager::LoadGoal(XmlElement* stageData)
{
	//============== Goal =====================================
	XmlElement* goal = stageData->FirstChildElement("Goal");
	int charIndex = 0;
	goal = goal->FirstChildElement("Thomas");
	for (; goal != nullptr; goal = goal->NextSiblingElement())
	{
		bool consist, isStatic, isMove, isLoop;
		double times;
		int triggerIndex;
		Vector2 startPos, endPos;

		XmlElement* data = goal->FirstChildElement("basic_element");
		consist = data->IntAttribute("consist");
		isStatic = data->IntAttribute("isstatic");

		if (consist == false)
		{
			charIndex++;
			continue;
		}

		data = data->NextSiblingElement("move_info");
		if (isStatic == false)
		{
			isMove = data->IntAttribute("ismove");
			isLoop = data->IntAttribute("isloop");
			times = data->DoubleAttribute("times");
			triggerIndex = data->IntAttribute("trigger_index");
		}

		data = data->NextSiblingElement("position");
		startPos.x = data->IntAttribute("posX");
		startPos.y = data->IntAttribute("posY");

		data = data->NextSiblingElement("end_position");
		endPos.x = data->IntAttribute("posX");
		endPos.y = data->IntAttribute("posY");

		if (isStatic == true)
			this->PlusGoal(m_Character->GetObj()[charIndex], startPos);
		else
			this->PlusGoal(m_Character->GetObj()[charIndex], startPos, endPos, isMove, isLoop, times);

		if (triggerIndex >= 0 && isStatic == false)
			triggerAndGoal[triggerIndex] = m_Goal->GetGoals()[charIndex];

		charIndex++;
	}

	//==============Save Point=====================================
	XmlElement* savePoint = stageData->FirstChildElement("SavePoint");

	savePoint = savePoint->FirstChildElement("SavePoint_1");
	for (; savePoint != nullptr; savePoint = savePoint->NextSiblingElement())
	{
		XmlElement* data = savePoint->FirstChildElement("position");
		Vector2 pos, size;
		pos.x = data->IntAttribute("posX");
		pos.y = data->IntAttribute("posY");
	
		data = data->NextSiblingElement("size");
		size.x = data->IntAttribute("sizeX");
		size.y = data->IntAttribute("sizeY");

		this->GetGM()->PlusSavePoint(this->GetCM()->GetObj(), pos, size);
	}
}




void ObjManager::PlusCharacter(Name name, Vector2 pos)
{
	this->objects.emplace_back(this->m_Character->PlusCharacter(name, pos));
}

void ObjManager::PlusTrigger(Character* owner, Vector2 center)
{
	this->objects.emplace_back(this->m_Obstacle->PlusTrigger(owner, center));
}

void ObjManager::PlusObstacle(Type type, Vector2 center, Vector2 size)
{
	this->objects.emplace_back(this->m_Obstacle->PlusObstacle((Type)type, center, size));
}

void ObjManager::PlusObstacle(Type type, Vector2 startPos, Vector2 endPos, Vector2 size, bool isMove, bool isLoop, double times)
{
	this->objects.emplace_back(this->m_Obstacle->PlusObstacle(type, startPos, endPos, size, isMove, isLoop, times));
}

void ObjManager::PlusObstacle(Vector2 center, Vector2 size, bool left, bool up, bool right, bool down)
{
	this->objects.emplace_back(this->m_Obstacle->PlusObstacle(center, size, left, up, right, down));
}

void ObjManager::PlusObstacle(Vector2 startPos, Vector2 endPos, Vector2 size, bool left, bool up, bool right, bool down,
	bool isMove, bool isLoop, double times)
{
	this->objects.emplace_back(this->m_Obstacle->PlusObstacle(startPos, endPos, size, left, up, right, down, isMove, isLoop, times));
}

void ObjManager::PlusGoal(Character* character, Vector2 pos)
{
	this->m_Goal->PlusGoal(character, pos);
}

void ObjManager::PlusGoal(Character* character, Vector2 startPos, Vector2 endPos, bool isMove, bool loop, double times)
{
	this->m_Goal->PlusGoal(character, startPos, endPos, isMove, loop, times);
}

