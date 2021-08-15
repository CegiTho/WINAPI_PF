#include "Framework.h"
#include "Keyboard.h"

Keyboard* Keyboard::instance = nullptr;

Keyboard::Keyboard()
	:curState{}, oldState{}
{
	ZeroMemory(mapState, sizeof(mapState));
	//�迭�� null�ʱ�ȭ�� �ΰ��� ���(�̴ϼȶ�����{} , ZeroMemory)
}

Keyboard::~Keyboard()
{
}

void Keyboard::Update()
{
	//���� ������ �Է°����� ���� old�� �־���
	memcpy(oldState, curState, sizeof(curState));

	//��� �Է°��� ���� �־���.
	//��ȯ�� 0 ,1   ������ �� 128,129    �������� ��   
	//���ο� �Է°���� curState�� ����
	GetKeyboardState(curState);
	//KEYMAX�� �迭�� �ƽ�Ű�ڵ带 ���� Ű���� �Է°� �迭�� �ְ� �Է°���� 0,1,128,129�� �����
	
	for (int i = 0; i < KEYMAX; i++)
	{
		byte key = curState[i] & 0x80;		
		//0x80(�������ִٰ� ȣ������� ����),0x81(�����־��� ȣ��������� ����)
		//�� �� ���� �ƴϸ� key�� �׻� 0
		curState[i] = key ? 1 : 0;

		int old = oldState[i];
		int cur = curState[i];

		if (old == 0 && cur == 1)	//�������־��� -> ����
			mapState[i] = DOWN;
		else if (old == 1 && cur == 0)	//�����־��� -> ������
			mapState[i] = UP;
		else if (old == 1 && cur == 1)	//�����־��� -> ����
			mapState[i] = PRESS;
		else if(old == 0 && cur == 0)
			mapState[i] = NONE;
	}

}
