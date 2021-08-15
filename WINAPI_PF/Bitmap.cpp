#include "Framework.h"
#include "Bitmap.h"

Bitmap::Bitmap(wstring file, int width, int height, COLORREF transColor)
	:transColor(transColor)
{
	CreateBitmap(file, width, height);
	frameSize = { width,height };
	maxFrame = { 1,1 };

}

Bitmap::Bitmap(wstring file, int width, int height, int frameX, int frameY, COLORREF transColor)
	:transColor(transColor)
{
	CreateBitmap(file, width, height);
	frameSize = { width / frameX ,height / frameY };
	maxFrame = { frameX,frameY };

}

Bitmap::~Bitmap()
{
	DeleteDC(memDC);
	DeleteObject(bitmap);
	DeleteDC(alphaMemDC);
	DeleteObject(alphaBitmap);
}

void Bitmap::CreateBitmap(wstring file, int width, int height)
{
	HDC hdc = GetDC(hWnd);

	memDC = CreateCompatibleDC(hdc);
	alphaMemDC = CreateCompatibleDC(hdc);
	alphaBitmap = CreateCompatibleBitmap(hdc, width, height);		//이미지 크기만한 비트맵
	ReleaseDC(hWnd,hdc);
	
	bitmap = (HBITMAP)LoadImage(hInst, file.c_str(), IMAGE_BITMAP, width, height, LR_LOADFROMFILE);

	SelectObject(memDC, bitmap);
	SelectObject(alphaMemDC, alphaBitmap);
	//DC - 메모리공간 , bitmap - 도화지

	originSize = { width,height };
}

void Bitmap::Render(Rect* rect)
{
	GdiTransparentBlt(
		Program::backBuffer, (int)rect->Left(), (int)rect->Top(), (int)rect->size.x, (int)rect->size.y,
		memDC, 0, 0, frameSize.x, frameSize.y,
		transColor
	);

	DrawBorderLine(rect);
}

void Bitmap::Render(Rect* rect, Vector2 curFrame)
{
	GdiTransparentBlt(
		Program::backBuffer, (int)rect->Left(), (int)rect->Top(), (int)rect->size.x, (int)rect->size.y,
		memDC, frameSize.x * curFrame.x, frameSize.y * curFrame.y, frameSize.x, frameSize.y,
		transColor
	);

	DrawBorderLine(rect);
}

void Bitmap::AlphaRender(Rect* rect, int alpha)
{
	blendFunc.SourceConstantAlpha = alpha;		//알파값 입력

	BitBlt(
		alphaMemDC, 0, 0, originSize.x, originSize.y,
		Program::backBuffer,rect->Left(),rect->Top(),
		SRCCOPY
	);

	GdiTransparentBlt(
		alphaMemDC, 0, 0, originSize.x, originSize.y,
		memDC, 0, 0, originSize.x, originSize.y,
		transColor
	);


	GdiAlphaBlend(
		Program::backBuffer, (int)rect->Left(), (int)rect->Top(), (int)rect->size.x, (int)rect->size.y,
		alphaMemDC, 0, 0, rect->size.x, rect->size.y,
		blendFunc
	);
	//단순히 이미지 전체 알파적용

	DrawBorderLine(rect);
}

void Bitmap::AlphaRender(Rect* rect, Vector2 curFrame, int alpha)
{
	blendFunc.SourceConstantAlpha = alpha;

	//배경을 알파처리 하면 뒷배경이 안나오고 의도하지 않은 색이 남는 경우가 있음.
	//따라서 일단 뒷배경을 alphaMemDC에 그린 다음 그 위에 alpha처리 할 비트맵 그린 다음 transparentblt으로 alpha처리 이미지 배경을 지워야함
	BitBlt(
		alphaMemDC, frameSize.x * curFrame.x, frameSize.y * curFrame.y, frameSize.x, frameSize.y,
		Program::backBuffer, (int)rect->Left(), (int)rect->Top(),
		SRCCOPY
	);
	//출력을 원하는 frame 위치 뒷배경에 backBuffer의 전체이미지 중 그려질 위치(rect)를 그려줌

	//배경색 알파처리
	GdiTransparentBlt(
		alphaMemDC, 0, 0, originSize.x, originSize.y,
		memDC, 0, 0, originSize.x, originSize.y,			//LoadImage한 bitmap이 memDC에 저장되어있음
		transColor
	);
	//전체 비트맵의 transColor 알파처리

	//배경 알파처리 완료된 이미지 전체의 알파처리
	GdiAlphaBlend(
		Program::backBuffer, (int)rect->Left(), (int)rect->Top(), (int)rect->size.x, (int)rect->size.y,
		alphaMemDC, frameSize.x * curFrame.x, frameSize.y * curFrame.y, frameSize.x, frameSize.y,
		blendFunc
	);

	DrawBorderLine(rect);

}
