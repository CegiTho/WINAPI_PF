#pragma once

class ObjManager
{
private:
	vector<T_Object*> objects;

	CharacterManager* m_Character;
	ObstacleManager* m_Obstacle;

public:
	ObjManager();
	~ObjManager();

	void Update();
	void Render(HDC hdc);

	void Collision();

	CharacterManager* GetCM() { return m_Character; }
	ObstacleManager* GetOM() { return m_Obstacle; }

	void PlusCharacter(Name name);
	void PlusObstacle(Type type, Vector2 center, Vector2 size);

};


