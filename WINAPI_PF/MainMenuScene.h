#pragma once

class MainMenuScene : public MenuScene
{
private:
	TextCell* menu;
	TextCellSelect* selectBar;


public:
	MainMenuScene();
	MainMenuScene(string tag);
	~MainMenuScene();

	virtual void Update() override;
	virtual void Render(HDC hdc) override;

	virtual void Start() override;
	virtual void End() override;

};

