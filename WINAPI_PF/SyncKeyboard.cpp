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
		curState[i] = key ? 1 : 0;		//´­·È´ÂÁö ¶³¾îÁ³´ÂÁö

		int old = oldState[i];
		int cur = curState[i];

		if (old == 0 && cur == 1)		//¶³¾îÁ®ÀÖ¾úÀ½ ,´­¸²
			mapState[i] = DOWN;
		else if (old == 1 && cur == 0)	//´­·ÁÀÖ¾úÀ½ , ¶³¾îÁü
			mapState[i] = UP;
		else if (old == 1 && cur == 1)	//´­·ÁÀÖ¾úÀ½ , ´­¸²
			mapState[i] = PRESS;
		else if (old == 0 && cur == 0)	//¶³¾îÁ®ÀÖ¾úÀ½ , ¶³¾îÁü
			mapState[i] = NONE;
	}
}
