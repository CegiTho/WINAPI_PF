#include "Framework.h"
#include "SyncKeyboard.h"

SyncKeyboard::SyncKeyboard()
	:mapState{}, curState{}, oldState{}
{
	
}

SyncKeyboard::~SyncKeyboard()
{

}

void SyncKeyboard::Update()
{
	memcpy(oldState, curState, sizeof(curState));

	for (int i = 0; i < KEYMAX; i++)
		curState[i] = GetAsyncKeyState(i);
	
	for (int i = 0; i < KEYMAX; i++)
	{
		SHORT key = curState[i] & 0x8000;		
		curState[i] = key ? 1 : 0;		//���ȴ��� ����������

		int old = oldState[i];
		int cur = curState[i];

		if (old == 0 && cur == 1)		//�������־��� ,����
			mapState[i] = DOWN;
		else if (old == 1 && cur == 0)	//�����־��� , ������
			mapState[i] = UP;
		else if (old == 1 && cur == 1)	//�����־��� , ����
			mapState[i] = PRESS;
		else if (old == 0 && cur == 0)	//�������־��� , ������
			mapState[i] = NONE;
	}
}
