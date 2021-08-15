#pragma once

class TextureManager
{
private:
	TextureManager();
	~TextureManager();
	
	static TextureManager* instance;

	map<wstring, Texture*> textures;

	Gdiplus::GdiplusStartupInput input;
	ULONG_PTR token;


public:
	static TextureManager* Get()
	{
		return instance;
	}

	static void Create()
	{
		instance = new TextureManager();
	}

	static void Delete()
	{
		delete instance;
	}
	
	Texture* BitmapAdd(wstring file, int width, int height, COLORREF transColor = MAGENTA);
	Texture* BitmapAdd(wstring file, int width, int height,int frameX,int frameY, COLORREF transColor = MAGENTA);

	Texture* PlusmapAdd(wstring file, Gdiplus::Color transColor = Gdiplus::Color::Magenta);
	Texture* PlusmapAdd(wstring file, int frameX,int frameY,Gdiplus::Color transColor = Gdiplus::Color::Magenta);

	bool isDebug;

};


