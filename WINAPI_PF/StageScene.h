#pragma once

class StageScene : public Scene
{
protected:
	ObjManager* m_Obj;
	ShadeManager* m_Shade;

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

};

