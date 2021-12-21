#include "Framework.h"
#include "Program.h"

#include "TestScene.h"

Program::Program(HWND hWindow)
{
	srand((unsigned)time(nullptr));
	hWnd = hWindow;

	SCENE->Add("Test", new TestScene());
	SCENE->ChangeScene("Test");

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
