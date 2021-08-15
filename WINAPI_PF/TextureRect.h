#pragma once

class TextureRect
{
private:
	Texture* texture;
	Rect* rect;

	bool isActive;


public:
	TextureRect(wstring file,int width,int height,COLORREF transColor = MAGENTA);
	TextureRect(wstring file,Gdiplus::Color transColor = Gdiplus::Color::Magenta);
	~TextureRect();

	void Render();
	void Render(int alpha);
	void CameraRender();

	Rect* GetRect() { return rect; }

	double& PosX() { return rect->center.x; }
	double& PosY() { return rect->center.y; }

	double& SizeX() { return rect->size.x; }
	double& SizeY() { return rect->size.y; }

	void SetActive(bool value) { isActive = value; }
	bool GetActive() { return isActive; }
	Texture* GetTexture() { return texture; }

};


