#pragma once

class TestScene : public Scene
{
private:
	ObjManager* m_Obj;
	
	ShadeManager* m_Shade;

	bool isEnd;

public:
	TestScene();
	~TestScene();


	virtual void Update() override;
	virtual void Render(HDC hdc) override;

	void End() override { isEnd = true; }


};



