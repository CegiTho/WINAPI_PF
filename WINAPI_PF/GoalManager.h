#pragma once

class GoalManager
{
private:
	vector<Goal*> goals;
	vector<SavePoint*> savePoints;

	bool isClear;

	STAGE_NUM nowStage;

public:
	GoalManager();
	~GoalManager();

	void Update();
	void Render(HDC hdc);
	void Collision();

	Goal* PlusGoal(Character* character, Vector2 pos);
	Goal* PlusGoal(Character* character, Vector2 startPos,Vector2 endPos,bool isMove,bool loop,double times);
	void PlusSavePoint(vector<Character*> characters,Vector2 pos,Vector2 size);
	bool Check();

	vector<Goal*> GetGoals() { return goals; }
	void SetNowStage(STAGE_NUM value) { nowStage = value; }
};


