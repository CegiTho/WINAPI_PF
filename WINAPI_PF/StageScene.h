#pragma once

class StageScene : public Scene
{
protected:
	ObjManager* m_Obj;
	ShadeManager* m_Shade;

	bool isStart = true;
	double stageRunTime =0.0;

public:
	StageScene() {}
	StageScene(string tag) {}
	virtual ~StageScene() {}

	virtual void Update() override = 0;
	virtual void Render(HDC hdc) override = 0;

	virtual void Start() override = 0;
	virtual void End() override = 0;
	ObjManager* GetObjManager() { return m_Obj; }
	ShadeManager* GetShadeManager() { return m_Shade; }

	void ClearCheck()
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

};

