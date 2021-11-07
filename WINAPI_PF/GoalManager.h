#pragma once

class GoalManager
{
private:
	vector<Goal*> goals;
	bool isClear;


public:
	GoalManager();
	~GoalManager();

	void Update();
	void Render(HDC hdc);

	Goal* PlusGoal(Character* character, Vector2 pos);
	bool Check();


};


