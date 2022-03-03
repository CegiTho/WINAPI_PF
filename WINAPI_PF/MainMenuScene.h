#pragma once

class MainMenuScene : public MenuScene
{
private:
	TextCell* menu;
	TextCellSelect* selectBar;
	vector<string> menuList;

	Thomas* target;

public:
	MainMenuScene();
	~MainMenuScene();

	virtual void Update() override;
	virtual void Render(HDC hdc) override;

	virtual bool Start() override;
	virtual bool End() override;

};

