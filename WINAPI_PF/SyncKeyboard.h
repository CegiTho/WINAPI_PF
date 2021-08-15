#pragma once

//GetAsyncKeyState로 keyboard 입력처리 하려는데 반환값이 GetKeyState랑 달라서 어떻게 해야할지 모르겠음.

#define KEYMAX 256

class SyncKeyboard
{
private:
	enum
	{
		NONE,
		DOWN,
		UP,
		PRESS
	};

	SyncKeyboard();
	~SyncKeyboard();

	SHORT oldState[KEYMAX];
	SHORT curState[KEYMAX];
	SHORT mapState[KEYMAX];

public:
	static SyncKeyboard* Get()
	{
		static SyncKeyboard instance;
		return &instance;
	}

	void Update();

	bool Down(UINT key) { return mapState[key] == DOWN; }
	bool Up(UINT key) { return mapState[key] == UP; }
	bool Press(UINT key) { return mapState[key] == PRESS; }

	

};


