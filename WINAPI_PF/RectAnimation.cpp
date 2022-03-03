#include "Framework.h"

RectAnimation::RectAnimation(Character* character)
	:character(character),state(IDLE)
{
	ratio.assign(State_Count,vector<Vector2>(5));
	frameUpdateSec.assign(State_Count,0);
	originSize = character->GetRect()->Size();

}

RectAnimation::~RectAnimation()
{
}

void RectAnimation::Update()
{
	switch (state)
	{
	case JUMP:
		Play(state);
		break;
	case GOAL:
		Play(state);
		break;
	case IDLE:
		break;
	}
}

void RectAnimation::Render(HDC hdc)
{
	character->GetRect()->Render(hdc);
}

void RectAnimation::Play(State state)
{
	time += DELTA;

	if (time > frameUpdateSec[state])
	{
		time -= frameUpdateSec[state];

		if (character->GetName() != Name::JAMES)
		{
			character->GetRect()->size.x = ratio[state][index].x;
			character->GetRect()->size.y = ratio[state][index].y;
		}
		else
		{
			character->GetRect()->size.x = ratio[state][index].x;
			character->GetRect()->size.y = ratio[state][index].y;
		}


		index++;

		if (index == ratio[state].size())
		{
			index = 0;
			time = 0;
			this->state = State::IDLE;
		}
	}



}

void RectAnimation::SetAnim(State state, vector<Vector2> anim,double frameUpdateSec)
{
	//ratio는 초기화단계에서 State_Count - 1개만 할당됨.
	if (state >= State_Count)
		return;

	//anim framesize또한 초기화에서 5개로 고정.
	if (anim.size() > MAX_ANIM_FRAME)
		return;

	for (int i = 0; i < anim.size(); i++)
	{
		ratio[state][i] = originSize * anim[i];
	}
	this->frameUpdateSec[state] = frameUpdateSec;
}
