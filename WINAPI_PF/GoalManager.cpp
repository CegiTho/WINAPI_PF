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
	
	Collision();
	if (Check() == true)
		;//여기에 싱글톤으로 구현된 게임매니저에서 next stage함수 호출

	for (SavePoint* sp : savePoints)
		sp->Update();
}

void GoalManager::Render(HDC hdc)
{
	for (Goal* goal : goals)
	{
		if (goal != nullptr)
		{
			if (goal->GetRect()->Collision(M_CAM->GetScreen()) == true)
				goal->Render(hdc);
		}
	}

	for (SavePoint* sp : savePoints)
	{
		sp->Render(hdc);
	}
}

void GoalManager::Collision()
{
	for (Goal* goal : goals)
	{
		if (goal != nullptr)
			goal->Collision();
	}
}

Goal* GoalManager::PlusGoal(Character* character, Vector2 pos)
{
	Goal* goal = new Goal(character, pos);

	int index = (int)character->GetName();
	this->goals[index] = goal;

	return goal;
}

void GoalManager::PlusSavePoint(vector<Character*> characters, Vector2 pos, Vector2 size)
{
	savePoints.emplace_back(new SavePoint(characters, pos, size));
}

bool GoalManager::Check()
{
	isClear = true;
	for (Goal* goal : goals)
	{
		if(goal != nullptr)
			isClear = isClear && goal->GoalCheck();
	}

	return isClear;
}
