#pragma once

class Bitmap : public Texture
{
private:
	HDC memDC;
	HBITMAP bitmap;

	COLORREF transColor;

	HDC alphaMemDC;
	HBITMAP alphaBitmap;

	BLENDFUNCTION blendFunc;



public:
	Bitmap(wstring file,int width,int height,COLORREF transColor = MAGENTA);
	Bitmap(wstring file,int width,int height,int frameX,int frameY,COLORREF transColor = MAGENTA);
	~Bitmap();

	void CreateBitmap(wstring file, int width, int height);

	virtual void Render(Rect* rect) override;
	virtual void Render(Rect* rect, Vector2 curFrame) override;

	virtual void AlphaRender(Rect* rect, int alpha) override;
	virtual void AlphaRender(Rect* rect, Vector2 curFrame, int alpha) override;

	HDC GetMemDC() override { return memDC; }


};