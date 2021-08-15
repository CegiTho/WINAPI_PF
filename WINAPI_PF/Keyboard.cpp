#include "Framework.h"
#include "Keyboard.h"

Keyboard* Keyboard::instance = nullptr;

Keyboard::Keyboard()
	:curState{}, oldState{}
{
	ZeroMemory(mapState, sizeof(mapState));
	//배열의 null초기화의 두가지 방법(이니셜라이저{} , ZeroMemory)
}

Keyboard::~Keyboard()
{
}

void Keyboard::Update()
{
	//직전 루프시 입력값들은 전부 old에 넣어줌
	memcpy(oldState, curState, sizeof(curState));

	//모든 입력값을 전부 넣어줌.
	//반환은 0 ,1   때졌을 때 128,129    눌러졌을 때   
	//새로운 입력결과를 curState에 저장
	GetKeyboardState(curState);
	//KEYMAX개 배열에 아스키코드를 따라 키보드 입력값 배열이 있고 입력결과가 0,1,128,129로 저장됨
	
	for (int i = 0; i < KEYMAX; i++)
	{
		byte key = curState[i] & 0x80;		
		//0x80(떨어져있다가 호출시점에 눌림),0x81(눌려있었고 호출시점에도 눌림)
		//위 두 상태 아니면 key는 항상 0
		curState[i] = key ? 1 : 0;

		int old = oldState[i];
		int cur = curState[i];

		if (old == 0 && cur == 1)	//떨어져있었음 -> 눌림
			mapState[i] = DOWN;
		else if (old == 1 && cur == 0)	//눌려있었음 -> 떨어짐
			mapState[i] = UP;
		else if (old == 1 && cur == 1)	//눌려있었음 -> 눌림
			mapState[i] = PRESS;
		else if(old == 0 && cur == 0)
			mapState[i] = NONE;
	}

}
