#include "Framework.h"

Plusmap::Plusmap(wstring file, Gdiplus::Color transColor)
	:isResize(false)
{
	CreatePlusmap(file, transColor);

	frameSize = originSize;
	maxFrame = { 1,1 };

}

Plusmap::Plusmap(wstring file, int frameX, int frameY, Gdiplus::Color transColor)
{
	CreatePlusmap(file, transColor);

	maxFrame = { frameX,frameY };
	frameSize = { originSize.x / frameX , originSize.y / frameY };

}

Plusmap::~Plusmap()
{
	delete graphics;
	delete image;

	for (Gdiplus::CachedBitmap* bitmap : cachedBitmap)
		delete bitmap;
}

void Plusmap::CreatePlusmap(wstring file, Gdiplus::Color transColor)
{
	graphics = new Gdiplus::Graphics(Program::backBuffer);
	image = Gdiplus::Image::FromFile(file.c_str());

	originSize.x = image->GetWidth();
	originSize.y = image->GetHeight();

	attributes.SetColorKey(transColor, transColor);

	//�̹��� Ȯ��-��� �����ɼ�(interpolation : ����,attribute : �Ӽ�)
	graphics->SetInterpolationMode(Gdiplus::InterpolationMode::InterpolationModeNearestNeighbor);
	graphics->SetPixelOffsetMode(Gdiplus::PixelOffsetMode::PixelOffsetModeHalf);

}

void Plusmap::Render(Rect* rect)
{
	if (isResize == false)
		Resize(rect->size);

	destRect.X = (INT)rect->Left();
	destRect.Y = (INT)rect->Top();
	destRect.Width = (INT)rect->size.x;
	destRect.Height = (INT)rect->size.y;

	graphics->DrawCachedBitmap(cachedBitmap[0], destRect.X, destRect.Y);

	DrawBorderLine(rect);
}

void Plusmap::Render(Rect* rect, Vector2 curFrame)
{
	if (isResize == false)
		Resize(rect->size);

	destRect.X = (INT)rect->Left();
	destRect.Y = (INT)rect->Top();
	destRect.Width = (INT)rect->size.x;
	destRect.Height = (INT)rect->size.y;

	int frame = curFrame.y * maxFrame.x + curFrame.x;
	graphics->DrawCachedBitmap(cachedBitmap[frame], destRect.X, destRect.Y);

	DrawBorderLine(rect);
}

void Plusmap::Render(Rect* rect, RECT rectFrame)
{
	if (isResize == false)
		Resize(rect->size);

	destRect.X = (INT)rect->Left();
	destRect.Y = (INT)rect->Top();
	destRect.Width = (INT)rect->size.x;
	destRect.Height = (INT)rect->size.y;

	graphics->DrawImage(image, destRect,
		rectFrame.left, rectFrame.top,
		rectFrame.right, rectFrame.bottom,
		Gdiplus::Unit::UnitPixel, &attributes
	);

	DrawBorderLine(rect);
}

void Plusmap::AlphaRender(Rect* rect, int alpha)
{
	if (isResize == false)
		Resize(rect->size);

	destRect.X = (INT)rect->Left();
	destRect.Y = (INT)rect->Top();
	destRect.Width = (INT)rect->size.x;
	destRect.Height = (INT)rect->size.y;

	Gdiplus::ColorMatrix matrix = {
		1.0f,0.0f,0.0f,0.0f,0.0f,				//R
		0.0f,1.0f,0.0f,0.0f,0.0f,				//G
		0.0f,0.0f,1.0f,0.0f,0.0f,				//B
		0.0f,0.0f,0.0f,alpha / 255.0f,0.0f,		//A
		0.0f,0.0f,0.0f,0.0f,1.0f				//?
	};

	//���ĸ�Ʈ���� ����
	attributes.SetColorMatrix(&matrix, Gdiplus::ColorMatrixFlagsDefault, Gdiplus::ColorAdjustTypeBitmap);

	//graphics->DrawCachedBitmap(cachedBitmap[0], destRect.X, destRect.Y);
	//alpha render�Ҷ��� cachedbitmap���δ� ������ �ȵ�.
	graphics->DrawImage(image, destRect,
		0, 0, originSize.x, originSize.y,
		Gdiplus::UnitPixel, &attributes
	);

	DrawBorderLine(rect);
}

void Plusmap::AlphaRender(Rect* rect, Vector2 curFrame, int alpha)
{
	if (isResize == false)
		Resize(rect->size);

	destRect.X = (INT)rect->Left();
	destRect.Y = (INT)rect->Top();
	destRect.Width = (INT)rect->size.x;
	destRect.Height = (INT)rect->size.y;

	//5x5��� , 0~1���̰�
	Gdiplus::ColorMatrix matrix = {
		1.0f,0.0f,0.0f,0.0f,0.0f,				//R
		0.0f,1.0f,0.0f,0.0f,0.0f,				//G
		0.0f,0.0f,1.0f,0.0f,0.0f,				//B
		0.0f,0.0f,0.0f,alpha / 255.0f,0.0f,		//A
		0.0f,0.0f,0.0f,0.0f,1.0f				//?
	};

	//���ĸ�Ʈ���� ����
	attributes.SetColorMatrix(&matrix, Gdiplus::ColorMatrixFlagsDefault, Gdiplus::ColorAdjustTypeBitmap);

	//graphics->DrawCachedBitmap(cachedBitmap[0], destRect.X, destRect.Y);
	//alpha render�Ҷ��� cachedbitmap���δ� ������ �ȵ�.
	graphics->DrawImage(image, destRect,
		frameSize.x * curFrame.x,frameSize.y*curFrame.y,frameSize.x,frameSize.y,
		Gdiplus::UnitPixel, &attributes
	);

	DrawBorderLine(rect);
}

void Plusmap::Resize(Vector2 size)
{
	isResize = true;

	int length = maxFrame.x * maxFrame.y;

	for (int i = 0; i < length; i++)
	{
		int x = i % maxFrame.x;
		int y = i / maxFrame.x;

		Gdiplus::Bitmap bitmap((int)size.x, (int)size.y);
		Gdiplus::Graphics tempGraphics(&bitmap);

		//�Լ� ��ȣ�������� �Ʒ� dRect �߰���. �����ε��� 2��,5���� �����Ϸ��� ������ ���ؼ� ���� ����.
		//���� �ƹ��ų� �ᵵ ��������Ű���� �ѵ� �׳� 2������ ����.
		Gdiplus::Rect dRect = { 0,0,(int)size.x,(int)size.y };

		tempGraphics.DrawImage(
			image, dRect,
			frameSize.x * x, frameSize.y * y, frameSize.x, frameSize.y,
			Gdiplus::Unit::UnitPixel, &attributes
		);

		Gdiplus::CachedBitmap* cMap = new Gdiplus::CachedBitmap(&bitmap, &tempGraphics);
		cachedBitmap.emplace_back(cMap);

	}

}
