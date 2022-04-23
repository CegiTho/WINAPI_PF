#pragma once

class Stage_1_4_Scene : public StageScene
{
private:



public:
	Stage_1_4_Scene(string tag);
	~Stage_1_4_Scene();

	virtual void Update() override;
	virtual void Render(HDC hdc) override;

	virtual void Start() override;
	virtual void End() override;

};


