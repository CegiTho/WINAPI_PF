#pragma once

class MenuScene : public Scene
{
protected:
	TextCell* cell;


	string tag;
	
	bool isEnd;
public:
	MenuScene();
	~MenuScene();

	virtual void Update() override =0;
	virtual void Render(HDC hdc) override =0;

	virtual void Start() override = 0;
	virtual void End() override = 0;

	string GetTag() { return tag; }


};
