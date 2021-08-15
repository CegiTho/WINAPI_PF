#pragma once

class Timer
{
private:
	Timer();
	~Timer();

	double timeScale;
	double timeElapsed;		//1주기

	//long long형 ,  주로 시간관련/네트워크 관련될 때 씀
	__int64 curTime;			//현재 진동수
	__int64 lastTime;			//직전 진동수
	__int64 periodFrequency;	//cpu진동수 저장

	int frameRate;				//=FPS
	int frameCount;

	double oneSecCount;
	double runTime;
	double lockFPS;				//FPS고정값

	

public:
	//얜 instance가 static으로 선언되어서 굳이 Create()할 필요 없이 컴파일중에 인스턴싱 됨.
	static Timer* Get()
	{
		static Timer instance;
		return &instance;
	}

	void Update();
	void Render();

	void SetLockFPS(double value) { lockFPS = value; }
	int GetFPS() { return frameRate; }

	double GetElapsedTime() { return timeElapsed; }
	double GetRunTime() { return runTime; }


};

