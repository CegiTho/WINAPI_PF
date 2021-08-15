#include "Framework.h"
#include "Program.h"

#include "TestScene.h"

HDC Program::backBuffer = nullptr;

Program::Program(HWND hWindow)
{
	srand((unsigned)time(nullptr));
	hWnd = hWindow;

	HDC hdc = GetDC(hWnd);
	backBuffer = CreateCompatibleDC(hdc);
	hBit = CreateCompatibleBitmap(hdc, WIN_WIDTH, WIN_HEIGHT);
	SelectObject(backBuffer, (HGDIOBJ)hBit);

	ReleaseDC(hWnd, hdc);

	SetBkMode(Program::backBuffer, TRANSPARENT);

	SCENE->Add("Test", new TestScene());
	SCENE->ChangeScene("Test");

}

Program::~Program()
{
	DeleteObject(backBuffer);
	DeleteObject(hBit);

}

void Program::Update()
{
	KEYBOARD->Update();
	TIMER->Update();

	SCENE->Update();

	InvalidateRect(hWnd, nullptr, false);
}

void Program::Render(HDC hdc)
{
	PatBlt(Program::backBuffer, 0, 0, WIN_WIDTH, WIN_HEIGHT, WHITENESS);	//backBuffer Èò»ö ÃÊ±âÈ­.

	SCENE->Render(backBuffer);

	TIMER->Render();

	BitBlt(
		hdc, 0, 0, WIN_WIDTH, WIN_HEIGHT,
		backBuffer, 0, 0, SRCCOPY
	);
}
