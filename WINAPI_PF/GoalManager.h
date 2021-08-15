#pragma once

class GoalManager
{
private:
	vector<Goal*> goals;
	bool isClear;


public:
	GoalManager();
	~GoalManager();

	vector<Goal*> CreateGoals(vector<Character*> characters);
	bool Check();


};


