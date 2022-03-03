#include "Framework.h"

SceneManager* SceneManager::instance = nullptr;

SceneManager::SceneManager()
    :curScene(nullptr)
{
}

SceneManager::~SceneManager()
{
    for (auto scene : scenes)
        delete scene.second;
}

void SceneManager::Update()
{
    if (curScene == nullptr)
        return;

    curScene->Update();
}

void SceneManager::Render(HDC hdc)
{
    if (curScene == nullptr)
        return;

    curScene->Render(hdc);
}

Scene* SceneManager::Add(string key, Scene* scene)
{
    if (scenes.count(key) > 0)
        return scenes[key];

    scenes[key] = scene;

    return scene;
}

void SceneManager::ChangeScene(string key)
{
    if (scenes.count(key) == 0)
        return;

    if (scenes[key] == curScene)
        return;

    if (curScene == nullptr)
        curScene = scenes[key];

    if (curScene->End() == true)
    {
        curScene = scenes[key];
        curScene->Start();
    }
}
