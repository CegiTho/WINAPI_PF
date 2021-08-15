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
    //textures �ȿ� Plusmap�� ��������ٵ� ���� Plusmap�� �������� ���� token�� ShutDown�Ǹ� ���α׷� ����.
    //Plusmap ������ Gdiplus::Graphics graphics ����� �����ִµ� �̰� �������¿��� Shutdown�Ǽ� �߻��ϴ� ������

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
