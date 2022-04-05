#include "Framework.h"
#include "Texture.h"

Texture::Texture()
	:borderLine{}
{
	borderPen = CreatePen(PS_SOLID, 3, GREEN);
}

Texture::~Texture()
{
	DeleteObject(borderPen);

}

void Texture::UpdateBorderLine(Rect* rect)
{
	borderLine[0].Start() = Vector2(rect->Left(), rect->Top());
	borderLine[0].End() = Vector2(rect->Right(), rect->Top());

	borderLine[1].Start() = Vector2(rect->Right(), rect->Top());
	borderLine[1].End() = Vector2(rect->Right(), rect->Bottom());
	
	borderLine[2].Start() = Vector2(rect->Right(), rect->Bottom());
	borderLine[2].End() = Vector2(rect->Left(), rect->Bottom());
	
	borderLine[3].Start() = Vector2(rect->Left(), rect->Bottom());
	borderLine[3].End() = Vector2(rect->Left(), rect->Top());

}

void Texture::DrawBorderLine(Rect* rect)
{
	SelectObject(MasterCamera::backBuffer, borderPen);

	UpdateBorderLine(rect);

	for (Line line : borderLine)
		line.Render(MasterCamera::backBuffer);

}
