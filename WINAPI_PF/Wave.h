#pragma once

class Wave
{
private:
	bool isActive;
	bool isRight;

	double runTime;

	POINT center;
	POINT* wave;

	WaveElem elem;

public:
	Wave(WaveElem elem, POINT center);
	~Wave();

	void SetActive(bool value) { isActive = value; }

	void Update();
	void Render(HDC hdc);
	
	void Damping();
	void Move(int deltaX = 0,int deltaY = 0);

	bool GetActive() { return isActive; }

};

