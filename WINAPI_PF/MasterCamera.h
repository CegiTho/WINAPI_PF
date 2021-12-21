#pragma once

class MasterCamera
{
private:
	Character* target;
	Rect* screen;

	
	HBITMAP hBitmap;

	Vector2 mapSize;
	Vector2 offset;

	bool isMoving;

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

	void TargetChange(Character* character);
	void SetPos(Vector2 pos) { this->screen->center = pos;}
	void SetMapSize(Vector2 size);

	HDC GetBackBuffer() { return this->backBuffer; }

	static HDC backBuffer;
};


