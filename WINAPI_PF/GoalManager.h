#pragma once

class GoalManager
{
private:
	vector<Goal*> goals;
	vector<SavePoint*> savePoints;

	bool isClear;


public:
	GoalManager();
	~GoalManager();

	void Update();
	void Render(HDC hdc);
	void Collision();

	Goal* PlusGoal(Character* character, Vector2 pos);
	void PlusSavePoint(vector<Character*> characters,Vector2 pos,Vector2 size);
	bool Check();


};


