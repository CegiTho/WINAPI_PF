#pragma once

typedef Name OwnerName;

class ObjManager
{
private:
	vector<T_Object*> objects;
	
	vector<int> shadeIndex;

	map<OwnerName, vector<int>> triggerIndex;
	map<OwnerName, Goal*> triggerGoal;

	CharacterManager*	m_Character;
	ObstacleManager*	m_Obstacle;
	GoalManager*		m_Goal;

public:
	ObjManager();
	~ObjManager();

	void LoadStage(STAGE_NUM num);

	void Update();
	void Render(HDC hdc);

	void ConnectToTrigger();

	CharacterManager*	GetCM()		{ return m_Character; }
	ObstacleManager*	GetOM()		{ return m_Obstacle; }
	GoalManager*		GetGM()		{ return m_Goal; }

	void PlusCharacter(Name name,Vector2 pos);

	void PlusTrigger(Character* owner,Vector2 center);
	void PlusObstacle(Type type, Vector2 center, Vector2 size);
	void PlusObstacle(Type type, Vector2 startPos,Vector2 endPos, Vector2 size,bool isMove,bool isLoop,double times);
	void PlusObstacle(Vector2 center, Vector2 size,bool left,bool up , bool right,bool down);
	void PlusObstacle(Vector2 startPos,Vector2 endPos, Vector2 size,bool left,bool up , bool right,bool down, bool isMove, bool isLoop,double times);

	void PlusGoal(Character* character, Vector2 pos);
	void PlusGoal(Character* character, Vector2 startPos,Vector2 endPos, bool isMove, bool loop,double times);

	vector<int> NeedShade() { return shadeIndex; }
};


