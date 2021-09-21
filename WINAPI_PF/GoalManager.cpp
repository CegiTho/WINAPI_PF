#include "Framework.h"

GoalManager::GoalManager(vector<Character*> characters, STAGE_NUM stage)
	:isClear(true)
{
	CreateGoals(characters, stage);
}

GoalManager::~GoalManager()
{
}

vector<Goal*> GoalManager::CreateGoals(vector<Character*> characters,STAGE_NUM stage)
{
	

	return goals;
}

bool GoalManager::Check()
{
	for (Goal* goal : goals)
	{
		isClear = isClear && goal->GoalCheck();
	}

	if (isClear == true)
		return isClear;
	else
		return false;
}
