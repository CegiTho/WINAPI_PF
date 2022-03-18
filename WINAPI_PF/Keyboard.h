#pragma once

#define KEYMAX 256
//���Ǵ� 255���µ� GetKeyState�Լ� ���ִ°� ���� 256�� �´°Ű��Ƽ� �̰ɷ� �ٲ�,
//������ �����ȵ� Ű ��־ ��� ����


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


	char GetKey() { return key; }
	bool GetConfirm() { return needConfirm; }
	void SetConfirm(bool value) { needConfirm = value; }
	void SetKey(int wParam);

	void SetJumpKey(char value) { jump = value; }
	void SetNextKey(char value) { nextChar = value; }
	void SetPrevKey(char value) { prevChar = value; }

	char GetJumpKey() { return jump; }
	char GetNextCharKey() { return nextChar; }
	char GetPrevCharKey() { return prevChar; }

	char GetKeyboardValue(int key) { return mapState[key]; }
	
private:
	byte curState[KEYMAX];
	byte oldState[KEYMAX];
	byte mapState[KEYMAX];

	char key;
	bool needConfirm;

	char jump = VK_SPACE;
	char nextChar = 'E';
	char prevChar = 'Q';
};


