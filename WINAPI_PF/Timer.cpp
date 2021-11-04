#include "Framework.h"
#include "Timer.h"

Timer::Timer()
	:frameRate(0),frameCount(0),timeElapsed(0),oneSecCount(0),runTime(0),lockFPS(0)
{
	QueryPerformanceFrequency((LARGE_INTEGER*)&periodFrequency);	//초당 cpu진동수 체크

	QueryPerformanceCounter((LARGE_INTEGER*)&lastTime);				//현재 cpu진동수

	timeScale = 1.0 / (double)periodFrequency;						//1주기
}

Timer::~Timer()
{
}

void Timer::Update()
{
	QueryPerformanceCounter((LARGE_INTEGER*)&curTime);
	timeElapsed = (double)(curTime - lastTime) * timeScale;

	if (lockFPS != 0)
	{
		while (timeElapsed < (1.0 / lockFPS))
		{
			QueryPerformanceCounter((LARGE_INTEGER*)&curTime);
			timeElapsed = (double)(curTime - lastTime) * timeScale;
		}
	}

	lastTime = curTime;

	//FPS
	frameCount++;
	oneSecCount += timeElapsed;

	if (oneSecCount >= 1)
	{
		frameRate = frameCount;
		frameCount = 0;
		oneSecCount -= 1;
	}

	runTime += timeElapsed;
}

void Timer::Render()
{
	wstring str;

	str = L"FPS : " + to_wstring(frameRate);
	TextOut(Program::backBuffer, 0, 500, str.c_str(), str.size());

	str = L"RunTime : " + to_wstring(runTime);
	TextOut(Program::backBuffer, 0, 20, str.c_str(), str.size());

	str = L"TimeElapsed : " + to_wstring(timeElapsed);
	TextOut(Program::backBuffer, 0, 40, str.c_str(), str.size());

}
