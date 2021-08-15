#pragma once

class Timer
{
private:
	Timer();
	~Timer();

	double timeScale;
	double timeElapsed;		//1�ֱ�

	//long long�� ,  �ַ� �ð�����/��Ʈ��ũ ���õ� �� ��
	__int64 curTime;			//���� ������
	__int64 lastTime;			//���� ������
	__int64 periodFrequency;	//cpu������ ����

	int frameRate;				//=FPS
	int frameCount;

	double oneSecCount;
	double runTime;
	double lockFPS;				//FPS������

	

public:
	//�� instance�� static���� ����Ǿ ���� Create()�� �ʿ� ���� �������߿� �ν��Ͻ� ��.
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

