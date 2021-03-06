#pragma once

#define KEYMAX 256
//강의는 255였는데 GetKeyState함수 써있는거 보면 256이 맞는거같아서 이걸로 바꿈,
//어차피 구현안된 키 몇개있어서 상관 없음

class Keyboard
{
private:
	enum
	{
		NONE,
		DOWN,
		UP,
		PRESS
	};

	Keyboard();
	~Keyboard();

	static Keyboard* instance;
public:
	static Keyboard* Get()				
	{
		return instance;
	}

	static void Create()
	{
		instance = new Keyboard();
	}

	static void Delete()
	{
		delete instance;
	}

	void Update();

	bool Down(UINT key) { return mapState[key] == DOWN; }
	bool Up(UINT key) { return mapState[key] == UP; }
	bool Press(UINT key) { return mapState[key] == PRESS; }

private:
	byte curState[KEYMAX];
	byte oldState[KEYMAX];
	byte mapState[KEYMAX];
};


