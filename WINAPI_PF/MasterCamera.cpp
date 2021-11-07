#include "Framework.h"
#include "MasterCamera.h"

HDC MasterCamera::backBuffer = nullptr;

MasterCamera::MasterCamera()
{
	target = nullptr;
	screen = new Rect({ 0,0 }, { WIN_WIDTH,WIN_HEIGHT });
	isMoving = true;
	offset = { CENTER_X,CENTER_Y };
	mapSize = { 0,0 };

	HDC hdc = GetDC(hWnd);
	MasterCamera::backBuffer = CreateCompatibleDC(hdc);
	hBitmap = nullptr;

	ReleaseDC(hWnd, hdc);
	SetBkMode(MasterCamera::backBuffer, TRANSPARENT);
}

MasterCamera::~MasterCamera()
{
	delete screen;

	DeleteObject(MasterCamera::backBuffer);
	DeleteObject(hBitmap);
}

void MasterCamera::Update()
{
	if (isMoving == true)
	{
		screen->center = LERP(screen->center, target->GetRect()->center, 0.05);
		if (screen->center == target->GetRect()->center)
			isMoving = false;
	}
	else
		screen->center = LERP(screen->center, target->GetRect()->center, 0.01);

	{
		if (screen->Left() < 0)
			screen->center.x = offset.x;
		if (screen->Right() > mapSize.x)
			screen->center.x = mapSize.x - offset.x;

		if (screen->Top() < 0)
			screen->center.y = offset.y;
		if (screen->Bottom() > mapSize.y)
			screen->center.y = mapSize.y - offset.y;
	}
}

void MasterCamera::TargetChange(Character* character)
{
	target = character;
	isMoving = true;
}

void MasterCamera::SetMapSize(Vector2 size)
{ 
	mapSize = size; 
	screen->center.x = mapSize.x / 2;
	screen->center.y = mapSize.y / 2;

	//MasterCamera::backBuffer가 CompatibleDC이지 hWnd랑 직접 관련있는 DC는 아니여서 그런가 아래 bitmap생성할 때 backBuffer넣으면 
	//색이 안나옴.
	HDC hdc = GetDC(hWnd);
	if (hBitmap == nullptr)
		hBitmap = CreateCompatibleBitmap(hdc, mapSize.x, mapSize.y);
	else 
	{
		DeleteObject(hBitmap);
		hBitmap = CreateCompatibleBitmap(hdc, mapSize.x, mapSize.y);
	}
	ReleaseDC(hWnd,hdc);

	SelectObject(MasterCamera::backBuffer, (HGDIOBJ)hBitmap);
}
