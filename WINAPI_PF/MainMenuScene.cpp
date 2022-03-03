#include "Framework.h"

MainMenuScene::MainMenuScene()
{
    menuList.emplace_back("New Game");
    menuList.emplace_back("Scenario Select");
    menuList.emplace_back("Setting");
    menuList.emplace_back("Exit");

    menu = new TextCell(menuList);
    selectBar = new TextCellSelect(menu);

    target = new Thomas({ WIN_WIDTH / 2 , WIN_HEIGHT / 2 });
    M_CAM->TargetChange(target);

}

MainMenuScene::~MainMenuScene()
{
    delete menu;
    delete selectBar;
    delete target;
}

void MainMenuScene::Update()
{
    menu->Update();
    selectBar->Update();

}

void MainMenuScene::Render(HDC hdc)
{
    menu->Render(hdc);
    selectBar->Render(hdc);

}

bool MainMenuScene::Start()
{
    menu->SetMove(true);
    return true;
}

bool MainMenuScene::End()
{
    return true;
}
