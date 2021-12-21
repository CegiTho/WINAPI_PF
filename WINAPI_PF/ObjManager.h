#pragma once

class ObjManager
{
private:
	vector<T_Object*> objects;

	CharacterManager*	m_Character;
	ObstacleManager*	m_Obstacle;
	GoalManager*		m_Goal;

public:
	ObjManager();
	~ObjManager();

	void LoadStage(STAGE_NUM num);

	void Update();
	void Render(HDC hdc);

	void Collision();

	CharacterManager* GetCM() { return m_Character; }
	ObstacleManager* GetOM() { return m_Obstacle; }

	void PlusCharacter(Name name,Vector2 pos);

	void PlusObstacle(Type type, Vector2 center, Vector2 size);
	void PlusObstacle(Vector2 center, Vector2 size,bool left,bool up , bool right,bool down);

	void PlusGoal(Character* character, Vector2 pos);

};


