#include "Framework.h"
#include "Program.h"

#include "TestScene.h"
#include "MainMenuScene.h"
#include "SettingMenuScene.h"
#include "ScenarioSelectMenuScene.h"

Program::Program(HWND hWindow)
{
	srand((unsigned)time(nullptr));
	hWnd = hWindow;

	LoadSound();
	
	SCENE->Add("Main Menu", new MainMenuScene());
	SCENE->Add("Setting", new SettingMenuScene());
	SCENE->Add("Scenario Select", new ScenarioSelectMenuScene());
	SCENE->Add("Test", new TestScene());
	//SCENE->Add("Test", new TestScene());
	SCENE->SetScene("Main Menu");

	SOUND->SetBGMVolume(0.0f);
	SOUND->SetFXVolume(0.5f);
	
}

Program::~Program()
{

}

void Program::Update()
{
	KEYBOARD->Update();
	TIMER->Update();

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
	SOUND->Add("BGM", "Resource/Sounds/BGM.mp3", true);//
	SOUND->Add("All_Land_Sound_FX", "Resource/Sounds/All_Land_Sound_FX.mp3", false);//
	SOUND->Add("Goal_In_Sound_FX", "Resource/Sounds/Goal_In_Sound_FX.mp3", false);//
	SOUND->Add("Goal_Out_Sound_FX", "Resource/Sounds/Goal_Out_Sound_FX.mp3", false);//
	SOUND->Add("Menu_Down_Sound_FX", "Resource/Sounds/Menu_Down_Sound_FX.mp3", false);
	SOUND->Add("Menu_Up_Sound_FX", "Resource/Sounds/Menu_Up_Sound_FX.mp3", false);
	SOUND->Add("Save_Point_In_FX", "Resource/Sounds/Save_Point_In_FX.mp3", false);//
	SOUND->Add("Stage_Clear_Sound_FX", "Resource/Sounds/Stage_Clear_Sound_FX.mp3", false);
	SOUND->Add("Trigger_Active_Sound_FX", "Resource/Sounds/Trigger_Active_Sound_FX.mp3", false);
	
	SOUND->Add("Thomas_Jump_Sound_James_Also_FX", "Resource/Sounds/Thomas_Jump_Sound_James_Also_FX.mp3", false);//
	SOUND->Add("Chris_Jump_Sound_FX", "Resource/Sounds/Chris_Jump_Sound_FX.mp3", false);//
	SOUND->Add("Clare_Jump_Sound_FX", "Resource/Sounds/Clare_Jump_Sound_FX.mp3", false);//
	SOUND->Add("John_Jump_Sound_FX", "Resource/Sounds/John_Jump_Sound_FX.mp3", false);//
	SOUND->Add("Laura_Jump_Sound_FX", "Resource/Sounds/Laura_Jump_Sound_FX.mp3", false);//
	SOUND->Add("Sarah_Jump_Sound_FX", "Resource/Sounds/Sarah_Jump_Sound_FX.mp3", false);//

	SOUND->Play("BGM", true);
	//SOUND->SetBGMVolume(0.0);
	//SOUND->SetFXVolume(0.0);
}
