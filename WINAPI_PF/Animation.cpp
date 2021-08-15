#include "Framework.h"
#include "Animation.h"

Animation::Animation(double frameUpdateSec)
	:time(0),frameUpdateSec(frameUpdateSec),play(false),loop(false),
	pingpong(false),EndEvent(nullptr),EndEventInt(nullptr),nextAction(0)
{


}

Animation::Animation(Texture* texture, double frameUpdateSec)
	: time(0), frameUpdateSec(frameUpdateSec), play(false), loop(false),
	pingpong(false), EndEvent(nullptr), EndEventInt(nullptr), nextAction(0)
{
	maxFrame = texture->MaxFrame();

	for (int y = 0; y < maxFrame.y; y++)
	{
		for (int x = 0; x < maxFrame.x; x++)
		{
			POINT pos = { x,y };
			frames.emplace_back(pos);
		}
	}

}

Animation::~Animation()
{
}

void Animation::Update()
{
	if (play == false)
		return;

	time += DELTA;

	if (time > frameUpdateSec)
	{
		time -= frameUpdateSec;	//그냥 0넣으면 미세하게 틀려짐
		curPlayNum++;

		if (curPlayNum > action.size() - 1)	//마지막까지 가면 터짐
		{
			if (loop == true)
				curPlayNum = 0;
			else
			{
				curPlayNum--;
				play = false;

				if (EndEvent != nullptr)
					EndEvent();
				if (EndEventInt != nullptr)
					EndEventInt(nextAction);
			}
		}
	}
}

void Animation::SetDefault(bool loop, bool pingpong)
{
	this->loop = loop;
	this->pingpong = pingpong;

	action.clear();

	for (int i = 0; i < frames.size(); i++)
	{
		action.emplace_back(i);
	}

	SetPingpong();
}

void Animation::SetArray(int* arr, int arrSize, bool loop, bool pingpong)
{
	this->loop = loop;
	this->pingpong = pingpong;

	action.clear();

	for (int i = 0; i < arrSize; i++)
	{
		action.emplace_back(arr[i]);
	}

	SetPingpong();

}

void Animation::SetPart(int start, int end, bool loop, bool pingpong)
{
	this->loop = loop;
	this->pingpong = pingpong;

	action.clear();

	for (int i = start; i <= end; i++)
	{
		action.emplace_back(i);
	}

	SetPingpong();
}

void Animation::SetFrame(int left, int top, int width, int height)
{
	RECT rect = { left,top,width,height };
	rectFrames.emplace_back(rect);
	action.emplace_back(action.size());
}

void Animation::SetPingpong()
{
	if (pingpong == true)
	{
		for (int i = action.size() - 2; i >= 0; i--)
			action.emplace_back(action[i]);
	}
}
