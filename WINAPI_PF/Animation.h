#pragma once

class Animation
{
private:
	vector<POINT> frames;
	vector<int> action;

	vector<RECT> rectFrames;

	int curPlayNum;
	POINT maxFrame;

	bool play;
	bool loop;
	bool pingpong;

	double time;
	double frameUpdateSec;

	int nextAction;

	function<void()> EndEvent;
	function<void(int)> EndEventInt;



public:
	Animation(double frameUpdateSec = 0.1);
	Animation(Texture* texture,double frameUpdateSec = 0.1);
	~Animation();

	void Update();
	
	void SetDefault(bool loop = false, bool pingpong = false);
	void SetArray(int* arr, int arrSize, bool loop = false, bool pingpong = false);
	void SetPart(int start, int end, bool loop = false, bool pingpong = false);
	void SetFrame(int left, int top, int width, int height);

	void SetPingpong();
	
	void Play() { play = true, curPlayNum = 0; }
	void Stop() { play = false; }
	bool GetPlay() { return play; }
	
	POINT GetFrame() { return frames[action[curPlayNum]]; }
	RECT GetRectFrame() { return rectFrames[curPlayNum]; }

	void SetLoop(bool value) { loop = value; }
	void SetPingpong(bool value) { pingpong = value; }

	void SetEndEvent(function<void()> value) { EndEvent = value; }
	void SetEndEvent(function<void(int)> value, int index)
	{
		EndEventInt = value;
		nextAction = index;
	}

};

