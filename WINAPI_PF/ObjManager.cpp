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

void ObjManager::ConnectToTrigger()
{
	for (auto temp : m_Obstacle->GetTriggers())
	{
		Name name = temp->GetOwner()->GetName();
		temp->AddConnect(triggerGoal[name]);
		for (auto obsList : triggerIndex)
		{
			for(auto obs : obsList.second)
				temp->AddConnect(m_Obstacle->GetObj()[obs]);
		}
	}
}
void ObjManager::PlusCharacter(Name name,Vector2 pos)
{
	this->objects.emplace_back(this->m_Character->PlusCharacter(name,pos));
}

void ObjManager::PlusTrigger(Character* owner, Vector2 center)
{
	this->objects.emplace_back(this->m_Obstacle->PlusTrigger(owner,center));
}

void ObjManager::PlusObstacle(Type type, Vector2 center, Vector2 size)
{
	this->objects.emplace_back(this->m_Obstacle->PlusObstacle((Type)type, center, size));
}

void ObjManager::PlusObstacle(Type type, Vector2 startPos, Vector2 endPos, Vector2 size, bool isMove, bool isLoop, double times)
{
	this->objects.emplace_back(this->m_Obstacle->PlusObstacle(type, startPos, endPos, size, isMove,isLoop, times));
}

void ObjManager::PlusObstacle( Vector2 center, Vector2 size, bool left, bool up, bool right, bool down)
{
	this->objects.emplace_back(this->m_Obstacle->PlusObstacle(center, size,left,up,right,down));
}

void ObjManager::PlusObstacle(Vector2 startPos, Vector2 endPos, Vector2 size, bool left, bool up, bool right, bool down,
	bool isMove, bool isLoop, double times)
{
	this->objects.emplace_back(this->m_Obstacle->PlusObstacle(startPos, endPos, size, left, up, right, down,isMove, isLoop, times));
}

void ObjManager::PlusGoal(Character* character, Vector2 pos)
{
	this->m_Goal->PlusGoal(character, pos);
}

