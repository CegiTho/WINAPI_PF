#include "Framework.h"

void StageScene::InitTarget()
{
	if (isStart == true)
	{
		if (stageRunTime > 1.0)
		{
			M_CAM->TargetChange(m_Obj->GetCM()->GetTargetCharacter()->GetRect());
			isStart = false;
			stageRunTime = 0.0;
		}
		else
		{
			stageRunTime += DELTA;
			return;
		}
		return;
	}
}

void StageScene::ChangeScene()
{
	if (KEYDOWN(VK_ESCAPE) == true)
		SCENE->ChangeScene("Main Menu");
	if (isEnd == true)
		SCENE->DequeueScene();
}

void StageScene::ClearCheck() 
{
	if (m_Obj->GetClearStage() == true)
	{
		vector<string> stageSeq = *SCENE->GetStageSeq();
		string nextStageTag;
		vector<string>::iterator iter = find(stageSeq.begin(), stageSeq.end(), this->tag);
		if (iter != stageSeq.end())
		{
			iter++;
			if (iter != stageSeq.end())
				nextStageTag = *iter;
			if (iter == stageSeq.end())
				nextStageTag = "Main Menu";

			SCENE->ChangeScene(nextStageTag);
		}
	}
}