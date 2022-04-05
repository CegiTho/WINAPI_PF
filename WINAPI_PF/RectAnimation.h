#pragma once

#define MAX_ANIM_FRAME 5

class Character;

enum State
{
	JUMP,
	GOAL,
	IDLE,
	SPAWN,
	State_Count
};

class RectAnimation
{
private:
	vector<vector<Vector2>> ratio;
	vector<double> frameUpdateSec;

	Character* character;
	Vector2 originSize;

	double time;
	int index;

	State state;

public:
	RectAnimation(Character* character);
	~RectAnimation();

	void Update();
	void Render(HDC hdc);

	void Play(State state);

	void SetAnim(State state, vector<Vector2> anim,double frameUpdateSec);
	void SetState(State state) { this->state = state; }


};


