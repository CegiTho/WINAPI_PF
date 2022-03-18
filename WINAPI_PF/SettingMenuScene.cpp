#include "Framework.h"
#include "SettingMenuScene.h"

SettingMenuScene::SettingMenuScene()
{
	this->tag = "Setting";
	isEnd = false;

	vector<string> tags;
	tags.emplace_back("Main Menu");
	tags.emplace_back("FX Volume");
	tags.emplace_back("Music Volume");
	tags.emplace_back("Jump");
	tags.emplace_back("Next Character");
	tags.emplace_back("Prev Character");

	vector<string> menuList;
	menuList.emplace_back("Return To Main Menu");
	menuList.emplace_back("FX Volume");
	menuList.emplace_back("Music Volume");
	menuList.emplace_back("Jump");
	menuList.emplace_back("Next Character");
	menuList.emplace_back("Prev Character");

	menu = new TextCell(menuList, tags);
	selectBar = new TextCellSelect(menu);
	volumeControl = new PercentType(menu);
	keyControl = new TextType(menu);
}

SettingMenuScene::~SettingMenuScene()
{
	delete selectBar;
	delete menu;
	delete volumeControl;
	delete keyControl;
}

void SettingMenuScene::Update()
{
	Control();
	selectBar->Update();
	volumeControl->Update();
	keyControl->Update();
	
	menu->Update();

	if (isEnd == true && menu->GetActive() == false)
		SCENE->DequeueScene();
}

void SettingMenuScene::Render(HDC hdc)
{
	selectBar->Render(hdc);
	volumeControl->Render(hdc);
	keyControl->Render(hdc);

	menu->Render(hdc);
}

void SettingMenuScene::Start()
{
	menu->SetMove(true);
	M_CAM->SetMapSize({ WIN_WIDTH, WIN_HEIGHT }, true);
}

void SettingMenuScene::End()
{
	isEnd = true;
	menu->SetMove(true);

}

void SettingMenuScene::Control()
{
	int index = menu->GetMenuIndex();
	if (menu->GetTags()[index] == "FX Volume" ||
		menu->GetTags()[index] == "Music Volume")
	{
		volumeControl->SetActive(true);
		keyControl->SetActive(false);
		selectBar->SetActive(false);
	}
	else if (menu->GetTags()[index] == "Jump" ||
		menu->GetTags()[index] == "Next Character" ||
		menu->GetTags()[index] == "Prev Character")
	{
		volumeControl->SetActive(false);
		keyControl->SetActive(true);
		selectBar->SetActive(false);
	}
	else
	{
		volumeControl->SetActive(false);
		keyControl->SetActive(false);
		selectBar->SetActive(true);
	}

}