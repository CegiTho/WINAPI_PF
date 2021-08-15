#include "Framework.h"

TextureRect::TextureRect(wstring file, int width, int height, COLORREF transColor)
	:isActive(true)
{
	texture = TEX->BitmapAdd(file, width, height, transColor);
	rect = new Rect(Vector2(0, 0), texture->Size());		
}

TextureRect::TextureRect(wstring file, Gdiplus::Color transColor)
	:isActive(true)
{
	texture = TEX->PlusmapAdd(file, transColor);
	rect = new Rect(Vector2(0, 0), texture->Size());
}

TextureRect::~TextureRect()
{
	delete rect;
}

void TextureRect::Render()
{
	if (isActive == true)
		texture->Render(rect);
}

void TextureRect::Render(int alpha)
{
	if (isActive == true)
		texture->AlphaRender(rect, alpha);
}

void TextureRect::CameraRender()
{
	if (isActive == true)
	{
		Rect temp = *rect;
		temp.center -= CAM->Pos();

		texture->Render(&temp);
	}
}
