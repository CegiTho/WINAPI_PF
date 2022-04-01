#include "Framework.h"

ObjManager::ObjManager()
{	
	m_Obstacle = new ObstacleManager();
	m_Character = new CharacterManager();
	m_Goal = new GoalManager();

}

ObjManager::ObjManager(STAGE_NUM num)
{
	m_Obstacle = new ObstacleManager();
	m_Character = new CharacterManager();
	m_Goal = new GoalManager();

	LoadStage(num);
}

ObjManager::ObjManager(Scene* owner, STAGE_NUM num)
{
	m_Obstacle = new ObstacleManager();
	m_Character = new CharacterManager();
	m_Goal = new GoalManager();

	this->owner = owner;

	LoadStage(num);
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

void ObjManager::StartSet()
{
	Character* activeCharacter = nullptr;
	vector<Character*> characters =this->m_Character->GetObj();
	for (Character* character : characters)
	{
		if (character != nullptr)
		{
			activeCharacter = character;
			break;
		}
	}
	M_CAM->TargetChange(activeCharacter);
	m_Character->SetCharacterActive(activeCharacter->GetName(), true);
}

void ObjManager::LoadStage(STAGE_NUM num)
{
	string file;
	switch (num)
	{
	case STAGE_1:
		file = "Resource/Stage_1_Data.xml";
		break;
	case STAGE_2:
		file = "Resource/Stage_2_Data.xml";
		break;
	case STAGE_3:		
		file = "Resource/Stage_3_Data.xml";
		break;
	case STAGE_4:
		file = "Resource/Stage_4_Data.xml";
		break;
	case STAGE_5:
		break;
	}
	m_Goal->SetNowStage(num);

	XmlDocument* document = new XmlDocument();
	XmlError err;
	err = document->LoadFile(file.c_str());
	if (err != XmlError::XML_SUCCESS)
		assert(0);

	XmlElement* stageElement = document->FirstChildElement("StageElement");
	bool success = stageElement->IntAttribute("success");
	if (success != true)
		assert(0);

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
		vector<int> obstacleIndices = triggerAndObstacle[i];
		for (int index : obstacleIndices)
			triggers[i]->AddConnect(m_Obstacle->GetObj()[index]);
	
		for (auto goal : triggerAndGoal[i])
			triggers[i]->AddConnect(goal);
	}

	triggerAndGoal.clear();
	triggerAndObstacle.clear();
}

void ObjManager::LoadCharacter(XmlElement* stageData)
{
	XmlElement* character = stageData->FirstChildElement("Character");
	int consist = 100;
	int errCheck = 100;
	int name = 100;
	Vector2 pos;

	//consist = character->IntAttribute("errc");
	//==========CHARACTER=======================
	XmlElement* characterData;
	characterData = character->FirstChildElement("Thomas");
	for (; characterData != nullptr; characterData = characterData->NextSiblingElement())
	{
		XmlElement* data = characterData->FirstChildElement("basic_element");
		consist = data->IntAttribute("consist");
		name = data->IntAttribute("name");
		if (consist != 1)
			continue;

		XmlElement* character_Pos = data->NextSiblingElement();
		pos.x = character_Pos->IntAttribute("posX");
		pos.y = character_Pos->IntAttribute("posY");

		this->PlusCharacter((Name)name, pos);
	}
}

