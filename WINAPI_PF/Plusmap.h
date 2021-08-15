#pragma once

class Plusmap : public Texture
{
private:
	Gdiplus::Image* image;
	Gdiplus::Graphics* graphics;

	Gdiplus::Rect destRect;
	Gdiplus::ImageAttributes attributes;

	//��������Ʈ �̹������� �ɰ����� �̹������� gdiplus�� �����ӵ���� ����.
	//�׷��� �ɰ��� �̹����� cachedBitmap�� �����Ͽ� �ǽð����� �ɰ��鼭 ���°� �ƴ϶� ����� �̹����� �������� �������� ����ȭ
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


