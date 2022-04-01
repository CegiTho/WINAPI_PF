#pragma once

class Stage_1_3_Scene : public StageScene
{
private:


public:
	Stage_1_3_Scene();
	Stage_1_3_Scene(string tag);
	Stage_1_3_Scene(STAGE_NUM stage);
	~Stage_1_3_Scene();


	virtual void Update() override;
	virtual void Render(HDC hdc) override;

	virtual void Start() override;
	virtual void End() override;

};
