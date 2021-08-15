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
	alphaBitmap = CreateCompatibleBitmap(hdc, width, height);		//�̹��� ũ�⸸�� ��Ʈ��
	ReleaseDC(hWnd,hdc);
	
	bitmap = (HBITMAP)LoadImage(hInst, file.c_str(), IMAGE_BITMAP, width, height, LR_LOADFROMFILE);

	SelectObject(memDC, bitmap);
	SelectObject(alphaMemDC, alphaBitmap);
	//DC - �޸𸮰��� , bitmap - ��ȭ��

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
	blendFunc.SourceConstantAlpha = alpha;		//���İ� �Է�

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
	//�ܼ��� �̹��� ��ü ��������

	DrawBorderLine(rect);
}

void Bitmap::AlphaRender(Rect* rect, Vector2 curFrame, int alpha)
{
	blendFunc.SourceConstantAlpha = alpha;

	//����� ����ó�� �ϸ� �޹���� �ȳ����� �ǵ����� ���� ���� ���� ��찡 ����.
	//���� �ϴ� �޹���� alphaMemDC�� �׸� ���� �� ���� alphaó�� �� ��Ʈ�� �׸� ���� transparentblt���� alphaó�� �̹��� ����� ��������
	BitBlt(
		alphaMemDC, frameSize.x * curFrame.x, frameSize.y * curFrame.y, frameSize.x, frameSize.y,
		Program::backBuffer, (int)rect->Left(), (int)rect->Top(),
		SRCCOPY
	);
	//����� ���ϴ� frame ��ġ �޹�濡 backBuffer�� ��ü�̹��� �� �׷��� ��ġ(rect)�� �׷���

	//���� ����ó��
	GdiTransparentBlt(
		alphaMemDC, 0, 0, originSize.x, originSize.y,
		memDC, 0, 0, originSize.x, originSize.y,			//LoadImage�� bitmap�� memDC�� ����Ǿ�����
		transColor
	);
	//��ü ��Ʈ���� transColor ����ó��

	//��� ����ó�� �Ϸ�� �̹��� ��ü�� ����ó��
	GdiAlphaBlend(
		Program::backBuffer, (int)rect->Left(), (int)rect->Top(), (int)rect->size.x, (int)rect->size.y,
		alphaMemDC, frameSize.x * curFrame.x, frameSize.y * curFrame.y, frameSize.x, frameSize.y,
		blendFunc
	);

	DrawBorderLine(rect);

}