void ObjManager::PlusGoal(Character* character, Vector2 startPos, Vector2 endPos, bool isMove, bool loop, double times)
{
	this->m_Goal->PlusGoal(character, startPos, endPos, isMove,loop, times);
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
	XmlElement* character = stageElement->FirstChildElement("Character");
	XmlElement* movingObstacle = stageElement->FirstChildElement("MoveObstacle");
	XmlElement* savePoint = stageElement->FirstChildElement("SavePoint");
	XmlElement* goal = stageElement->FirstChildElement("Goal");
	XmlElement* movingGoal = stageElement->FirstChildElement("MoveGoal");
	XmlElement* obstacle = stageElement->FirstChildElement("Obstacle");
	XmlElement* trigger = stageElement->FirstChildElement("Trigger");

	int index = 0;
	int name = 0;
	Vector2 pos;
	Vector2 size;

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

	//==========Trigger=======================
	trigger = trigger->FirstChildElement("trigger1");
	for (; trigger != nullptr; trigger = trigger->NextSiblingElement())
	{
		XmlElement* owner = trigger->FirstChildElement("Owner");
		XmlElement* position = owner->NextSiblingElement();

		index = owner->IntAttribute("owner");
		pos.x = position->IntAttribute("posX");
		pos.y = position->IntAttribute("posY");

		this->PlusTrigger(m_Character->GetObj()[index], pos);
	}

	//==========GOAL=======================(Static)
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

	//==========GOAL=======================(Moving)
	index = 0;
	movingGoal = movingGoal->FirstChildElement("Thomas");
	for (; movingGoal != nullptr; movingGoal = movingGoal->NextSiblingElement())
	{
		bool consist, isMove;
		OwnerName triggerOwner;
		consist = movingGoal->IntAttribute("consist");
		isMove = movingGoal->IntAttribute("ismove");
		triggerOwner = (OwnerName)movingGoal->IntAttribute("triggerowner");

		//m_Character->GetObj의 null 체크가 불필요할지 아닐지 모르겠음.
		if (consist != true || m_Character->GetObj()[index] == nullptr)
		{
			index++;
			continue;
		}
		bool loop = movingGoal->IntAttribute("loop");
		double times = movingGoal->DoubleAttribute("times");
		Vector2 endPos;

		XmlElement* goal_Pos = movingGoal->FirstChildElement();
		XmlElement* goal_EndPos = goal_Pos->NextSiblingElement();
		pos.x = goal_Pos->IntAttribute("posX");
		pos.y = goal_Pos->IntAttribute("posY");
		endPos.x = goal_EndPos->IntAttribute("posX");
		endPos.y = goal_EndPos->IntAttribute("posY");

		this->PlusGoal(m_Character->GetObj()[index], pos, endPos, isMove, loop, times);

		if (triggerOwner >= 0)
			triggerGoal[triggerOwner] = m_Goal->GetGoals()[index];
		index++;
	}

	//==========OBSTACLE=======================(Static)
	name = 0;
	obstacle = obstacle->FirstChildElement();
	for (; obstacle != nullptr; obstacle = obstacle->NextSiblingElement())
	{
		bool shade;
		XmlElement* type = obstacle->FirstChildElement("type");
		XmlElement* obs_Pos = obstacle->FirstChildElement("position");
		XmlElement* obs_Size = obstacle->FirstChildElement("size");

		name = type->IntAttribute("type");
		shade = type->IntAttribute("shade");

		pos.x = obs_Pos->IntAttribute("posX");
		pos.y = obs_Pos->IntAttribute("posY");

		size.x = obs_Size->IntAttribute("sizeX");
		size.y = obs_Size->IntAttribute("sizeY");

		vector<bool> side;
		side.assign(4, false);
		if (name == Type::SPIKE)
		{
			XmlElement* spikeSide = obstacle->FirstChildElement("side");
			side[Side::LEFT] = spikeSide->IntAttribute("left");
			side[Side::UP] = spikeSide->IntAttribute("top");
			side[Side::RIGHT] = spikeSide->IntAttribute("right");
			side[Side::DOWN] = spikeSide->IntAttribute("bottom");
		}

		if (shade == true)
			shadeIndex.emplace_back(this->m_Obstacle->GetObj().size());

		switch ((Type)name)
		{
		case NORMAL:
			this->PlusObstacle((Type)name, pos, size);
			break;
		case SPIKE:
			this->PlusObstacle(pos, size, side[Side::LEFT], side[Side::UP], side[Side::RIGHT], side[Side::DOWN]);
			break;
		case WATER:
			this->PlusObstacle((Type)name, pos, size);
			break;
		}
	}

	//==========OBSTACLE=======================(Moving)
	name = 0;
	movingObstacle = movingObstacle->FirstChildElement();
	for (; movingObstacle != nullptr; movingObstacle = movingObstacle->NextSiblingElement())
	{
		bool isLoop, isMove, shade;
		double times;
		Name triggerOwner;

		Vector2 endPosition;
		XmlElement* type = movingObstacle->FirstChildElement("type");
		XmlElement* start_Pos = movingObstacle->FirstChildElement("startPosition");
		XmlElement* end_Pos = movingObstacle->FirstChildElement("endPosition");
		XmlElement* obs_Size = movingObstacle->FirstChildElement("size");

		name = type->IntAttribute("type");
		isLoop = type->IntAttribute("loop");
		times = type->DoubleAttribute("times");
		isMove = type->IntAttribute("ismove");
		shade = type->IntAttribute("shade");
		triggerOwner = (Name)type->IntAttribute("triggerowner");

		pos.x = start_Pos->IntAttribute("posX");
		pos.y = start_Pos->IntAttribute("posY");
		endPosition.x = end_Pos->IntAttribute("posX");
		endPosition.y = end_Pos->IntAttribute("posY");

		size.x = obs_Size->IntAttribute("sizeX");
		size.y = obs_Size->IntAttribute("sizeY");

		vector<bool> side;
		side.assign(4, false);
		if (name == Type::SPIKE)
		{
			XmlElement* spikeSide = movingObstacle->FirstChildElement("side");
			side[Side::LEFT] = spikeSide->IntAttribute("left");
			side[Side::UP] = spikeSide->IntAttribute("top");
			side[Side::RIGHT] = spikeSide->IntAttribute("right");
			side[Side::DOWN] = spikeSide->IntAttribute("bottom");
		}

		if (shade == true)
			shadeIndex.emplace_back(this->m_Obstacle->GetObj().size());
		if (triggerOwner >= 0)
			triggerIndex[triggerOwner].emplace_back(this->m_Obstacle->GetObj().size());


		switch ((Type)name)
		{
		case NORMAL:
			this->PlusObstacle((Type)name, pos, endPosition, size, isMove, isLoop, times);
			break;
		case SPIKE:
			this->PlusObstacle(pos, endPosition, size, side[Side::LEFT], side[Side::UP], side[Side::RIGHT], side[Side::DOWN], isMove, isLoop, times);
			break;
		default:
			break;
		}

	}

	//============SAVE_POINT=====================
	if (savePoint != nullptr)
	{
		//XmlElement* savePointInfo = savePoint->FirstChildElement();
		savePoint = savePoint->FirstChildElement();
		for (; savePoint != nullptr; savePoint = savePoint->NextSiblingElement())
		{
			XmlElement* savePointInfo = savePoint->FirstChildElement();
			pos.x = savePointInfo->IntAttribute("posX");
			pos.y = savePointInfo->IntAttribute("posY");

			savePointInfo = savePointInfo->NextSiblingElement();
			size.x = savePointInfo->IntAttribute("sizeX");
			size.y = savePointInfo->IntAttribute("sizeY");

			this->GetGM()->PlusSavePoint(this->GetCM()->GetObj(), pos, size);
		}
	}

	ConnectToTrigger();
}