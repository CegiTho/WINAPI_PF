#pragma once

class SettingMenuScene : public MenuScene
{
private:
	TextCell* menu;
	
	TextCellSelect* selectBar;
	PercentType* volumeControl;
	TextType* keyControl;


public:
	SettingMenuScene();
	~SettingMenuScene();

	virtual void Update() override;
	virtual void Render(HDC hdc) override;

	virtual void Start() override;
	virtual void End() override;

	void Control();

};
