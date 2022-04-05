#pragma once

class MenuScene : public Scene
{
protected:


	
public:
	MenuScene();
	MenuScene(string tag) {}
	~MenuScene();

	virtual void Update() override =0;
	virtual void Render(HDC hdc) override =0;

	virtual void Start() override = 0;
	virtual void End() override = 0;

};
