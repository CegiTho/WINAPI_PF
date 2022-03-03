#pragma once

class TestScene : public Scene
{
private:
	ObjManager* m_Obj;
	
	ShadeManager* m_Shade;


public:
	TestScene();
	~TestScene();


	virtual void Update() override;
	virtual void Render(HDC hdc) override;



};



