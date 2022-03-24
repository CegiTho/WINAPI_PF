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
	for (Goal* goal : goals)
		goal->Update();

	for (SavePoint* sp : savePoints)
		sp->Update();

	if (Check() == true)
	{
		SOUND->Play("Stage_Clear_Sound_FX");
		//
		SCENE->ChangeScene("Main Menu");
		;//여기에 싱글톤으로 구현된 게임매니저에서 next stage함수 호출
	}
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

Goal* GoalManager::PlusGoal(Character* character, Vector2 startPos, Vector2 endPos, bool isMove, bool loop, double times)
{
	Goal* goal = new Goal(character, startPos,endPos,times,isMove,loop);

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
