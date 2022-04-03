#pragma once

class MasterCamera
{
private:
	Rect* target;
	Rect* screen;

	HBITMAP hBitmap;

	HDC clearDC;
	HBITMAP screenClear;

	Vector2 mapSize;
	Vector2 offset;

	bool isMoving;
	bool isHold;
	bool stageOut;
	bool isClear;

	int alpha;
	int clearAlpha;

	MasterCamera();
	~MasterCamera();


public:
	static MasterCamera* Get()
	{
		static MasterCamera instance;
		return &instance;
	}

	void Update();

	Vector2 GetPos() { return screen->LeftTopV(); }
	Vector2 GetMapSize() { return mapSize; }
	Rect* GetScreen() { return screen; }

	void TargetChange(Rect* rect);
	void SetPos(Vector2 pos) { this->screen->center = pos;}
	void SetMapSize(Vector2 size,bool isHold);
	void SetHold(bool value) { isHold = value; }
	void SetClear(bool value) { isClear = value; }

	HDC GetBackBuffer() { return this->backBuffer; }

	void ScreenClear();

	static HDC backBuffer;
};


