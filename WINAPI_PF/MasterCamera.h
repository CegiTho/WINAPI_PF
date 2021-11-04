#pragma once

class MasterCamera
{
private:
	Character* target;
	Rect* screen;

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
	Rect* GetScreen() { return screen; }

	void TargetChange(Character* character);
	void SetPos(Vector2 pos) { this->screen->center = pos;}
	void SetMapSize(Vector2 size);

};


