#pragma once

class Wave
{
private:
	bool isActive;
	bool isRight;

	double runTime;
	double oneSec;

	POINT center;
	POINT* wave;
	POINT* origin;

	WaveElem elem;

public:
	Wave(WaveElem elem,bool isRight);
	Wave(WaveElem elem, POINT center,bool isRight);
	~Wave();

	void SetActive(bool value) { isActive = value; }

	void Update();
	void Render(HDC hdc);
	
	void Damping();
	void Move(int deltaX = 0,int deltaY = 0);

	bool GetActive() { return isActive; }
	void SetCenter(POINT center);
};

