#pragma once

class Plusmap : public Texture
{
private:
	Gdiplus::Image* image;
	Gdiplus::Graphics* graphics;

	Gdiplus::Rect destRect;
	Gdiplus::ImageAttributes attributes;

	//스프라이트 이미지같이 쪼개쓰는 이미지에서 gdiplus는 프레임드랍이 심함.
	//그래서 쪼개진 이미지를 cachedBitmap에 저장하여 실시간으로 쪼개면서 쓰는게 아니라 저장된 이미지를 꺼내쓰는 형식으로 최적화
	vector<Gdiplus::CachedBitmap*> cachedBitmap;
	
	bool isResize;



public:
	Plusmap(wstring file,Gdiplus::Color transColor = Gdiplus::Color::Magenta);
	Plusmap(wstring file,int frameX,int frameY,Gdiplus::Color transColor = Gdiplus::Color::Magenta);
	~Plusmap();

	void CreatePlusmap(wstring file, Gdiplus::Color transColor);

	virtual void Render(Rect* rect) override;
	virtual void Render(Rect* rect, Vector2 curFrame) override;
	virtual void Render(Rect* rect, RECT rectFrame) override;

	virtual void AlphaRender(Rect* rect, int alpha) override;
	virtual void AlphaRender(Rect* rect, Vector2 curFrame, int alpha) override;

	void Resize(Vector2 size);
	
};


