#pragma once

class MenuScene : public Scene
{
protected:
	TextCell* cell;


	string tag;
	
public:
	MenuScene();
	~MenuScene();

	virtual void Update() override =0;
	virtual void Render(HDC hdc) override =0;

	virtual bool Start() override = 0;
	virtual bool End() override = 0;

	string GetTag() { return tag; }


};
