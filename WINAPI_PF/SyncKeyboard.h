#pragma once

//GetAsyncKeyState�� keyboard �Է�ó�� �Ϸ��µ� ��ȯ���� GetKeyState�� �޶� ��� �ؾ����� �𸣰���.

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


