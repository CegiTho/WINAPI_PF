#include "Framework.h"
#include "TextureManager.h"

TextureManager* TextureManager::instance = nullptr;

TextureManager::TextureManager()
    :isDebug(true)
{
    Gdiplus::GdiplusStartup(&token, &input, nullptr);
}

TextureManager::~TextureManager()
{
    for (auto texture : textures)
        delete texture.second;

    Gdiplus::GdiplusShutdown(token);        
    //textures 안에 Plusmap도 들어있을텐데 만약 Plusmap이 지워지기 전에 token이 ShutDown되면 프로그램 터짐.
    //Plusmap 각각이 Gdiplus::Graphics graphics 멤버를 갖고있는데 이게 남은상태에서 Shutdown되서 발생하는 문제임

    textures.clear();
}

Texture* TextureManager::BitmapAdd(wstring file, int width, int height, COLORREF transColor)
{
    if (textures.count(file) > 0)
        return textures[file];

    Texture* texture = new Bitmap(file, width, height, transColor);

    textures[file] = texture;

    return texture;
}

Texture* TextureManager::BitmapAdd(wstring file, int width, int height, int frameX, int frameY, COLORREF transColor)
{
    if (textures.count(file) > 0)
        return textures[file];

    Texture* texture = new Bitmap(file, width, height, frameX, frameY, transColor);

    textures[file] = texture;

    return texture;
}

Texture* TextureManager::PlusmapAdd(wstring file, Gdiplus::Color transColor)
{
    if (textures.count(file) > 0)
        return textures[file];

    Texture* texture = new Plusmap(file, transColor);

    textures[file] = texture;
  
    return texture;
}

Texture* TextureManager::PlusmapAdd(wstring file, int frameX, int frameY, Gdiplus::Color transColor)
{
    if (textures.count(file) > 0)
        return textures[file];

    Texture* texture = new Plusmap(file, frameX, frameY, transColor);

    textures[file] = texture;

    return texture;
}