void ObjManager::LoadObstacle(XmlElement* stageData)
{
	XmlElement* obstacle = stageData->FirstChildElement("Obstacle");
	XmlElement* trigger = stageData->FirstChildElement("Trigger");

	obstacle = obstacle->FirstChildElement("obs0");
	for (; obstacle != nullptr; obstacle = obstacle->NextSiblingElement())
	{
		int type, triggerIndex;
		double times;
		bool isMove, isLoop, isShade, isStatic;
		Vector2 startPos, destPos, size;

		XmlElement* data = obstacle->FirstChildElement("basic_element");
		type = data->IntAttribute("type");
		isShade = data->IntAttribute("shade");
		isStatic = data->IntAttribute("isstatic");

		data = data->NextSiblingElement("move_info");

		if (isStatic == false)
		{
			isMove = data->IntAttribute("ismove");
			isLoop = data->IntAttribute("isloop");
			times = data->DoubleAttribute("times");
		}

		data = data->NextSiblingElement("position");
		startPos.x = data->IntAttribute("posX");
		startPos.y = data->IntAttribute("posY");
		
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
		data = data->NextSiblingElement("destposition0");
		if (data != nullptr)
		{
			destPos.x = data->IntAttribute("posX");
			destPos.y = data->IntAttribute("posY");
			triggerIndex = data->IntAttribute("trigger_index");
		}
		if (isShade == true)
			shadeIndex.emplace_back(this->m_Obstacle->GetObj().size());

		if (isStatic == false && isMove == false && triggerIndex < 0)
			assert(0);	//something is wrong


		switch (type)
		{
		case NORMAL:
		{
			if (isStatic == false)
				this->PlusObstacle((Type)type, startPos, destPos, size, isMove, isLoop, times);
			else
				this->PlusObstacle((Type)type, startPos, size);
		}
			break;
		case SPIKE:
		{
			if (isStatic == false)
				this->PlusObstacle(startPos, destPos, size, side[LEFT], side[UP], side[RIGHT], side[DOWN], isMove, isLoop, times);
			else
				this->PlusObstacle(startPos, size, side[LEFT], side[UP], side[RIGHT], side[DOWN]);
		}
			break;
		case WATER:
			this->PlusObstacle((Type)type, startPos, size);
			break;
		}

		while (data != nullptr)
		{
			Vector2 addDestPos;
			addDestPos.x = data->IntAttribute("posX");
			addDestPos.y = data->IntAttribute("posY");
			int triggerIndex = data->IntAttribute("trigger_index");

			this->GetOM()->GetObj().back()->AddDestPos(addDestPos);
			triggerAndObstacle[triggerIndex].emplace_back(this->m_Obstacle->GetObj().size() - 1);
			data = data->NextSiblingElement();
		}
	}//TriggerAndObstacle[0]이 잘못들어가는중인거같음.

	trigger = trigger->FirstChildElement("trigger0");
	Name owner;
	bool isHori;
	int obstacleIndex, dist;
	Side side;
	for (; trigger != nullptr; trigger = trigger->NextSiblingElement())
	{
		XmlElement* data = trigger->FirstChildElement("basic_element");
		owner = (Name)data->IntAttribute("owner");
		isHori = data->IntAttribute("ishori");

		data = data->NextSiblingElement("attached_index");
		obstacleIndex = data->IntAttribute("obstacle_index");
		dist = data->IntAttribute("dist");
		side = (Side)data->IntAttribute("side");

		//up down right left
		

		this->PlusTrigger(m_Character->GetObj()[owner],m_Obstacle->GetObj()[obstacleIndex],isHori,side,dist);
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
			isLoop = data->IntAttribute("loop");
			times = data->DoubleAttribute("times");
		}

		data = data->NextSiblingElement("position");
		startPos.x = data->IntAttribute("posX");
		startPos.y = data->IntAttribute("posY");

		data = data->NextSiblingElement("destposition0");
		if (data != nullptr)
		{
			endPos.x = data->IntAttribute("posX");
			endPos.y = data->IntAttribute("posY");
			triggerIndex = data->IntAttribute("trigger_index");
		}

		if (isStatic == true)
			this->PlusGoal(m_Character->GetObj()[charIndex], startPos);
		else
			this->PlusGoal(m_Character->GetObj()[charIndex], startPos, endPos, isMove, isLoop, times);

		if (isMove == false && isStatic == false && triggerIndex < 0)
			assert(0);

		if (triggerIndex >= 0 && isStatic == false)
			triggerAndGoal[triggerIndex].emplace_back(m_Goal->GetGoals()[charIndex]);

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

void ObjManager::PlusTrigger(Character* owner, Obstacle* stachedDest, bool isHori, Side side, double dist)
{
	this->objects.emplace_back(this->m_Obstacle->PlusTrigger(owner, stachedDest,isHori,side,dist));
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

