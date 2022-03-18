#include "Framework.h"

MainMenuScene::MainMenuScene()
{
    isEnd = false;

    vector<string> menuList,tags;
    menuList.emplace_back("New Game");
    menuList.emplace_back("Scenario Select");
    menuList.emplace_back("Setting");
    menuList.emplace_back("Exit");
    tags = menuList;
    tags[0] = "Test";

    menu = new TextCell(menuList,tags);

    selectBar = new TextCellSelect(menu);
    selectBar->SetActive(true);

    tag = "Main Menu";
}

MainMenuScene::~MainMenuScene()
{
    delete menu;
    delete selectBar;
}

void MainMenuScene::Update()
{
   
    menu->Update();
    selectBar->Update();
    
    if (isEnd == true && menu->GetActive() == false)
        SCENE->DequeueScene();
}

void MainMenuScene::Render(HDC hdc)
{
    selectBar->Render(hdc);
    menu->Render(hdc);

}

void MainMenuScene::Start()
{
    menu->SetMove(true);
    M_CAM->SetMapSize({ WIN_WIDTH, WIN_HEIGHT },true);
}

void MainMenuScene::End()
{
    isEnd = true;
    menu->SetMove(true);
}
