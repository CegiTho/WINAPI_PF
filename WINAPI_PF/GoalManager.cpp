#include "Framework.h"

GoalManager::GoalManager()
	:isClear(false)
{

	this->goals.assign(CHARACTER_COUNT, nullptr);
}

GoalManager::~GoalManager()
{
	for (Goal* goal : goals)
		delete goal;
}

void GoalManager::Update()
{
	for (Goal* goal : goals)
		goal->Update();
}

void GoalManager::Render(HDC hdc)
{
	for (Goal* goal : goals)
		goal->Render(hdc);
}


Goal* GoalManager::PlusGoal(Character* character, Vector2 pos)
{
	Goal* goal = new Goal(character, pos);

	int index = (int)character->GetName();
	this->goals[index] = goal;

	return goal;
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
