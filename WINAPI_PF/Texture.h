#pragma once
class Texture
{
protected:
	POINT originSize;
	POINT frameSize;
	POINT maxFrame;

	Line borderLine[4];
	HPEN borderPen;

public:
	Texture();
	virtual ~Texture();

	virtual void Render(Rect* rect) {}
	virtual void Render(Rect* rect, Vector2 curFrame) {}
	virtual void Render(Rect* rect, RECT rectFrame) {}

	virtual void AlphaRender(Rect* rect, int alpha) {}
	virtual void AlphaRender(Rect* rect, Vector2 curFrame, int alpha) {}

	void UpdateBorderLine(Rect* rect);
	void DrawBorderLine(Rect* rect);

	POINT OriginSize() { return originSize; }
	POINT FrameSize() { return frameSize; }
	POINT MaxFrame() { return maxFrame; }

	Vector2 Size() { return Vector2((double)frameSize.x, (double)frameSize.y); }

	virtual HDC GetMemDC() { return nullptr; }

};
