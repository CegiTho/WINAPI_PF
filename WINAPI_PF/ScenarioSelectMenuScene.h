#pragma once

class ScenarioSelectMenuScene : public MenuScene
{
private:
	TextCell* menu;

	TextCellSelect* selectBar;
	RectListType* scenarioList;

public:
	ScenarioSelectMenuScene();
	~ScenarioSelectMenuScene();

	virtual void Update() override;
	virtual void Render(HDC hdc) override;

	virtual void Start() override;
	virtual void End() override;

	void Control();
};

