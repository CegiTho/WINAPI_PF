#pragma once

class GoalManager
{
private:
	vector<Goal*> goals;
	bool isClear;


public:
	GoalManager(vector<Character*> characters, STAGE_NUM stage);
	~GoalManager();

	vector<Goal*> CreateGoals(vector<Character*> characters, STAGE_NUM stage);
	bool Check();


};


