#include "Framework.h"
#include "MasterCamera.h"

HDC MasterCamera::backBuffer = nullptr;

MasterCamera::MasterCamera()
{
	target = nullptr;
	screen = new Rect({ 0,0 }, { WIN_WIDTH,WIN_HEIGHT });
	isMoving = true;
	isHold = false;
	offset = { CENTER_X,CENTER_Y };
	mapSize = { 0,0 };

	HDC hdc = GetDC(hWnd);
	MasterCamera::backBuffer = CreateCompatibleDC(hdc);
	clearDC = CreateCompatibleDC(hdc);
	hBitmap = nullptr;

	ReleaseDC(hWnd, hdc);
	SetBkMode(MasterCamera::backBuffer, TRANSPARENT);

}

MasterCamera::~MasterCamera()
{
	delete screen;

	DeleteObject(clearDC);
	DeleteObject(screenClear);

	DeleteObject(MasterCamera::backBuffer);
	DeleteObject(hBitmap);
}

void MasterCamera::Update()
{
	if (isHold == true)
		return;

	if (isClear == true)
	{
		ScreenClear();
		return;
	}
	screen->center = LERP(screen->center, target->center, 0.03);

	{
		if (screen->Left() < 0)
			screen->center.x = screen->size.x * 0.5;
		if (screen->Right() > mapSize.x)
			screen->center.x = mapSize.x - screen->size.x * 0.5;

		if (screen->Top() < 0)
			screen->center.y = screen->size.y * 0.5;
		if (screen->Bottom() > mapSize.y)
			screen->center.y = mapSize.y - screen->size.y * 0.5;
	}
}

void MasterCamera::TargetChange(Rect* rect)
{
	target = rect;
	isMoving = true;
}

void MasterCamera::SetMapSize(Vector2 size, bool isHold)
{ 
	mapSize = size; 
	screen->center.x = mapSize.x / 2;
	screen->center.y = mapSize.y / 2;
	this->isHold = isHold;
	offset.x = size.x * 0.5;
	offset.y = size.y * 0.5;

	//MasterCamera::backBuffer가 CompatibleDC이지 hWnd랑 직접 관련있는 DC는 아니여서 그런가 아래 bitmap생성할 때 backBuffer넣으면 
	//색이 안나옴.
	HDC hdc = GetDC(hWnd);
	if (hBitmap == nullptr)
	{
		hBitmap = CreateCompatibleBitmap(hdc, mapSize.x, mapSize.y);
		screenClear = CreateCompatibleBitmap(hdc, mapSize.x, mapSize.y);
	}
	else 
	{
		DeleteObject(hBitmap);
		hBitmap = CreateCompatibleBitmap(hdc, mapSize.x, mapSize.y);
		DeleteObject(screenClear);
		screenClear = CreateCompatibleBitmap(hdc, mapSize.x, mapSize.y);
	}
	ReleaseDC(hWnd,hdc);

	SelectObject(MasterCamera::backBuffer, (HGDIOBJ)hBitmap);
	SelectObject(clearDC, (HGDIOBJ)screenClear);
}

void MasterCamera::ScreenClear()
{
	
}

