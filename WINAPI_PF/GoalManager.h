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
	void Render(HDC hdc,Vector2 offset);

	Goal* PlusGoal(Character* character, Vector2 pos);
	bool Check();


};


