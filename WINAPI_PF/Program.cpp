#include "Framework.h"
#include "Program.h"

#include "TestScene.h"
#include "MainMenuScene.h"
#include "SettingMenuScene.h"
#include "ScenarioSelectMenuScene.h"
#include "Stage_1_1_Scene.h"
#include "Stage_1_2_Scene.h"
#include "Stage_1_3_Scene.h"

Program::Program(HWND hWindow)
{
	srand((unsigned)time(nullptr));
	hWnd = hWindow;

	LoadSound();
	
	SCENE->Add("Main Menu", new MainMenuScene("Main Menu"));
	SCENE->Add("Setting", new SettingMenuScene("Setting"));
	SCENE->Add("Scenario Select", new ScenarioSelectMenuScene("Scenario Select"));
	SCENE->Add("Stage_1-1", new Stage_1_1_Scene("Stage_1-1"));
	SCENE->Add("Stage_1-2", new Stage_1_2_Scene("Stage_1-2"));
	SCENE->Add("Stage_1-3", new Stage_1_3_Scene("Stage_1-3"));


	SCENE->SetScene("Main Menu");

	SOUND->Play("BGM",0.1f);
}

Program::~Program()
{

}

void Program::Update()
{
	KEYBOARD->Update();
	TIMER->Update();
	SOUND->Update();

	M_CAM->Update();

	SCENE->Update();

	InvalidateRect(hWnd, nullptr, false);
}

void Program::Render(HDC hdc)
{
	//backBuffer Èò»ö ÃÊ±âÈ­.
	PatBlt(M_CAM->GetBackBuffer(), 0, 0, M_CAM->GetScreen()->size.x, M_CAM->GetScreen()->size.y, WHITENESS);	

	SCENE->Render(M_CAM->GetBackBuffer());

	TIMER->Render();

	BitBlt(
		hdc, 0, 0, WIN_WIDTH, WIN_HEIGHT,
		M_CAM->GetBackBuffer(),M_CAM->GetPos().x, M_CAM->GetPos().y , SRCCOPY
	);

}

void Program::LoadSound()
{
	SOUND->Add("BGM", "Resource/Sounds/BGM.mp3", BG_CHANNEL,0.0f);//
	SOUND->Add("Goal_In_Sound_FX", "Resource/Sounds/Goal_In_Sound_FX.mp3", SUB_FX_CHANNEL, 0.0f);
	SOUND->Add("Goal_Out_Sound_FX", "Resource/Sounds/Goal_Out_Sound_FX.mp3", SUB_FX_CHANNEL, 0.0f);
	SOUND->Add("Menu_Down_Sound_FX", "Resource/Sounds/Menu_Down_Sound_FX.mp3", SUB_FX_CHANNEL, 0.0f);
	SOUND->Add("Menu_Up_Sound_FX", "Resource/Sounds/Menu_Up_Sound_FX.mp3", SUB_FX_CHANNEL, 0.0f);
	SOUND->Add("Save_Point_In_FX", "Resource/Sounds/Save_Point_In_FX.mp3", SUB_FX_CHANNEL, 0.0f);
	SOUND->Add("Stage_Clear_Sound_FX", "Resource/Sounds/Stage_Clear_Sound_FX.mp3", SUB_FX_CHANNEL, 0.0f);
	SOUND->Add("Trigger_Active_Sound_FX", "Resource/Sounds/Trigger_Active_Sound_FX.mp3", SUB_FX_CHANNEL, 0.0f);
	SOUND->Add("Water_Collision_Sound_FX", "Resource/Sounds/Water_Collision_Sound_FX.mp3", SUB_FX_CHANNEL, 0.0f);
	
	SOUND->Add("All_Land_Sound_FX", "Resource/Sounds/All_Land_Sound_FX.mp3", MAIN_FX_CHANNEL, 0.0f);
	SOUND->Add("Thomas_Jump_Sound_James_Also_FX", "Resource/Sounds/Thomas_Jump_Sound_James_Also_FX.mp3", MAIN_FX_CHANNEL, 0.0f);
	SOUND->Add("Chris_Jump_Sound_FX", "Resource/Sounds/Chris_Jump_Sound_FX.mp3", MAIN_FX_CHANNEL, 0.0f);
	SOUND->Add("Clare_Jump_Sound_FX", "Resource/Sounds/Clare_Jump_Sound_FX.mp3", MAIN_FX_CHANNEL, 0.0f);
	SOUND->Add("John_Jump_Sound_FX", "Resource/Sounds/John_Jump_Sound_FX.mp3", MAIN_FX_CHANNEL, 0.0f);
	SOUND->Add("Laura_Jump_Sound_FX", "Resource/Sounds/Laura_Jump_Sound_FX.mp3", MAIN_FX_CHANNEL, 0.0f);
	SOUND->Add("Sarah_Jump_Sound_FX", "Resource/Sounds/Sarah_Jump_Sound_FX.mp3", MAIN_FX_CHANNEL, 0.0f);

}
