#include "Framework.h"
#include "ScenarioSelectMenuScene.h"

ScenarioSelectMenuScene::ScenarioSelectMenuScene()
{
	isEnd = false;

	this->tag = "Scenario Select";

	vector<string> menuList, tags;
	menuList.emplace_back("Return To Main Menu");
	menuList.emplace_back("Chapter_1");
	menuList.emplace_back("Chapter_2");
	menuList.emplace_back("Chapter_3");
	menuList.emplace_back("Chapter_4");
	tags = menuList;
	tags[0] = "Main Menu";

	menu = new TextCell(menuList, tags);
	selectBar = new TextCellSelect(menu);
	scenarioList = new RectListType(menu);


}

ScenarioSelectMenuScene::ScenarioSelectMenuScene(string tag)
{
	isEnd = false;

	this->tag = tag;
	
	vector<string> menuList, tags;
	menuList.emplace_back("Return To Main Menu");
	menuList.emplace_back("Chapter_1");
	menuList.emplace_back("Chapter_2");
	menuList.emplace_back("Chapter_3");
	menuList.emplace_back("Chapter_4");
	tags = menuList;
	tags[0] = "Main Menu";
	
	menu = new TextCell(menuList, tags);
	selectBar = new TextCellSelect(menu);
	scenarioList = new RectListType(menu);
}

ScenarioSelectMenuScene::~ScenarioSelectMenuScene()
{
	delete menu;
	delete selectBar;
	delete scenarioList;
}

void ScenarioSelectMenuScene::Update()
{
	Control();
	menu->Update();
	selectBar->Update();
	scenarioList->Update();

	if (isEnd == true && menu->GetActive() == false)
		SCENE->DequeueScene();
}

void ScenarioSelectMenuScene::Render(HDC hdc)
{
	selectBar->Render(hdc);
	scenarioList->Render(hdc);
	menu->Render(hdc);

}

void ScenarioSelectMenuScene::Start()
{
	menu->SetMove(true);
	M_CAM->SetMapSize({ WIN_WIDTH,WIN_HEIGHT }, true);
}

void ScenarioSelectMenuScene::End()
{
	isEnd = true;
	menu->SetMove(true);
}

void ScenarioSelectMenuScene::Control()
{
	int index = menu->GetMenuIndex();

	if (menu->GetTags()[index] == "Main Menu")
	{
		scenarioList->SetActive(false);
		selectBar->SetActive(true);
	}
	else
	{
		scenarioList->SetActive(true);
		selectBar->SetActive(false);
	}
}
