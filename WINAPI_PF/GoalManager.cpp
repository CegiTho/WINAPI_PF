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

	if (Check() == true)
		;//여기에 싱글톤으로 구현된 게임매니저에서 next stage함수 호출
}

void GoalManager::Render(HDC hdc)
{
	for (Goal* goal : goals)
	{
		if(goal->GetRect()->Collision(M_CAM->GetScreen()) == true)
			goal->Render(hdc);
	}
}

void GoalManager::Render(HDC hdc, Vector2 offset)
{
	for (Goal* goal : goals)
	{
		if (goal->GetRect()->Collision(M_CAM->GetScreen()) == true)
			goal->Render(hdc);
	}
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
