#include "Framework.h"

GoalManager::GoalManager()
	:isClear(true)
{
}

GoalManager::~GoalManager()
{
}

vector<Goal*> GoalManager::CreateGoals(vector<Character*> characters)
{
	for(Character* character : characters)
		goals.emplace_back(new Goal(character,))

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
